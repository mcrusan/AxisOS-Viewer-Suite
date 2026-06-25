/*==============================================================================
 *  FILE:        viewer_offset.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Offset calculations and helpers for viewer rendering.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *============================================================================*/

#ifndef VIEWER_OFFSET_H
#define VIEWER_OFFSET_H

#include <stddef.h>

/* Convert byte index → row number */
size_t viewer_offset_row(size_t byte_index);

/* Convert row number → byte index */
size_t viewer_offset_start_byte(size_t row);

#endif /* VIEWER_OFFSET_H */
