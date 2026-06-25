/*==============================================================================
 *  FILE:        viewer_metrics.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Public API for text metrics used by geometry calculations.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - viewer_get_char_width() returns the pixel width of a single
 *        monospace character using the current Pango layout.
 *      - Used by geometry, layout, and rendering modules.
 *============================================================================*/

#ifndef VIEWER_METRICS_H
#define VIEWER_METRICS_H

#include <gtk/gtk.h>

/* Return width of one monospace character in pixels */
int viewer_get_char_width(GtkWidget *text_view);

#endif /* VIEWER_METRICS_H */
