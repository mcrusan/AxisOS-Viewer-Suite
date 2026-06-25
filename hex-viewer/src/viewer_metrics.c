/*==============================================================================
 *  FILE:        viewer_metrics.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Measure pixel width of a single monospaced character.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - Used to compute pane widths and ASCII gutter alignment.
 *      - Must be called after font assignment.
 *============================================================================*/

#include <gtk/gtk.h>

int viewer_get_char_width(GtkWidget *widget)
{
    PangoContext *ctx = gtk_widget_get_pango_context(widget);
    PangoFontDescription *desc = pango_context_get_font_description(ctx);
    PangoFontMetrics *metrics =
    pango_context_get_metrics(ctx, desc, pango_language_get_default());

    int width = pango_font_metrics_get_approximate_char_width(metrics)
    / PANGO_SCALE;

    pango_font_metrics_unref(metrics);
    return width;
}
