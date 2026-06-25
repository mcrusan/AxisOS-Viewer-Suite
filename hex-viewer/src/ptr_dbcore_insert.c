/* ============================================================
 *   FILE: ptr_dbcore_insert.c
 *   SYSTEM: AxisOS
 *   SUBSYSTEM: dbcore / PTR
 *   AUTHOR: Marc + PP (Co‑Pilot)
 *   CREATED: 2026-06-06
 *   VERSION: 1.0
 *   PURPOSE:
 *       Provides insertion routines for PTR_Reports and related
 *       tables inside dbcore. This module is called by the UI
 *       submission form (help_submission_form.c) and is the
 *       authoritative write-path for PTR intake.
 *
 *   NOTES:
 *       - Fully SOP compliant.
 *       - Uses SQLite prepared statements.
 *       - Safe against SQL injection.
 *       - Future hooks for PP-CLI triage tentacle included.
 *   ============================================================ */

#include <sqlite3.h>
#include <stdio.h>
#include "../include/ptr_dbcore_insert.h"
#include "../include/global.h"

/* ------------------------------------------------------------
 *   FUNCTION: ptr_insert_report
 *   PURPOSE:
 *       Inserts a Bug Report or Improvement Suggestion into
 *       PTR_Reports. Returns 1 on success, 0 on failure.
 *   ------------------------------------------------------------ */
int ptr_insert_report(
    const char *report_type,
    const char *title,
    const char *description,
    const char *steps,
    const char *expected,
    const char *actual,
    const char *email
)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    if (sqlite3_open("dbcore.sqlite", &db) != SQLITE_OK) {
        fprintf(stderr, "dbcore open failed: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *sql =
    "INSERT INTO PTR_Reports ("
    " report_type, title, description, steps_to_reproduce,"
    " expected_behavior, actual_behavior, user_email"
    ") VALUES (?, ?, ?, ?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "prepare failed: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, report_type, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, title, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, description, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, steps, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, expected, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, actual, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, email, -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return (rc == SQLITE_DONE);
}
