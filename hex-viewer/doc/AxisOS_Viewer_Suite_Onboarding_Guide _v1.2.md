/* -----------------------------------------------------------------------------
   File:        AxisOS_Viewer_Suite_Onbording_Guide_v1.2.md
   Project:     AxisOS Viewer Suite
   Description: Dual‑pane binary inspection tools (Hex, Octal, Binary, ASCII)
   Author:      Marc F Crusan / PP
   Date:        20260623
   Version:     v1.2
   SOP:         Fully compliant with SOP v1.2
   ----------------------------------------------------------------------------- */

# **AxisOS Viewer Suite — Onboarding Guide (v1.2)**
### *Welcome to the Viewer Suite lineage.*

This guide brings a new developer from zero → productive with the Viewer Suite in the shortest possible time, while preserving the discipline and standards that keep AxisOS clean, predictable, and drift‑free.

---

## ⭐ 1. What the Viewer Suite *is*
The Viewer Suite is a **dual‑pane binary inspection tool** built for AxisOS.
It provides:

- **Hex / Octal / Binary** numeric views
- **ASCII** side‑by‑side representation
- **Synchronized scrolling**
- **Plugin support**
- **Hot‑reload‑safe architecture**
- **SOP‑compliant codebase**

It is the first “user‑facing” tool in the AxisOS micro‑enterprise stack.

---

## ⭐ 2. Repository Layout
Every file lives in a predictable place:

```
viewer_files/
    include/                # All headers
    src/                    # All .c modules
    plugins/                # Optional .so plugins
    bin/                    # Build output
    Makefile                # Build rules
```

### Key modules
- **viewer.c / viewer.h** — file loading + numeric/ASCII rendering
- **gui_wrapper.c** — main window, menus, toolbar, dual‑pane layout
- **syntax_highlighter.c** — address column highlighting
- **plugin_loader.c** — dynamic plugin discovery
- **about.c** — About dialog
- **main.c** — entry point

Everything is SOP v1.2 aligned.

---

## ⭐ 3. Build Requirements
### Dependencies
- GTK+ 3
- GModule
- pkg‑config
- GCC or Clang

### Build command
From the project root:

```
make
```

Binary appears at:

```
bin/axis-view-gui
```

Run it from a terminal to see debug output.

---

## ⭐ 4. SOP v1.2 — The Rules You Must Follow
Every module in the Viewer Suite follows the same 10‑point SOP:

1. Must compile cleanly with `-Wall -Wextra`.
2. No ambiguous memory ownership.
3. No silent failures.
4. No undocumented global state.
5. Must use the **dual‑pane architecture**.
6. Must include the full SOP header.
7. Must be readable and free of drift.
8. Must produce deterministic output.
9. Plugins must follow the AxisOS Plugin ABI.
10. No animals harmed. PP may be inconvenienced.

This is the backbone of the project.

---

## ⭐ 5. Dual‑Pane Architecture (Core Concept)

The Viewer Suite is built around a strict, predictable layout:

- **Left pane:** Numeric view (Hex/Oct/Bin)
- **Right pane:** ASCII view
- **Shared vertical adjustment** ensures perfect sync
- **Monospace fonts only**
- **Consistent margins**

This is non‑negotiable.
Every viewer SKU (Hex, Oct, Bin, Pro, Pro+) must follow it.

---

## ⭐ 6. Rendering Pipeline
When a file is opened:

1. `viewer_render_file()` loads the file
2. It formats each 16‑byte block
3. It writes numeric output to `hex_buf`
4. It writes ASCII output to `ascii_buf`
5. Syntax highlighter tags the address column
6. GTK updates both panes simultaneously

The pipeline is deterministic and reproducible.

---

## ⭐ 7. Plugin System
Plugins live in:

```
./plugins/
```

Each plugin must export:

```c
AxisPluginInfo *plugin_info(void);
```

And return:

```c
typedef struct {
    const char *name;
    const char *description;
    void (*run)(GtkWidget *parent);
} AxisPluginInfo;
```

Plugins appear automatically under the **Plugins** menu.

---

## ⭐ 8. Debugging the Viewer
### Allocation Debug
To inspect pane widths:

```c
g_signal_connect(hex_view,   "size-allocate",
                 G_CALLBACK(debug_allocation), "HEX_VIEW");
g_signal_connect(ascii_view, "size-allocate",
                 G_CALLBACK(debug_allocation), "ASCII_VIEW");
```

Run from terminal to see:

```
[ALLOC] HEX_VIEW     width=780
[ALLOC] ASCII_VIEW   width=360
```

This is essential when GTK misbehaves.

---

## ⭐ 9. Common Pitfalls (and how to avoid them)

### ❌ Pane collapse
Cause: ASCII view natural width too small
Fix: `gtk_widget_set_size_request(ascii_scroll, 360, -1);`

### ❌ Plugins not loading
Cause: missing `plugin_info` symbol
Fix: ensure plugin exports correct ABI

### ❌ Drift between modules
Cause: missing SOP header
Fix: copy the canonical header block

### ❌ Viewer looks “off”
Cause: missing monospace font
Fix: `gtk_text_view_set_monospace(view, TRUE);`

---

## ⭐ 10. How to Add a New Feature
Every new feature must:

- follow SOP v1.2
- avoid global state unless justified
- maintain dual‑pane architecture
- include full header block
- compile cleanly
- avoid regressions

If a feature touches layout, run allocation debug.

---

## ⭐ 11. How to Add a New Plugin
1. Create `plugins/myplugin.c`
2. Implement `plugin_info()`
3. Build with:

```
gcc -shared -fPIC -o plugins/myplugin.so myplugin.c `pkg-config --cflags --libs gtk+-3.0`
```

4. Restart viewer
5. Plugin appears automatically

---

## ⭐ 12. How to Ship a Release
A release must include:

- `bin/axis-view-gui`
- `include/`
- `src/`
- `plugins/`
- `Makefile`
- `README.md`
- `SOP_v1.2.md` (this document)

Version bump only when architecture changes.

---

## ⭐ 13. Culture & Philosophy
AxisOS development is built on:

- craftsmanship
- clarity
- discipline
- zero drift
- mythos
- humor
- and the occasional cookie 🍪 reward

You’re not just writing code — you’re adding to a lineage.

---

## ⭐ 14. Final Words for New Developers
Welcome to the Viewer Suite.
This is a small codebase, but it’s built with the same care you’d give a spacecraft or a handmade pen.

If you follow SOP v1.2, you’ll never get lost.
If you drift, the system will tell you.
If you break something, we fix it together.
