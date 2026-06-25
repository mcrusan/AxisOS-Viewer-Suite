/*==============================================================================
 *  FILE:        viewer_layout.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Layout helpers for aligning hex, ASCII, and offset panes.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *============================================================================*/

#ifndef VIEWER_LAYOUT_H
#define VIEWER_LAYOUT_H

#include <gtk/gtk.h>

void viewer_sync_scroll(GtkWidget *hex_view,
                        GtkWidget *ascii_view,
                        GtkWidget *offset_view);

#endif /* VIEWER_LAYOUT_H */
