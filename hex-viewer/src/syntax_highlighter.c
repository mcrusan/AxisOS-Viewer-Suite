/*==============================================================================
 *  FILE:        syntax_highlighter.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Tag-based highlighting for numeric and ASCII panes.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-04
 *  VERSION:     1.3
 *
 *  STANDARD OPERATING PROCEDURE — AxisOS Code Compliance
 *  ---------------------------------------------------------------------------
 *  • All modules must include a complete SOP header block.
 *  • Comments must be concise, contextual, and non-decorative.
 *  • No banner art, no ASCII rulers, no narrative comments.
 *  • Functions must be single-purpose and predictable.
 *  • All identifiers must be stable and consistent across modules.
 *  • All behavior must be deterministic and testable.
 *============================================================================*/

#include "../include/syntax_highlighter.h"
#include "../include/global.h"

/*------------------------------------------------------------------------------
 *  syntax_highlighter_apply()
 *
 *  Apply tag-based highlighting to a GtkTextBuffer. This function is used for
 *  both the numeric pane (address + hex) and the ASCII pane. Address highlighting
 *  is always applied to the first 8 characters of each line. ASCII highlighting
 *  applies printable vs. control character tags to the remainder of the line.
 *----------------------------------------------------------------------------*/
void syntax_highlighter_apply(GtkTextBuffer *buf)
{
    if (!buf) return;

    GtkTextTagTable *table = gtk_text_buffer_get_tag_table(buf);

    /* Address tag (first 8 chars) */
    GtkTextTag *addr_tag = gtk_text_tag_table_lookup(table, "addr");
    if (!addr_tag) {
        addr_tag = gtk_text_buffer_create_tag(buf, "addr",
                                              "foreground", "#8888ff",
                                              "weight", PANGO_WEIGHT_BOLD,
                                              NULL);
    }

    /* Printable ASCII tag */
    GtkTextTag *ascii_print = gtk_text_tag_table_lookup(table, "ascii_print");
    if (!ascii_print) {
        // ascii_print = gtk_text_buffer_create_tag(buf, "ascii_print",
        //                                         "foreground", "#C0CAF5",
        //                                         NULL);

        ascii_print = gtk_text_buffer_create_tag(buf, "ascii_print",
                                                 "foreground", "#C0CAF5",
                                                 "weight", PANGO_WEIGHT_NORMAL,
                                                 NULL);

        /* Set priority properly */
        // gtk_text_tag_set_priority(ascii_print, 10);

    }

    /* Control / non-printable ASCII tag */
    GtkTextTag *ascii_control = gtk_text_tag_table_lookup(table, "ascii_control");
    if (!ascii_control) {
        // ascii_control = gtk_text_buffer_create_tag(buf, "ascii_control",
        //                                           "foreground", "#F7768E",
        //                                           NULL);

        ascii_control = gtk_text_buffer_create_tag(buf, "ascii_control",
                                                   "foreground", "#F7768E",
                                                   "background-set", FALSE,
                                                   "weight", PANGO_WEIGHT_NORMAL,
                                                   NULL);
    }

    GtkTextIter iter;
    gtk_text_buffer_get_start_iter(buf, &iter);

    while (!gtk_text_iter_is_end(&iter)) {

        GtkTextIter line_start = iter;
        GtkTextIter line_end   = iter;

        gtk_text_iter_forward_to_line_end(&line_end);

        /* Highlight address region (first 8 chars) */
        GtkTextIter addr_end = line_start;
        gtk_text_iter_forward_chars(&addr_end, 8);
        gtk_text_buffer_apply_tag(buf, addr_tag, &line_start, &addr_end);

        /* Highlight ASCII region (after address) */
        GtkTextIter ascii_iter = addr_end;

        while (gtk_text_iter_compare(&ascii_iter, &line_end) < 0) {

            gunichar ch = gtk_text_iter_get_char(&ascii_iter);

            GtkTextIter next = ascii_iter;
            gtk_text_iter_forward_char(&next);

            if (g_unichar_isprint(ch))
                gtk_text_buffer_apply_tag(buf, ascii_print, &ascii_iter, &next);
            else
                gtk_text_buffer_apply_tag(buf, ascii_control, &ascii_iter, &next);

            ascii_iter = next;
        }

        if (!gtk_text_iter_forward_line(&iter))
            break;
    }
}
