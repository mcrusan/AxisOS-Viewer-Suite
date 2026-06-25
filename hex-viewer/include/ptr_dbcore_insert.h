/* ============================================================
 *   FILE: ptr_dbcore_insert.h
 *   SYSTEM: AxisOS
 *   SUBSYSTEM: dbcore / PTR
 *   AUTHOR: Marc + PP (Co‑Pilot)
 *   CREATED: 2026-06-06
 *   VERSION: 1.0
 *   PURPOSE:
 *       Header for PTR dbcore insertion routines.
 *   ============================================================ */

#ifndef PTR_DBCORE_INSERT_H
#define PTR_DBCORE_INSERT_H

int ptr_insert_report(
    const char *report_type,
    const char *title,
    const char *description,
    const char *steps,
    const char *expected,
    const char *actual,
    const char *email
);

#endif
