/*==============================================================================
 *  FILE:        viewer_geometry_utils.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Utility functions for measuring text geometry in GtkTextView.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - viewer_get_char_width() returns the pixel width of a single
 *        monospace character using the current Pango layout.
 *      - Used by viewer_set_hex_geometry() to compute column widths.
 *============================================================================*/

#include <gtk/gtk.h>
#include "../include/viewer_geometry.h"
/*
int viewer_get_char_width(GtkWidget *text_view)
{
    PangoContext *ctx = gtk_widget_get_pango_context(text_view);
    PangoFontMetrics *metrics =
    pango_context_get_metrics(ctx,
                              pango_context_get_font_description(ctx),
                              pango_context_get_language(ctx));

    int width = pango_font_metrics_get_approximate_char_width(metrics);

    pango_font_metrics_unref(metrics);

    // Convert from Pango units to pixels
    return width / PANGO_SCALE;
}
*/
