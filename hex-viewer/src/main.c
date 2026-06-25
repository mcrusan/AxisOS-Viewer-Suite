/*==============================================================================
 *  FILE:        main.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     GTK application entry point.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-04
 *  VERSION:     1.3
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  (See viewer.h for full SOP text — identical across modules.)
 *============================================================================*/

#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "../include/global.h"

App *app = NULL;

GtkWidget *create_main_window(void);

// 20260605 (MFC) forward declaration for help window
void open_help_window(GtkWindow *parent);

static void setup_hotkeys(GtkWidget *window) {
    GtkAccelGroup *accel = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(window), accel);

    // O — Open
    gtk_widget_add_accelerator(app->menu_open, "activate",
                               accel, GDK_KEY_o, GDK_CONTROL_MASK,
                               GTK_ACCEL_VISIBLE);

    // Q — Quit
    gtk_widget_add_accelerator(app->menu_quit, "activate",
                               accel, GDK_KEY_q, GDK_CONTROL_MASK,
                               GTK_ACCEL_VISIBLE);

    // A — About
    gtk_widget_add_accelerator(app->menu_about, "activate",
                               accel, GDK_KEY_a, GDK_CONTROL_MASK,
                               GTK_ACCEL_VISIBLE);

    // F1 — Help
    gtk_widget_add_accelerator(app->menu_help, "activate",
                               accel, GDK_KEY_F1, 0,
                               GTK_ACCEL_VISIBLE);
}

// 20260605 (MFC) F‑1 hotkey support
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    (void)data;
    // TODO: 20260607 (MFC) add hotket for O, Q, A / in time S, P etc
    if (event->keyval == GDK_KEY_F1) {
        open_help_window(GTK_WINDOW(widget));
        return TRUE;
    }
    return FALSE;
}

void open_help_window(GtkWindow *parent) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
        "Viewer Help",
        parent,
        GTK_DIALOG_MODAL,
        "_Close", GTK_RESPONSE_CLOSE,
        NULL
    );

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);

    GtkWidget *label = gtk_label_new(
        "Viewer Quick Reference\n"
        "\n"
        "Hex Viewer: View files in hexadecimal.\n"
        "Octal Viewer: View files in octal.\n"
        "Binary Viewer: View files in binary.\n"
        "Net Viewer: Open files from network sources.\n"
        "\n"
        "Keyboard Shortcuts:\n"
        "  F1  – Help\n"
        "  Ctrl+O – Open File\n"
        "  Ctrl+Q – Quit\n"
        "\n"
        "PP Tip: \"Runtime is watching… stay hydrated.\"\n"
    );

    gtk_label_set_xalign(GTK_LABEL(label), 0.0);
    gtk_label_set_yalign(GTK_LABEL(label), 0.0);
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(label), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(label), 60);

    gtk_container_add(GTK_CONTAINER(scroll), label);
    gtk_container_add(GTK_CONTAINER(content), scroll);

    gtk_widget_set_size_request(scroll, 450, 350);

    gtk_window_set_icon_from_file(GTK_WINDOW(parent), "./logo_crusan.png", NULL);

    gtk_widget_show_all(dialog);

    g_signal_connect_swapped(dialog, "response",
                             G_CALLBACK(gtk_widget_destroy), dialog);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    app = g_malloc0(sizeof(App));

    GtkWidget *window = create_main_window();
    app->window = window;   // FIX: ensure app->window is valid for setup_hotkeys

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_icon_from_file(GTK_WINDOW(window), "./logo_crusan.png", NULL); // 20260607 (MFC) our window needs an icon

    // 20260605 (MFC) F‑1 key binding
    g_signal_connect(window, "key-press-event",
                     G_CALLBACK(on_key_press), NULL);

    setup_hotkeys(app->window);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
