/*==============================================================================
 *  FILE:        about.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     About dialog implementation.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-04
 *  VERSION:     1.2
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  (See viewer.h for full SOP text — identical across modules.)
 *============================================================================*/

#include <gtk/gtk.h>
#include "../include/about.h"
#include "../include/global.h"

void show_about_dialog(GtkWidget *parent, gpointer data)
{
    (void)data;

    const gchar *authors[] = {
        "Marc F Crusan\nmarc@crusan.net\nPP - our Co-pilot",
        "<a href='https://www.paypal.com/donate/?hosted_button_id=9VSLMAJVS74CA'>Donate via PayPal</a>",
        NULL
    };

    GtkWidget *dialog = gtk_about_dialog_new();

    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog),
                                      "Viewer Suite");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.3");

    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),
                                  "Dual-pane Hex/Oct/Bin viewer with ASCII pane.\n"
                                  "Part of the AxisOS micro-enterprise toolchain."
    );

    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), authors);

    /* Load AxisOS logo */
    GError *err = NULL;
    GdkPixbuf *logo = gdk_pixbuf_new_from_file("./logo_crusan.png", &err);
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), "./logo_crusan.png", NULL);

    if (logo) {
        gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), logo);
        g_object_unref(logo);
    } else {
        g_warning("Failed to load AxisOS logo: %s", err->message);
        g_clear_error(&err);

        gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), NULL);
        gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(dialog), NULL);
    }

    /* PayPal link — AboutDialog supports custom widgets via credits section */
    GtkWidget *paypal_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(paypal_label),
                         "<span size='large' weight='bold'>Support AxisOS</span>\n"
                         "<a href='https://www.paypal.com/donate/?hosted_button_id=9VSLMAJVS74CA'>Donate via PayPal</a>");
    gtk_label_set_xalign(GTK_LABEL(paypal_label), 0.5);
    gtk_label_set_selectable(GTK_LABEL(paypal_label), TRUE);

    gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(dialog),
                                        "",
                                        (const gchar *[]) { NULL });

    gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(dialog), TRUE);

    /* FIX: Resolve parent to actual toplevel window */
    if (parent) {
        GtkWidget *toplevel = gtk_widget_get_toplevel(parent);
        if (GTK_IS_WINDOW(toplevel)) {
            gtk_window_set_transient_for(GTK_WINDOW(dialog),
                                         GTK_WINDOW(toplevel));
        }
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
