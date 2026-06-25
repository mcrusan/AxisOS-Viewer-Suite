/*==============================================================================
 *  FILE:        viewer_selection_sync.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Mirror selection between hex and ASCII panes.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - Hex pane uses 3 chars per byte: "XX "
 *      - ASCII pane uses 1 char per byte
 *      - Selection must be mirrored without recursion
 *============================================================================*/

#include <gtk/gtk.h>

/* Forward declarations */
static void on_hex_mark_set(GtkTextBuffer *hex_buf,
                            GtkTextIter   *iter,
                            GtkTextMark   *mark,
                            gpointer        user_data);

static void on_ascii_mark_set(GtkTextBuffer *ascii_buf,
                              GtkTextIter   *iter,
                              GtkTextMark   *mark,
                              gpointer        user_data);

static gboolean sync_guard = FALSE;

/*────────────────────────────────────────────────────────────────────────────*/
/*  Compatibility wrapper for gui_wrapper.c                                   */
/*────────────────────────────────────────────────────────────────────────────*/
void viewer_sync_selection(GtkTextBuffer *hex_buf,
                           GtkTextBuffer *ascii_buf,
                           GtkTextBuffer *source_buf)
{
    /* Determine direction based on which buffer triggered the event */
    if (source_buf == hex_buf) {
        on_hex_mark_set(hex_buf, NULL, NULL, ascii_buf);
    } else if (source_buf == ascii_buf) {
        on_ascii_mark_set(ascii_buf, NULL, NULL, hex_buf);
    }
}


/*────────────────────────────────────────────────────────────────────────────*/
/*  Convert hex offset → byte index                                           */
/*────────────────────────────────────────────────────────────────────────────*/
static inline int hex_offset_to_byte(int offset)
{
    return offset / 3;   /* "XX " = 3 chars per byte */
}

/*────────────────────────────────────────────────────────────────────────────*/
/*  Convert ASCII offset → byte index                                         */
/*────────────────────────────────────────────────────────────────────────────*/
static inline int ascii_offset_to_byte(int offset)
{
    return offset;       /* 1 char per byte */
}

/*────────────────────────────────────────────────────────────────────────────*/
/*  Mirror selection from hex → ASCII                                         */
/*────────────────────────────────────────────────────────────────────────────*/
static void on_hex_mark_set(GtkTextBuffer *hex_buf,
                            GtkTextIter   *iter,
                            GtkTextMark   *mark,
                            gpointer        user_data)
{
(void)mark;
(void)iter;

    if (sync_guard) return;
    sync_guard = TRUE;

    GtkTextBuffer *ascii_buf = GTK_TEXT_BUFFER(user_data);

    GtkTextIter h_start, h_end;
    if (!gtk_text_buffer_get_selection_bounds(hex_buf, &h_start, &h_end)) {
        sync_guard = FALSE;
        return;
    }

    int byte_start = hex_offset_to_byte(gtk_text_iter_get_offset(&h_start));
    int byte_end   = hex_offset_to_byte(gtk_text_iter_get_offset(&h_end));

    GtkTextIter a_start, a_end;
    gtk_text_buffer_get_iter_at_offset(ascii_buf, &a_start, byte_start);
    gtk_text_buffer_get_iter_at_offset(ascii_buf, &a_end,   byte_end);

    gtk_text_buffer_select_range(ascii_buf, &a_start, &a_end);

    sync_guard = FALSE;
}

/*────────────────────────────────────────────────────────────────────────────*/
/*  Mirror selection from ASCII → hex                                         */
/*────────────────────────────────────────────────────────────────────────────*/
static void on_ascii_mark_set(GtkTextBuffer *ascii_buf,
                              GtkTextIter   *iter,
                              GtkTextMark   *mark,
                              gpointer        user_data)
{
(void)mark;
(void)iter;
    if (sync_guard) return;
    sync_guard = TRUE;

    GtkTextBuffer *hex_buf = GTK_TEXT_BUFFER(user_data);

    GtkTextIter a_start, a_end;
    if (!gtk_text_buffer_get_selection_bounds(ascii_buf, &a_start, &a_end)) {
        sync_guard = FALSE;
        return;
    }

    int byte_start = ascii_offset_to_byte(gtk_text_iter_get_offset(&a_start));
    int byte_end   = ascii_offset_to_byte(gtk_text_iter_get_offset(&a_end));

    GtkTextIter h_start, h_end;
    gtk_text_buffer_get_iter_at_offset(hex_buf, &h_start, byte_start * 3);
    gtk_text_buffer_get_iter_at_offset(hex_buf, &h_end,   byte_end   * 3);

    gtk_text_buffer_select_range(hex_buf, &h_start, &h_end);

    sync_guard = FALSE;
}

/*────────────────────────────────────────────────────────────────────────────*/
/*  Public API: connect both buffers                                          */
/*────────────────────────────────────────────────────────────────────────────*/
void viewer_enable_selection_sync(GtkTextBuffer *hex_buf,
                                  GtkTextBuffer *ascii_buf)
{
    g_signal_connect(hex_buf,   "mark-set",
                     G_CALLBACK(on_hex_mark_set),   ascii_buf);

    g_signal_connect(ascii_buf, "mark-set",
                     G_CALLBACK(on_ascii_mark_set), hex_buf);
}
