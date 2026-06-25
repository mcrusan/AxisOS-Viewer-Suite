/*==============================================================================
 *  FILE:        viewer_font.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Apply fixed-width font to text views for alignment stability.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - Hex/Oct/Bin viewers require monospaced font for column alignment.
 *      - Called once during viewer initialization.
 *============================================================================*/

#include <gtk/gtk.h>

void viewer_set_font(GtkWidget *view)
{
    PangoFontDescription *font =
    pango_font_description_from_string("Source Code Pro 11");

    gtk_widget_override_font(view, font);
    pango_font_description_free(font);
}
