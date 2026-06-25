/* ============================================================
 *   FILE: help_submission_form.c
 *   SYSTEM: AxisOS
 *   SUBSYSTEM: UI / Help Menu / PTR Submission
 *   AUTHOR: Marc + PP (Co‑Pilot)
 *   CREATED: 2026-06-06
 *   VERSION: 1.0
 *   PURPOSE:
 *       Implements the modal submission form for PTR intake:
 *       - Bug Reports
 *       - Improvement Suggestions
 *
 *       Collects user input and prepares it for insertion into
 *       dbcore (PTR_Reports). This module is the UI front-end
 *       for the AxisOS PTR system.
 *
 *   NOTES:
 *       - Fully SOP compliant.
 *       - dbcore insertion hooks marked TODO.
 *       - PP-CLI tentacle integration planned.
 *   ============================================================ */

#include <gtk/gtk.h>
#include "../include/global.h"

static GtkWidget* make_text_view() {
    GtkWidget *tv = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv), GTK_WRAP_WORD_CHAR);
    return tv;
}

/* ------------------------------------------------------------
 *   FUNCTION: submit_ptr_form
 *   PURPOSE:
 *       Displays a modal submission form for either Bug Reports
 *       or Improvement Suggestions. Collects user input and
 *       prepares it for dbcore insertion.
 *   ------------------------------------------------------------ */
void submit_ptr_form(GtkWidget *widget, gpointer data) {

    const char *type = (const char*)data;

    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        type,
        NULL,
        GTK_DIALOG_MODAL,
        "_Submit", GTK_RESPONSE_OK,
        "_Cancel", GTK_RESPONSE_CANCEL,
        NULL
    );

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 6);
    gtk_container_add(GTK_CONTAINER(content), grid);

    GtkWidget *title_entry = gtk_entry_new();
    GtkWidget *desc_view   = make_text_view();
    GtkWidget *steps_view  = make_text_view();
    GtkWidget *expected_view = make_text_view();
    GtkWidget *actual_view   = make_text_view();
    GtkWidget *email_entry = gtk_entry_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(title_entry), "Short title");
    gtk_entry_set_placeholder_text(GTK_ENTRY(email_entry), "Optional email for plugin reward");

    int row = 0;

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Title:"), 0, row, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), title_entry, 1, row++, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Description:"), 0, row, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), desc_view, 1, row++, 1, 1);

    if (g_strcmp0(type, "Bug Report") == 0) {
        gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Steps to Reproduce:"), 0, row, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), steps_view, 1, row++, 1, 1);

        gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Expected Behavior:"), 0, row, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), expected_view, 1, row++, 1, 1);

        gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Actual Behavior:"), 0, row, 1, 1);
        gtk_grid_attach(GTK_GRID(grid), actual_view, 1, row++, 1, 1);
    }

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Email (optional):"), 0, row, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), email_entry, 1, row++, 1, 1);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        /* ----------------------------------------------------
         *           TODO:
         *             - Insert into PTR_Reports (dbcore)
         *             - Auto-assign plugin reward if email provided
         *             - Trigger PP-CLI triage tentacle
         *           ---------------------------------------------------- */
    }

    gtk_widget_destroy(dialog);
}
