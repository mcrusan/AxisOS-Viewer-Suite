/**
 * plugin.c — Plugin API: Dynamic .so Loading & Registration
 * Author  : Marc (MFC)
 * Project : FreshStart+  |  AxisOS
 * License : MIT
 *
 * From scratch doc page 6:
 *   gcc -fPIC -shared -o plugin_inspector.so plugin_inspector.c \
 *       `pkg-config --cflags --libs gtk+-3.0`
 */

#include "../include/plugin.h"
#include "../include/logger.h"
#include "../include/utils.h"

FsPlugin fs_plugin_registry[FS_PLUGIN_MAX];
int      fs_plugin_count = 0;

/* ── Load all .so files from FS_PLUGIN_DIR ───────────────────────────────── */
int fs_plugin_load_all(void)
{
    GDir   *dir = g_dir_open(FS_PLUGIN_DIR, 0, NULL);
    if (!dir) {
        FS_WARN("Plugin dir not found: " FS_PLUGIN_DIR);
        return 0;
    }
    const char *name;
    int loaded = 0;
    while ((name = g_dir_read_name(dir)) != NULL) {
        if (fs_util_str_ends_with(name, ".so")) {
            char path[FS_MAX_PATH];
            snprintf(path, sizeof(path), "%s/%s", FS_PLUGIN_DIR, name);
            if (fs_plugin_load(path) == 0) loaded++;
        }
    }
    g_dir_close(dir);
    char msg[128];
    snprintf(msg, sizeof(msg), "🪝 Loaded %d plugin(s)", loaded);
    FS_LOG(msg);
    return loaded;
}

/* ── Load a single .so plugin ────────────────────────────────────────────── */
int fs_plugin_load(const char *so_path)
{
    if (fs_plugin_count >= FS_PLUGIN_MAX) {
        FS_WARN("Plugin registry full");
        return -1;
    }
    void *handle = dlopen(so_path, RTLD_NOW | RTLD_GLOBAL);
    if (!handle) {
        char msg[512];
        snprintf(msg, sizeof(msg), "❌ Plugin load failed: %s — %s", so_path, dlerror());
        FS_ERROR(msg);
        return -1;
    }
    /* The plugin's __attribute__((constructor)) runs automatically on dlopen,
     * calling fs_plugin_self_register() which fills registry entry */
    FsPlugin *p = &fs_plugin_registry[fs_plugin_count - 1];
    p->handle = handle;
    p->plugin_run = dlsym(handle, "plugin_run");

    char msg[256];
    snprintf(msg, sizeof(msg), "🪝 Plugin loaded: %s v%s — %s",
             p->name, p->version, p->description);
    FS_LOG(msg);
    return 0;
}

/* ── Called by PLUGIN_REGISTER macro inside plugin's PLUGIN_INIT ─────────── */
void fs_plugin_self_register(const char *name, const char *version, const char *desc)
{
    if (fs_plugin_count >= FS_PLUGIN_MAX) return;
    FsPlugin *p = &fs_plugin_registry[fs_plugin_count++];
    g_strlcpy(p->name,        name    ? name    : "unknown", sizeof(p->name));
    g_strlcpy(p->version,     version ? version : "0.0",     sizeof(p->version));
    g_strlcpy(p->description, desc    ? desc    : "",        sizeof(p->description));
}

/* ── Unload all plugins ───────────────────────────────────────────────────── */
void fs_plugin_unload_all(void)
{
    for (int i = 0; i < fs_plugin_count; i++) {
        if (fs_plugin_registry[i].handle)
            dlclose(fs_plugin_registry[i].handle);
    }
    fs_plugin_count = 0;
    FS_LOG("🪝 All plugins unloaded");
}

/* ── Invoke a plugin by name ─────────────────────────────────────────────── */
int fs_plugin_run(const char *name, const char *args)
{
    for (int i = 0; i < fs_plugin_count; i++) {
        if (strcmp(fs_plugin_registry[i].name, name) == 0) {
            if (fs_plugin_registry[i].plugin_run) {
                fs_plugin_registry[i].plugin_run(args);
                return 0;
            }
        }
    }
    FS_WARN("Plugin not found");
    return -1;
}

/* ── Plugin manager dialog ───────────────────────────────────────────────── */
void fs_plugin_show_manager(void)
{
    GtkWidget *dlg = gtk_dialog_new_with_buttons(
        "🪝 Plugin Manager", GTK_WINDOW(app->window),
        GTK_DIALOG_MODAL, "_Close", GTK_RESPONSE_CLOSE, NULL);
    gtk_window_set_default_size(GTK_WINDOW(dlg), 480, 320);

    GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dlg));
    GtkListStore *store = gtk_list_store_new(3,
        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    for (int i = 0; i < fs_plugin_count; i++) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, fs_plugin_registry[i].name,
            1, fs_plugin_registry[i].version,
            2, fs_plugin_registry[i].description, -1);
    }

    GtkWidget *tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    const char *cols[] = { "Name", "Version", "Description" };
    for (int i = 0; i < 3; i++) {
        GtkTreeViewColumn *col = gtk_tree_view_column_new_with_attributes(
            cols[i], gtk_cell_renderer_text_new(), "text", i, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree), col);
    }
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), tree);
    gtk_container_add(GTK_CONTAINER(content), scroll);

    if (fs_plugin_count == 0) {
        gtk_container_add(GTK_CONTAINER(content),
            gtk_label_new("No plugins loaded.\nPlace .so files in " FS_PLUGIN_DIR));
    }

    gtk_widget_show_all(dlg);
    gtk_dialog_run(GTK_DIALOG(dlg));
    gtk_widget_destroy(dlg);
}
