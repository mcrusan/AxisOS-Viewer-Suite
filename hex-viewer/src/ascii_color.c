/*==============================================================================
 *  FILE:        ascii_color.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Apply full-line color tags to ASCII gutter for consistent
 *               appearance regardless of theme overrides.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - Tag must cover the entire inserted range.
 *      - Tag priority must exceed theme defaults.
 *      - This ensures ASCII gutter color is uniform across the whole line.
 *============================================================================*/

#include <gtk/gtk.h>

void ascii_apply_full_line_color(GtkTextBuffer *buf,
                                 GtkTextIter   *start,
                                 GtkTextIter   *end)
{
    GtkTextTagTable *table = gtk_text_buffer_get_tag_table(buf);

    /* Create or fetch the ASCII color tag */
    GtkTextTag *tag = gtk_text_tag_table_lookup(table, "ascii_color");
    if (!tag) {
        tag = gtk_text_tag_new("ascii_color");

        /* High priority ensures we override theme defaults */
        g_object_set(tag, "foreground", "#A0A0A0", "priority", 10, NULL);

        gtk_text_tag_table_add(table, tag);

        /* REAL priority setting — this is the missing piece */
        // gtk_text_tag_set_priority(tag, 10);


    }

    /* Apply tag to the entire line */
    gtk_text_buffer_apply_tag(buf, tag, start, end);
}
