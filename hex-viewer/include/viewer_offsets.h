/*==============================================================================
 *  FILE:        viewer_offsets.H
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Render byte-offset ruler for the hex viewer.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  - All viewer modules must include a header block.
 *  - All rendering functions must be deterministic and side-effect free.
 *  - All buffers must be cleared before insertion.
 *  - All formatting must be monospaced and aligned to 16-byte boundaries.
 *============================================================================*/

#ifndef AXISOS_VIEWEROFFSETS_H
#define AXISOS_VIEWEROFFSETS_H

#include <gtk/gtk.h>
#include <stdio.h>
/***
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
***/
void viewer_render_offsets(GtkTextBuffer *buf, size_t file_size);


#endif /* AXISOS_VIEWEROFFSETS_H */
