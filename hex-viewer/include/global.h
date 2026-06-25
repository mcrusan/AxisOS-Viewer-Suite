/*==============================================================================
 *  FILE:        global.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Global constants and shared definitions.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-04
 *  VERSION:     1.3
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  (See viewer.h for full SOP text — identical across modules.)
 *============================================================================*/

#ifndef AXISOS_GLOBAL_H
#define AXISOS_GLOBAL_H

#include <gtk/gtk.h>

#define EDITOR_TITLE "Viewer Suite v1.3"

#define TAG_PRIORITY_SELECTION 10

typedef struct {
    GtkWidget *window;
    GtkWidget *menu_open;
    GtkWidget *menu_quit;
    GtkWidget *menu_about;
    GtkWidget *menu_help;
    // … other fields …
} App;

#endif /* AXISOS_GLOBAL_H */
