/**
 * plugin.h — FreshStart+ Plugin API v1
 * Author: Marc (MFC) | FreshStart+ / AxisOS
 *
 * Plugins are shared objects (.so) implementing these symbols.
 * Build: gcc -fPIC -shared -o myplugin.so myplugin.c \
 *           `pkg-config --cflags --libs gtk+-3.0`
 */
#ifndef PLUGIN_H
#define PLUGIN_H
#include "global.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ── Plugin Entry Points (implement these in your plugin .so) ── */

/**
 * PLUGIN_INIT — called once on dlopen().
 * Call PLUGIN_REGISTER() here to identify your plugin.
 */
#define PLUGIN_INIT         void freshstart_plugin_init(void)

/**
 * PLUGIN_REGISTER — registers name, version, description.
 * Called from within PLUGIN_INIT.
 */
#define PLUGIN_REGISTER(name, ver, desc) \
    _fs_plugin_register((name), (ver), (desc))
void _fs_plugin_register (const gchar *name, const gchar *version,
                          const gchar *description);

/**
 * plugin_run — called by Tools > Plugins > [YourPlugin].
 * args: space-separated arguments (may be NULL).
 */
void freshstart_plugin_run     (const gchar *args);

/**
 * plugin_destroy — called once on unload / app exit.
 */
void freshstart_plugin_destroy (void);

/* ── Plugin Manager (host side) ── */
gboolean  fs_plugin_load        (const gchar *so_path);
gboolean  fs_plugin_unload      (const gchar *name);
void      fs_plugin_unload_all  (void);
void      fs_plugin_discover    (void);       /* scans FS_PLUGINS_DIR */
FsPlugin *fs_plugin_find        (const gchar *name);
void      fs_plugin_run_named   (const gchar *name, const gchar *args);
GSList   *fs_plugin_list        (void);

/* ── Plugin API Helpers (available to plugins) ── */
GtkWidget *fs_api_get_window        (void);
GtkWidget *fs_api_get_active_view   (void);
gchar     *fs_api_get_active_text   (void);
void       fs_api_insert_text       (const gchar *text);
void       fs_api_log               (FsLogLevel level, const gchar *msg);
void       fs_api_run_db_command    (const gchar *sql);
void       fs_api_show_output       (const gchar *text);

#ifdef __cplusplus
}
#endif
#endif /* PLUGIN_H */
