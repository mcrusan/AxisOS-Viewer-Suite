/*==============================================================================
 *  FILE:        viewer_render_hex.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Render 16‑byte hex blocks into a GtkTextBuffer.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *============================================================================*/

#ifndef VIEWER_RENDER_HEX_H
#define VIEWER_RENDER_HEX_H

#include <gtk/gtk.h>
#include <stddef.h>

void viewer_render_hex(GtkTextBuffer *buf,
                       const unsigned char *data,
                       size_t len);

#endif /* VIEWER_RENDER_HEX_H */
