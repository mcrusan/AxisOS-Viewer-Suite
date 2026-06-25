/*==============================================================================
 *  FILE:        gui_wrapper.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Main window, menu bar, toolbar, dual-pane layout wiring.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-04
 *  VERSION:     1.3 + selection-sync
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  (See viewer.h for full SOP text — identical across modules.)
 *============================================================================*/

#include "../include/global.h"
// #include "../include/plugin_loader.h"
#include "../include/about.h"
#include "../include/syntax_highlighter.h"
#include "../include/viewer.h"
#include "../include/viewer_modes.h"

#include <gtk/gtk.h>
#include <string.h>

extern App *app;

/* Dual-pane text views and buffers */
GtkWidget     *hex_view   = NULL;
GtkWidget     *ascii_view = NULL;
GtkTextBuffer *hex_buf    = NULL;
GtkTextBuffer *ascii_buf  = NULL;

/* Forward declaration for selection sync (implemented in viewer.c or similar) */
void viewer_sync_selection(GtkTextBuffer *hex_buffer,
                           GtkTextBuffer *ascii_buffer,
                           GtkTextBuffer *source_buffer);

/*────────────────────────────────────────────────────────────────────────────*/
/*  Selection change callback                                                 */
/*────────────────────────────────────────────────────────────────────────────*/
static void
on_mark_set(GtkTextBuffer *buffer,
            GtkTextIter   *location,
            GtkTextMark   *mark,
            gpointer       user_data)
{
    (void)location;
    (void)user_data;

    const char *name = gtk_text_mark_get_name(mark);
    if (!name)
        return;

    /* Only react to caret/selection changes */
    if (strcmp(name, "insert") != 0 &&
        strcmp(name, "selection_bound") != 0)
        return;

    /* Delegate actual mapping/sync to viewer layer */
    viewer_sync_selection(hex_buf, ascii_buf, buffer);
}

/*────────────────────────────────────────────────────────────────────────────*/
/*  Mode → string                                                             */
/*────────────────────────────────────────────────────────────────────────────*/
static const char* viewer_mode_to_string(ViewerMode current_mode)
{
    switch (current_mode) {
        case VIEW_MODE_HEX: return "hex";
        case VIEW_MODE_OCT: return "oct";
        case VIEW_MODE_BIN: return "bin";
        case VIEW_MODE_NET: return "net";
        default:            return "hex";
    }
}

/*────────────────────────────────────────────────────────────────────────────*/
/*  Open file dialog and render into dual-pane viewer                         */
/*────────────────────────────────────────────────────────────────────────────*/
static void on_open_file(GtkWidget *widget, gpointer data)
{
    (void)widget;
    (void)data;

    static ViewerMode current_mode = VIEW_MODE_HEX;

    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Open File",
        NULL,
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open",   GTK_RESPONSE_ACCEPT,
        NULL
    );

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename =
        gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        viewer_render_file(filename,
                           viewer_mode_to_string(current_mode),
                           hex_buf,
                           ascii_buf);

        /* Re-apply syntax highlighting on both panes after render */
        syntax_highlighter_apply(hex_buf);
        //syntax_highlighter_apply(ascii_buf);

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

