/*==============================================================================
 *  FILE:        viewer_render_ascii.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Render ASCII gutter with printable chars or '.' fallback.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - Printable range: 32–126
 *      - Non-printable → '.'
 *============================================================================*/

#include <stddef.h>

void viewer_render_ascii_line(char *out,
                              const unsigned char *buf,
                              size_t len)
{
    for (size_t i = 0; i < len; i++)
        out[i] = (buf[i] >= 32 && buf[i] <= 126) ? buf[i] : '.';

    out[len] = '\0';
}
