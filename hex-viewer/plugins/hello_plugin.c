/*==============================================================================
 *  FILE:        hello_plugin.c
 *  PROJECT:     AxisOS — Viewer Suite
 *  PURPOSE:     Demonstration plugin for FreshStart+ Plugin API v1
 *
 *  AUTHOR:      Marc (MFC)
 *  CREATED:     2026-06-07
 *  VERSION:     1.0
 *
 *  NOTES:
 *      - Shows how to register a plugin
 *      - Demonstrates plugin_run() and plugin_destroy()
 *      - Uses host API helpers (fs_api_show_output, fs_api_log)
 *
 *============================================================================*/

#include <gtk/gtk.h>
#include "../include/plugin.h"

/*────────────────────────────────────────────────────────────────────────────*/
/*  PLUGIN_INIT — runs automatically via constructor on dlopen()              */
/*────────────────────────────────────────────────────────────────────────────*/

__attribute__((constructor))
PLUGIN_INIT
{
    PLUGIN_REGISTER("Hello Plugin",
                    "1.0",
                    "Demonstration plugin for AxisOS Viewer Suite");
}

/*────────────────────────────────────────────────────────────────────────────*/
/*  freshstart_plugin_run — called when user activates plugin                 */
/*────────────────────────────────────────────────────────────────────────────*/

void freshstart_plugin_run(const gchar *args)
{
    (void)args;

    fs_api_log(FS_LOG_INFO, "Hello Plugin: run invoked");

    fs_api_show_output(
        "Hello from the Hello Plugin!\n"
        "This plugin is running inside the AxisOS Viewer Suite.\n"
        "\n"
        "Args passed: (none)\n"
    );
}

/*────────────────────────────────────────────────────────────────────────────*/
/*  freshstart_plugin_destroy — optional cleanup on unload                    */
/*────────────────────────────────────────────────────────────────────────────*/

void freshstart_plugin_destroy(void)
{
    fs_api_log(FS_LOG_INFO, "Hello Plugin: destroy invoked");
}
