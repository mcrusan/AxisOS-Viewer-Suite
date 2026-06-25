/*==============================================================================
 *  FILE:        viewer_offsets.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Render byte-offset ruler for the hex viewer.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  - Offset ruler must align 1:1 with hex/ASCII rows.
 *  - One line per 16 bytes.
 *  - Offsets must be uppercase 8-digit hex.
 *  - No buffer side effects beyond insertion.
 *  - Must be called after buffer is cleared.
 *============================================================================*/

#include <gtk/gtk.h>
#include <stdio.h>
#include "../include/viewer_offsets.h"

void viewer_render_offsets(GtkTextBuffer *buf, size_t file_size)
{
    GtkTextIter iter;
    gtk_text_buffer_get_start_iter(buf, &iter);

    /* Number of 16-byte rows */
    size_t lines = (file_size + 15) / 16;

    char line[32];

    for (size_t i = 0; i < lines; i++) {
        snprintf(line, sizeof(line), "%08lX\n", (unsigned long)(i * 16));
        gtk_text_buffer_insert(buf, &iter, line, -1);
    }
}
