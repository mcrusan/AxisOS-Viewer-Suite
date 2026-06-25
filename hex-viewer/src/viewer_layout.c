/* ============================================================
 *   FILE: viewer_layout.c
 *   SYSTEM: AxisOS
 *   SUBSYSTEM: UI / Viewer Layout
 *   AUTHOR: Marc + PP (Co‑Pilot)
 *   CREATED: 2026-06-07
 *   VERSION: 1.0
 *   PURPOSE:
 *       Adjust ASCII pane width based on active viewer mode.
 *       Hex, Octal, Binary each require different horizontal
 *       density. Net mode hides the ASCII pane entirely.
 *   ============================================================ */

#include "../include/viewer_layout.h"
#include "../include/global.h"

void set_viewer_mode(ViewerMode mode) {
    current_mode = mode;
    set_ascii_width_for_mode(mode, ascii_scroll);
    update_window_width(mode);
    refresh_view_buffers();
}


void set_ascii_width_for_mode(int mode, GtkWidget *ascii_scroll) {

    if (mode == MODE_HEX) {
        gtk_widget_set_size_request(ascii_scroll, 180, -1);
    }
    else if (mode == MODE_OCT) {
        gtk_widget_set_size_request(ascii_scroll, 150, -1);
    }
    else if (mode == MODE_BIN) {
        gtk_widget_set_size_request(ascii_scroll, 210, -1);
    }
    else if (mode == MODE_NET) {
        gtk_widget_hide(ascii_scroll);
        return;
    }

    gtk_widget_show(ascii_scroll);
}
