/*==============================================================================
 *  FILE:        viewer_offset.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Render byte-offset ruler for hex viewer.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - One line per 16 bytes.
 *      - 8-digit hex offsets.
 *      - Non-editable, non-focusable.
 *============================================================================*/

#include <gtk/gtk.h>

GtkWidget* viewer_create_offset_view(void)
{
    GtkWidget *view = gtk_text_view_new();

    gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view), GTK_WRAP_NONE);
    gtk_widget_set_can_focus(view, FALSE);

    /* Monospaced font for alignment */
    PangoFontDescription *font =
    pango_font_description_from_string("Source Code Pro 11");
    gtk_widget_override_font(view, font);
    pango_font_description_free(font);

    return view;
}
