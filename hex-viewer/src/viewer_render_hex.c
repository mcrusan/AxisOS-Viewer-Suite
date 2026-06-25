/*==============================================================================
 *  FILE:        viewer_render_hex.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Render one line of hex bytes with fixed spacing.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - 3 chars per byte: "XX "
 *      - No tabs, no variable spacing.
 *============================================================================*/

#include <stdio.h>

void viewer_render_hex_line(char *out,
                            const unsigned char *buf,
                            size_t len)
{
    for (size_t i = 0; i < len; i++)
        sprintf(out + (i * 3), "%02X ", buf[i]);
}
