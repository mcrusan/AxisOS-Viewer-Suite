/*==============================================================================
 *  FILE:        viewer_render_ascii.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Render ASCII representation of bytes into a GtkTextBuffer.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *============================================================================*/

#ifndef VIEWER_RENDER_ASCII_H
#define VIEWER_RENDER_ASCII_H

#include <gtk/gtk.h>
#include <stddef.h>

void viewer_render_ascii(GtkTextBuffer *buf,
                         const unsigned char *data,
                         size_t len);

#endif /* VIEWER_RENDER_ASCII_H */
