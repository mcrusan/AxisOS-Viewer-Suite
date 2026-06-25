/* ============================================================
 *   FILE: pp_ptr_list.c
 *   SYSTEM: AxisOS
 *   SUBSYSTEM: PP-CLI / PTR Commands
 *   AUTHOR: Marc + PP (Co‑Pilot)
 *   CREATED: 2026-06-06
 *   VERSION: 1.0
 *   PURPOSE:
 *       Implements the "pp ptr list" command for PP-CLI.
 *       Retrieves PTR_Reports from dbcore and prints them in a
 *       clean, readable table format. This is the primary
 *       developer-facing view into the PTR system.
 *
 *   NOTES:
 *       - Fully SOP compliant.
 *       - Uses SQLite prepared statements.
 *       - Output formatted for terminal readability.
 *       - Future enhancement: filters, pagination, severity sort.
 *   ============================================================ */

#include <stdio.h>
#include <sqlite3.h>
#include "pp_ptr_list.h"
#include "../include/global.h"

/* ------------------------------------------------------------
 *   FUNCTION: pp_ptr_list
 *   PURPOSE:
 *       Lists all PTR reports in a formatted table.
 *   ------------------------------------------------------------ */
void pp_ptr_list() {

    sqlite3 *db;
    sqlite3_stmt *stmt;

    if (sqlite3_open("dbcore.sqlite", &db) != SQLITE_OK) {
        fprintf(stderr, "PP-CLI: dbcore open failed: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql =
    "SELECT report_id, report_type, title, severity, status, submitted_at "
    "FROM PTR_Reports ORDER BY report_id DESC;";

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
            fprintf(stderr, "PP-CLI: prepare failed: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        printf("\n");
        printf("============================================================\n");
        printf("  AXISOS PTR REPORTS (Newest First)\n");
        printf("============================================================\n");
        printf(" ID   | TYPE        | SEVERITY | STATUS       | TITLE\n");
        printf("------------------------------------------------------------\n");

        while (sqlite3_step(stmt) == SQLITE_ROW) {

            int id = sqlite3_column_int(stmt, 0);
            const unsigned char *type = sqlite3_column_text(stmt, 1);
            const unsigned char *title = sqlite3_column_text(stmt, 2);
            const unsigned char *severity = sqlite3_column_text(stmt, 3);
            const unsigned char *status = sqlite3_column_text(stmt, 4);

            printf(" %-4d | %-10s | %-8s | %-12s | %s\n",
                   id,
                   type ? type : "",
                   severity ? severity : "",
                   status ? status : "",
                   title ? title : ""
            );
        }

        printf("------------------------------------------------------------\n");
        printf(" PP-CLI: End of PTR list.\n\n");

        sqlite3_finalize(stmt);
        sqlite3_close(db);
}
