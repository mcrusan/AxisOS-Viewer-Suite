/* ============================================================
 *   FILE: help_menu.c
 *   SYSTEM: AxisOS
 *   SUBSYSTEM: UI / Help Menu
 *   AUTHOR: Marc + PP (Co‑Pilot)
 *   CREATED: 2026-06-06
 *   VERSION: 1.0
 *   PURPOSE:
 *       Defines the Help menu structure for AxisOS, including:
 *       - Help (F1)
 *       - Bug Report submission form
 *       - Improvement Suggestion submission form
 *       - About dialog
 *
 *       All menu items follow AxisOS UI standards and connect
 *       to SOP-compliant modules. This file is part of the
 *       user-facing support and PTR intake workflow.
 *
 *   NOTES:
 *       - Fully SOP compliant.
 *       - Submission forms implemented in help_submission_form.c
 *       - PP acts as co-pilot for triage and routing.
 *   ============================================================ */

#include <gtk/gtk.h>
#include "help_submission_form.h"   // SOP-compliant header
#include "../include/global.h"

GtkWidget* build_help_menu() {

    GtkWidget *help_menu = gtk_menu_new();

    GtkWidget *help_item  = gtk_menu_item_new_with_label("Help (F1)");
    GtkWidget *bug_item   = gtk_menu_item_new_with_label("Bug Report…");
    GtkWidget *enh_item   = gtk_menu_item_new_with_label("Improvement Suggestion…");
    GtkWidget *about_item = gtk_menu_item_new_with_label("About AxisOS");

    GtkWidget *sep1 = gtk_separator_menu_item_new();
    GtkWidget *sep2 = gtk_separator_menu_item_new();

    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), help_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), sep1);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), bug_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), enh_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), sep2);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_item);

    g_signal_connect(bug_item, "activate", G_CALLBACK(submit_ptr_form), "Bug Report");
    g_signal_connect(enh_item, "activate", G_CALLBACK(submit_ptr_form), "Improvement Suggestion");

    return help_menu;
}
