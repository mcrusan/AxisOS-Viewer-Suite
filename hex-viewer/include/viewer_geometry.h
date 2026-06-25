/*==============================================================================
 *  FILE:        viewer_geometry.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Geometry functions for hex, ASCII, and offset panes.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *============================================================================*/

#ifndef VIEWER_GEOMETRY_H
#define VIEWER_GEOMETRY_H

#include <gtk/gtk.h>

/* Set width of hex pane (48 monospace chars) */
void viewer_set_hex_geometry(GtkWidget *hex_view);

/* Set width of ASCII pane (16 monospace chars) */
void viewer_set_ascii_geometry(GtkWidget *ascii_view);

/* Apply geometry lock to all panes */
void viewer_apply_geometry_lock(GtkWidget *hex_view,
                                GtkWidget *ascii_view,
                                GtkWidget *offset_view);

#endif /* VIEWER_GEOMETRY_H */
