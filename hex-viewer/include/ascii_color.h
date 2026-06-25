/*==============================================================================
 *  FILE:        ascii_color.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Public API for ASCII full-line color application.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  - All viewer modules must include a full SOP header block.
 *  - ASCII color functions must not modify buffer content.
 *  - Coloring must be applied using GtkTextTags only.
 *  - Must be safe to call repeatedly without side effects.
 *============================================================================*/

#ifndef ASCII_COLOR_H
#define ASCII_COLOR_H

#include <gtk/gtk.h>

void ascii_apply_full_line_color(GtkTextBuffer *buf,
                                 GtkTextIter *start,
                                 GtkTextIter *end);

#endif /* ASCII_COLOR_H */