/*────────────────────────────────────────────────────────────────────────────*/
/*  Create main application window                                            */
/*────────────────────────────────────────────────────────────────────────────*/
GtkWidget * create_main_window(void)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), EDITOR_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(window), 750, 500); // Hex window size

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 6);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /* Menubar */
    GtkWidget *menubar = gtk_menu_bar_new();

    /* File menu */
    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *file_item = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);

    GtkWidget *open_menu = gtk_menu_new();
    GtkWidget *open_item = gtk_menu_item_new_with_label("Open");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(open_item), open_menu);

    GtkWidget *open_hex = gtk_menu_item_new_with_label("Hex View");

    gtk_menu_shell_append(GTK_MENU_SHELL(open_menu), open_hex);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);

    GtkWidget *file_sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_sep);

    GtkWidget *quit_item = gtk_menu_item_new_with_label("Quit");
    g_signal_connect_swapped(quit_item, "activate",
                             G_CALLBACK(gtk_window_close), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_item);

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_item);

    /* Help menu */
    GtkWidget *help_menu = gtk_menu_new();
    GtkWidget *help_item = gtk_menu_item_new_with_label("Help");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_item), help_menu);

    GtkWidget *about_item = gtk_menu_item_new_with_label("About");
    g_signal_connect(about_item, "activate",
                     G_CALLBACK(show_about_dialog), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_item);

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_item);

    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    /* Register menu items into global App struct for hotkeys */
    app->menu_open  = open_hex;
    app->menu_quit  = quit_item;
    app->menu_about = about_item;
    app->menu_help  = help_item;

    /*──────────────────────────────────────────────────────────────────────*/
    /*  Accelerator group — FIXED (correct order, correct window)           */
    /*──────────────────────────────────────────────────────────────────────*/
    GtkAccelGroup *accel = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(window), accel);

    gtk_widget_add_accelerator(open_hex,
                               "activate",
                               accel,
                               GDK_KEY_o,
                               GDK_CONTROL_MASK,
                               GTK_ACCEL_VISIBLE);

    gtk_widget_add_accelerator(quit_item,
                               "activate",
                               accel,
                               GDK_KEY_q,
                               GDK_CONTROL_MASK,
                               GTK_ACCEL_VISIBLE);

    /* Toolbar with viewer mode buttons */
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);

    GtkWidget *btn_open_hex = gtk_button_new_with_label("Hex");

    gtk_box_pack_start(GTK_BOX(toolbar), btn_open_hex, FALSE, FALSE, 0);

    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_hexpand(spacer, TRUE);
    gtk_box_pack_start(GTK_BOX(toolbar), spacer, TRUE, TRUE, 0);

    GtkWidget *btn_about = gtk_button_new_with_label("About");
    g_signal_connect(btn_about, "clicked",
                     G_CALLBACK(show_about_dialog), window);
    gtk_box_pack_end(GTK_BOX(toolbar), btn_about, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    /* Wire file open actions */
    g_signal_connect(open_hex, "activate",
                     G_CALLBACK(on_open_file), "hex");

    g_signal_connect(btn_open_hex, "clicked",
                     G_CALLBACK(on_open_file), "hex");

    /* Create dual-pane tag tables and buffers */
    GtkTextTagTable *hex_tags   = gtk_text_tag_table_new();
    GtkTextTagTable *ascii_tags = gtk_text_tag_table_new();

    hex_buf   = gtk_text_buffer_new(hex_tags);
    ascii_buf = gtk_text_buffer_new(ascii_tags);

    /* Connect selection-change signals for sync */
    g_signal_connect(hex_buf,   "mark-set",
                     G_CALLBACK(on_mark_set), NULL);
    g_signal_connect(ascii_buf, "mark-set",
                     G_CALLBACK(on_mark_set), NULL);

    /* Create dual-pane views */
    hex_view   = gtk_text_view_new_with_buffer(hex_buf);
    ascii_view = gtk_text_view_new_with_buffer(ascii_buf);

    /* Removed selection-priority override (no longer needed) */

    gtk_text_view_set_monospace(GTK_TEXT_VIEW(hex_view), TRUE);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(ascii_view), TRUE);

    /* Pane padding and width tuning */
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(hex_view), 12);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(ascii_view), 12);

    /* Scrolled windows */
    GtkWidget *hex_scroll   = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *ascii_scroll = gtk_scrolled_window_new(NULL, NULL);

    gtk_container_add(GTK_CONTAINER(hex_scroll),   hex_view);
    gtk_container_add(GTK_CONTAINER(ascii_scroll), ascii_view);

    gtk_widget_set_hexpand(hex_scroll, TRUE);
    gtk_widget_set_hexpand(ascii_scroll, FALSE);
    gtk_widget_set_size_request(ascii_scroll, 180, -1);

    /* Pane spacing */
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 14);

    gtk_box_pack_start(GTK_BOX(hbox), hex_scroll,   TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), ascii_scroll, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    /* Shared vertical adjustment */
    GtkAdjustment *vadj =
    gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(hex_scroll));
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(ascii_scroll), vadj);

    int width  = 750;
    int height = 500;

    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    /* Initial syntax highlighting on both panes */
    syntax_highlighter_apply(hex_buf);

    return window;
}
