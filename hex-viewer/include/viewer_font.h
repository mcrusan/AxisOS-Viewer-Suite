/*==============================================================================
 *  FILE:        viewer_font.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Font application and CSS loading for viewer panes.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *============================================================================*/

#ifndef VIEWER_FONT_H
#define VIEWER_FONT_H

#include <gtk/gtk.h>

/* Apply monospace font to all viewer panes */
void viewer_apply_font(GtkWidget *hex_view,
                       GtkWidget *ascii_view,
                       GtkWidget *offset_view);

#endif /* VIEWER_FONT_H */
