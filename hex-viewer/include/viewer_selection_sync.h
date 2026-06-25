/*==============================================================================
 *  FILE:        viewer_selection_sync.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Public API for hex/ASCII selection mirroring.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  - Selection sync must be non-recursive (guarded).
 *  - Hex offsets convert via 3 chars/byte; ASCII via 1 char/byte.
 *  - Must not modify buffer content; selection only.
 *============================================================================*/

#ifndef VIEWER_SELECTION_SYNC_H
#define VIEWER_SELECTION_SYNC_H

#include <gtk/gtk.h>

void viewer_enable_selection_sync(GtkTextBuffer *hex_buf,
                                  GtkTextBuffer *ascii_buf);

#endif /* VIEWER_SELECTION_SYNC_H */
