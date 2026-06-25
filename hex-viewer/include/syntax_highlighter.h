/*==============================================================================
 *  FILE:        syntax_highlighter.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Syntax highlighting hooks for numeric pane.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-04
 *  VERSION:     1.2
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  (See viewer.h for full SOP text — identical across modules.)
 *============================================================================*/

#ifndef AXISOS_SYNTAX_HIGHLIGHTER_H
#define AXISOS_SYNTAX_HIGHLIGHTER_H

#include <gtk/gtk.h>

void syntax_highlighter_apply(GtkTextBuffer *buf);

#endif /* AXISOS_SYNTAX_HIGHLIGHTER_H */
