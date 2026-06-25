/* ============================================================
 *   FILE: pp_ptr_view.c
 *   SYSTEM: AxisOS
 *   SUBSYSTEM: PP-CLI / PTR Commands
 *   AUTHOR: Marc + PP (Co‑Pilot)
 *   CREATED: 2026-06-06
 *   VERSION: 1.0
 *   PURPOSE:
 *       Implements the "pp ptr view <id>" command for PP-CLI.
 *       Retrieves a single PTR_Reports entry from dbcore and
 *       prints full details in a readable, structured format.
 *
 *   NOTES:
 *       - Fully SOP compliant.
 *       - Uses SQLite prepared statements.
 *       - Output formatted for terminal readability.
 *       - Future enhancement: JSON export, PP-CLI piping.
 *   ============================================================ */

#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include "pp_ptr_view.h"
#include "../include/global.h"

/* ------------------------------------------------------------
 *   FUNCTION: pp_ptr_view
 *   PURPOSE:
 *       Displays full details for a single PTR report.
 *   ------------------------------------------------------------ */
void pp_ptr_view(int report_id) {

    sqlite3 *db;
    sqlite3_stmt *stmt;

    if (sqlite3_open("dbcore.sqlite", &db) != SQLITE_OK) {
        fprintf(stderr, "PP-CLI: dbcore open failed: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql =
    "SELECT report_id, report_type, title, description,"
    " steps_to_reproduce, expected_behavior, actual_behavior,"
    " severity, status, user_email, submitted_at, updated_at "
    "FROM PTR_Reports WHERE report_id = ?;";

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
            fprintf(stderr, "PP-CLI: prepare failed: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_int(stmt, 1, report_id);

        if (sqlite3_step(stmt) != SQLITE_ROW) {
            printf("PP-CLI: No PTR report found with ID %d\n", report_id);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        printf("\n============================================================\n");
        printf("  AXISOS PTR REPORT #%d\n", sqlite3_column_int(stmt, 0));
        printf("============================================================\n");

        printf(" Type:        %s\n", sqlite3_column_text(stmt, 1));
        printf(" Severity:    %s\n", sqlite3_column_text(stmt, 7));
        printf(" Status:      %s\n", sqlite3_column_text(stmt, 8));
        printf(" Submitted:   %s\n", sqlite3_column_text(stmt, 10));
        printf(" Updated:     %s\n", sqlite3_column_text(stmt, 11));
        printf(" Email:       %s\n", sqlite3_column_text(stmt, 9));
        printf("\n");

        printf(" Title:\n   %s\n\n", sqlite3_column_text(stmt, 2));

        printf(" Description:\n   %s\n\n", sqlite3_column_text(stmt, 3));

        const unsigned char *steps = sqlite3_column_text(stmt, 4);
        if (steps && strlen((const char*)steps) > 0) {
            printf(" Steps to Reproduce:\n   %s\n\n", steps);
        }

        const unsigned char *expected = sqlite3_column_text(stmt, 5);
        if (expected && strlen((const char*)expected) > 0) {
            printf(" Expected Behavior:\n   %s\n\n", expected);
        }

        const unsigned char *actual = sqlite3_column_text(stmt, 6);
        if (actual && strlen((const char*)actual) > 0) {
            printf(" Actual Behavior:\n   %s\n\n", actual);
        }

        printf("============================================================\n");
        printf(" PP-CLI: End of report.\n\n");

        sqlite3_finalize(stmt);
        sqlite3_close(db);
}
