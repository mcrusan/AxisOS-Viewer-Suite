/* -----------------------------------------------------------------------------
   File:        AxisOS_Viewer_Suite_README_v1.2.md
   Project:     AxisOS Viewer Suite
   Description: Dual‑pane binary inspection tools (Hex, Octal, Binary, ASCII)
   Author:      Marc F Crusan / PP
   Date:        20260623
   Version:     v1.2
   SOP:         Fully compliant with SOP v1.2
   ----------------------------------------------------------------------------- */
# *“AxisOS™ micro-enterprise solutions”*
# **AxisOS Viewer Suite — README.md (v1.2)**
*A dual‑pane binary inspection tool for AxisOS.*

---

## ⭐ Overview
The **AxisOS Viewer Suite** is a GTK‑based, dual‑pane binary viewer designed for micro‑enterprise tooling within the AxisOS ecosystem.  
It provides synchronized numeric and ASCII views, plugin extensibility, and a clean, deterministic rendering pipeline.

The suite includes:

- **Hex Viewer** — primary binary inspector  
- **Octal Viewer** — octal‑formatted numeric pane  
- **Binary Viewer** — bit‑level inspection  
- **ASCII Pane** — synchronized printable gutter  
- **Plugin System** — AxisOS Plugin ABI v1.0  

The Viewer Suite is built with craftsmanship, clarity, and strict SOP v1.2 compliance.

---

## ⭐ Features
- **Dual‑pane architecture**
  - Left: Hex / Octal / Binary
  - Right: ASCII
  - Shared vertical scrolling
- **Monospace rendering**
- **16‑byte line formatting**
- **Address column highlighting**
- **GTK3 UI with menus + toolbar**
- **Plugin system (AxisOS Plugin ABI v1.0)**
- **Hot‑reload‑safe modules**
- **SOP v1.2 standardized codebase**

---

## ⭐ Hex Viewer (Primary Component)
The Hex Viewer is the flagship tool of the suite.

### Capabilities
- Clean, aligned hex output  
- Printable ASCII gutter  
- 16 bytes per row  
- Smooth scrolling  
- Large‑file friendly  
- GTK‑based UI  

### Usage
```
bin/axis-view-gui <filename>
```

Or via menu:

- **File → Open → Hex View**

### Planned Enhancements
- Search functionality  
- Go‑to‑offset dialog  
- Highlighting ranges  
- Configurable bytes‑per‑row  
- Color themes  
- Drag‑and‑drop loading  

---

## ⭐ Project Structure
```
viewer_files/
    include/                # Header files
    src/                    # Source modules
    plugins/                # Optional .so plugins
    bin/                    # Build output
    Makefile                # Build rules
```

### Key Modules
- **viewer.c / viewer.h** — file loading + numeric/ASCII rendering  
- **gui_wrapper.c** — main window + dual‑pane layout  
- **syntax_highlighter.c** — address column highlighting  
- **plugin_loader.c** — dynamic plugin discovery  
- **about.c** — About dialog  
- **main.c** — application entry point  

---

## ⭐ Build Instructions
### Requirements
- GTK+ 3  
- GModule  
- pkg‑config  
- GCC or Clang  

### Build
From project root:

```
make
```

Binary appears at:

```
bin/axis-view-gui
```

Run from a terminal to see debug output.

---

## ⭐ Usage
Launch the viewer:

```
bin/axis-view-gui
```

### Open a file
Use:

- **File → Open → Hex View**  
- **File → Open → Octal View**  
- **File → Open → Binary View**  
- Or the toolbar buttons  

### Plugins
Plugins appear automatically under the **Plugins** menu.

---

## ⭐ Plugin Development
Plugins must export:

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

Place compiled `.so` files in:

```
./plugins/
```

They will be discovered automatically at runtime.

---

## ⭐ SOP v1.2 Compliance 
All modules must include the full SOP header and follow the 10‑point standard:

1. Clean compilation (`-Wall -Wextra`)
2. Clear memory ownership
3. No silent failures
4. No undocumented globals
5. Dual‑pane architecture
6. SOP header required
7. Readable, maintainable code
8. Deterministic output
9. Plugin ABI v1.0 compliance
10. No animals harmed

Full SOP included in `SOP_v1.2.md`.

---

## ⭐ Debugging
### Pane Allocation Debug
Attach to text views:

```c
g_signal_connect(hex_view,   "size-allocate",
                 G_CALLBACK(debug_allocation), "HEX_VIEW");
g_signal_connect(ascii_view, "size-allocate",
                 G_CALLBACK(debug_allocation), "ASCII_VIEW");
```

Run from terminal to see pane widths.

---

## ⭐ Versioning
- **1.0** — Prototype  
- **1.1** — Drift era  
- **1.2** — SOP standardization (current)  

---

## ⭐ Philosophy
The Viewer Suite is built with:

- craftsmanship  
- clarity  
- discipline  
- zero drift  
- humor  
- and the occasional cookie (🍪) reward 

This is more than a tool — it’s part of the AxisOS lineage.

---

## ⭐ License
AxisOS micro‑enterprise license.  
No animals harmed. PP mildly inconvenienced.
```

