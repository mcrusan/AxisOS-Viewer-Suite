/*==============================================================================
 *  FILE:        viewer_geometry.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Compute and apply geometry for hex + ASCII panes, ensuring
 *               perfect alignment across fonts, themes, and DPI settings.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  - Geometry must be applied *after* scroll windows and text views exist.
 *  - Must run after font is applied (CSS provider loaded).
 *  - Must compute character width using viewer_metrics.c utilities.
 *  - Must set hex/ASCII pane widths to prevent drift during scrolling.
 *  - Must not hardcode pixel values; all geometry is font‑derived.
 *============================================================================*/

#include <gtk/gtk.h>
#include "../include/viewer_geometry.h"
#include "../include/viewer_metrics.h"      /* viewer_get_char_width() */
#include "../include/viewer_offsets.h"      /* offset gutter width     */

/*------------------------------------------------------------------------------
 *  viewer_set_hex_geometry
 *
 *  Compute the pixel width of the hex pane based on:
 *      - 16 bytes per row
 *      - 3 chars per byte ("AA ")
 *      - monospace character width from viewer_metrics
 *
 *  This function must be called AFTER:
 *      - hex_view is created
 *      - ascii_view is created
 *      - scroll windows are created
 *      - CSS font is applied
 *----------------------------------------------------------------------------*/
void viewer_set_hex_geometry(GtkWidget *hex_view)
{
    if (!hex_view)
        return;

    /* Character width in pixels (monospace) */
    int cw = viewer_get_char_width(hex_view);

    /* 16 bytes * 3 chars ("AA ") = 48 chars */
    int hex_chars = 16 * 3;

    /* Pixel width of the hex pane */
    int hex_width_px = hex_chars * cw;

    /* Apply geometry */
    gtk_widget_set_size_request(hex_view, hex_width_px, -1);
}

/*------------------------------------------------------------------------------
 *  viewer_set_ascii_geometry
 *
 *  ASCII pane is always 16 characters wide.
 *----------------------------------------------------------------------------*/
void viewer_set_ascii_geometry(GtkWidget *ascii_view)
{
    if (!ascii_view)
        return;

    int cw = viewer_get_char_width(ascii_view);
    int ascii_width_px = 16 * cw;

    gtk_widget_set_size_request(ascii_view, ascii_width_px, -1);
}

/*------------------------------------------------------------------------------
 *  viewer_apply_geometry_lock
 *
 *  Called once after:
 *      - hex_view added to scroll window
 *      - ascii_view added to scroll window
 *      - offset_view added to scroll window
 *      - CSS font applied
 *
 *  Ensures all three panes remain perfectly aligned.
 *----------------------------------------------------------------------------*/
/*
void viewer_apply_geometry_lock(GtkWidget *hex_view,
                                GtkWidget *ascii_view,
                                GtkWidget *offset_view)
{
    viewer_set_hex_geometry(hex_view);
    viewer_set_ascii_geometry(ascii_view);

    // Offset gutter width is fixed: 8 hex chars + newline
    int cw = viewer_get_char_width(offset_view);
    int offset_width_px = 8 * cw;

    gtk_widget_set_size_request(offset_view, offset_width_px, -1);
}
*/
