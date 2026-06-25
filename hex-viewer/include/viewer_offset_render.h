/*==============================================================================
 *  FILE:        viewer_offset_render.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Render offset gutter lines (00000000, 00000010, …).
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *============================================================================*/

#ifndef VIEWER_OFFSET_RENDER_H
#define VIEWER_OFFSET_RENDER_H

#include <gtk/gtk.h>

void viewer_offset_render(GtkTextBuffer *buf, size_t total_bytes);

#endif /* VIEWER_OFFSET_RENDER_H */
