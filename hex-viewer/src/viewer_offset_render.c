/*==============================================================================
 *  FILE:        viewer_offset_render.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Insert offset lines into the offset view buffer.
 *
 *  NOTES:
 *      - Called once per file load.
 *      - offset = line_index * 16
 *============================================================================*/

#include <gtk/gtk.h>
#include <stdio.h>
/*
void viewer_render_offsets(GtkTextBuffer *buf, size_t file_size)
{
    GtkTextIter iter;
    gtk_text_buffer_get_start_iter(buf, &iter);

    size_t lines = (file_size + 15) / 16;

    char line[16];

    for (size_t i = 0; i < lines; i++) {
        snprintf(line, sizeof(line), "%08lX\n", i * 16);
        gtk_text_buffer_insert(buf, &iter, line, -1);
    }
}
*/
