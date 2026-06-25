/* ============================================================
 *   FILE: cli_args.c
 *   SYSTEM: AxisOS
 *   SUBSYSTEM: Editor / CLI Argument Parser
 *   AUTHOR: Marc + PP (Co‑Pilot)
 *   CREATED: 2026-06-06
 *   VERSION: 1.2
 *   PURPOSE:
 *       Handles command-line arguments for marc_editor.
 *       This parser is ONLY for the editor, not PP-CLI.
 *   ============================================================ */

#include "../include/global.h"

void print_help() {
    printf("Usage: axis-view-gui [options]\n");
    printf("Options:\n");
    printf("  -f <file>        Open a file\n");
    printf("  --help           Show this help message\n");
    printf("  -v | --version   Show editor version\n");
    printf("  -p <plugin>      Load a specific plugin\n");
    printf("  --debug          Enable debug mode\n");
}

int process_args(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;

        } else if (strcmp(argv[i], "-f") == 0 && (i + 1) < argc) {
            printf("Opening file: %s\n", argv[++i]);
            open_file(argv[i]);

        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            printf("Viewer Suite v1.1\n");

        } else if (strcmp(argv[i], "-p") == 0 && (i + 1) < argc) {
            printf("Loading plugin: %s\n", argv[++i]);

        } else if (strcmp(argv[i], "--debug") == 0) {
            printf("Debug mode enabled.\n");
            enable_debug_mode();

        } else {
            printf("Unknown option: %s\n", argv[i]);
            return -1;
        }
    }

    return 1;
}
