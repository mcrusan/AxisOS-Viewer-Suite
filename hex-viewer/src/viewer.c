/*==============================================================================
 *  FILE:        viewer.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     File loading and dual-pane numeric/ASCII rendering.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-04
 *  VERSION:     1.3
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  1. All modules must compile cleanly under GCC and Clang with -Wall -Wextra.
 *  2. No dynamic memory without ownership clarity; all allocations paired with
 *     deterministic frees or owned by GTK lifecycle.
 *  3. No silent failures — all errors must be logged or surfaced to caller.
 *  4. No global state except where explicitly documented and justified.
 *  5. All UI components must follow dual-pane viewer architecture:
 *         LEFT  = numeric view (Hex/Oct/Bin)
 *         RIGHT = ASCII view
 *     with synchronized vertical scrolling and consistent monospace rendering.
 *  6. All modules must include SOP headers, consistent naming, and no drift.
 *  7. All code must be readable, maintainable, and free of legacy artifacts.
 *  8. All viewer output must be deterministic and reproducible.
 *  9. All plugins must follow the AxisOS Plugin ABI (v1.0).
 * 10. No animals were harmed in the making of this software.
 *
 *  NOTES:
 *      - This file is part of the AxisOS Viewer Suite distribution.
 *      - Any modification must preserve SOP compliance.
 *      - All viewer modules must remain hot‑reload safe.
 *============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/global.h"
#include "../include/ascii_color.h"
#include "../include/viewer.h"

static ViewerMode mode_from_string(const char *mode_str)
{
    if (!mode_str) return VIEW_MODE_HEX;
    if (strcmp(mode_str, "hex") == 0) return VIEW_MODE_HEX;
    if (strcmp(mode_str, "oct") == 0) return VIEW_MODE_OCT;
    if (strcmp(mode_str, "bin") == 0) return VIEW_MODE_BIN;
    return VIEW_MODE_HEX;
}

static void format_line(ViewerMode mode,
            unsigned long offset,
            const unsigned char *buf,
            size_t len,
            GString *numeric,
            GString *ascii)
{
    g_string_append_printf(numeric, "%08lX  ", offset);

    for (size_t i = 0; i < 16; i++) {
        if (i < len) {
            unsigned char c = buf[i];
            switch (mode) {
            case VIEW_MODE_HEX:
                g_string_append_printf(numeric, "%02X ", c);
                break;
            case VIEW_MODE_NET:
                break;
            case VIEW_MODE_OCT:
                g_string_append_printf(numeric, "%03o ", c);
                break;
            case VIEW_MODE_BIN: {
                for (int b = 7; b >= 0; --b)
                    g_string_append_c(numeric, (c & (1 << b)) ? '1' : '0');
                g_string_append_c(numeric, ' ');
                break;
            }
            }
            g_string_append_c(ascii, (c >= 32 && c <= 126) ? c : '.');
        } else {
            switch (mode) {
            case VIEW_MODE_HEX:
                g_string_append(numeric, "   ");
                break;
            case VIEW_MODE_NET:
                break;
            case VIEW_MODE_OCT:
                g_string_append(numeric, "    ");
                break;
            case VIEW_MODE_BIN:
                g_string_append(numeric, "         ");
                break;
            }
            g_string_append_c(ascii, ' ');
        }
        if (mode == VIEW_MODE_HEX && (i == 7))
            g_string_append_c(numeric, ' ');
    }

    g_string_append_c(numeric, '\n');
    g_string_append_c(ascii, '\n');
}

void viewer_render_file(const char *path,
                   const char *mode_str,
                   GtkTextBuffer *hex_buf,
                   GtkTextBuffer *ascii_buf)
{
    if (!path || !hex_buf || !ascii_buf) {
        g_warning("viewer_render_file: invalid arguments\n");
        return;
    }

    FILE *fp = fopen(path, "rb");
    if (!fp) {
        g_warning("Failed to open '%s': %s\n", path, strerror(errno));
        return;
    }

    ViewerMode mode = mode_from_string(mode_str);

    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(hex_buf, &start);
    gtk_text_buffer_get_end_iter(hex_buf, &end);
    gtk_text_buffer_delete(hex_buf, &start, &end);

    gtk_text_buffer_get_start_iter(ascii_buf, &start);
    gtk_text_buffer_get_end_iter(ascii_buf, &end);
    gtk_text_buffer_delete(ascii_buf, &start, &end);

    // ascii_apply_full_line_color(ascii_buf, &start, &end);

    /* Disable GTK's selection-foreground override for ASCII pane */
    // GtkTextTagTable *table = gtk_text_buffer_get_tag_table(ascii_buf);
    // GtkTextTag *sel = gtk_text_tag_table_lookup(table, "selection");

    GString *numeric = g_string_new(NULL);
    GString *ascii   = g_string_new(NULL);

    unsigned char buf[16];
    unsigned long offset = 0;
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) {
        format_line(mode, offset, buf, n, numeric, ascii);
        offset += n;
    }

    fclose(fp);

    gtk_text_buffer_set_text(hex_buf, numeric->str, -1);
    gtk_text_buffer_set_text(ascii_buf, ascii->str, -1);

    g_string_free(numeric, TRUE);
    g_string_free(ascii, TRUE);
}

size_t viewer_get_file_size(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fclose(fp);

    return size;
}
