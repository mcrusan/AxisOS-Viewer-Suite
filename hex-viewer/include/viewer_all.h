/*==============================================================================
 *  FILE:        viewer_all.h
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Unified include index for all public viewer APIs.
 *
 *  AUTHOR:      Marc & PP (Pocket Professor)
 *  CREATED:     2026-06-08
 *  VERSION:     1.0
 *
 *  NOTE: To use place the following at the top of a *.c file
 *  #include "../include/viewer_all.h"
 *
 *============================================================================*/

#ifndef VIEWER_ALL_H
#define VIEWER_ALL_H

/* Core viewer API */
#include "viewer.h"
#include "viewer_modes.h"
#include "global.h"

/* Rendering */
#include "viewer_render_hex.h"
#include "viewer_render_ascii.h"
#include "ascii_color.h"

/* Offsets */
#include "viewer_offsets.h"
#include "viewer_offset_render.h"
#include "viewer_file_size.h"

/* Geometry + Metrics */
#include "viewer_geometry.h"
#include "viewer_metrics.h"
#include "viewer_layout.h"
#include "viewer_font.h"

/* Selection + Sync */
#include "viewer_selection_sync.h"

/* Utilities */
#include "pp_ptr_list.h"
#include "pp_ptr_view.h"
#include "ptr_dbcore_insert.h"

#endif /* VIEWER_ALL_H */
