/*==============================================================================
 *  FILE:        viewer_file_size.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Utility: get file size in bytes.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - Used by offset renderer and viewer core.
 *      - Must be safe for large files.
 *============================================================================*/

#include <stdio.h>
#include <stdlib.h>

size_t viewer_get_file_size(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fclose(fp);

    return size;
}
