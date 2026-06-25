/*==============================================================================
 *  FILE:        viewer.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Public interface for dual-pane viewer rendering.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-04
 *  VERSION:     1.2
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

#ifndef AXISOS_VIEWER_H
#define AXISOS_VIEWER_H

#include <gtk/gtk.h>

typedef enum {
    VIEW_MODE_HEX = 0,
    VIEW_MODE_OCT = 1,
    VIEW_MODE_BIN = 2,
    VIEW_MODE_NET = 3
} ViewerMode;

size_t viewer_get_file_size(const char *filename);

void viewer_render_file(const char *path,
                        const char *mode_str,
                        GtkTextBuffer *hex_buf,
                        GtkTextBuffer *ascii_buf);

#endif /* AXISOS_VIEWER_H */
