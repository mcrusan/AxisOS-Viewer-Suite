# -----------------------------------------------------------------------------
# File:        README.md
# Description: Official technical documentation for Crusan & Co. AxisOS™ Viewer Suite — Dual-Pane Binary Inspection Tooling (Hex, Octal, Binary & ASCII).
# Author:      Marc F. Crusan (MFC) / Crusan & Co. w/ PP & AGY (AXEL)
# Date:        2026111501
# Version:     v1.3.1-Silicon
# -----------------------------------------------------------------------------
# 2026111501 (MFC/AGY) Converted header to canonical # 5-Field SOP format and added GitHub Sponsors badge & link.
# 2026110901 (MFC/PP/AGY) Promoted root README.md with canonical 5-Field SOP Header & Crusan & Co. IP/Trademark notice.
# 2026062301 (MFC/PP) Standardized AxisOS Viewer Suite v1.2 documentation.

# Crusan & Co. — AxisOS™ Viewer Suite (`axis-view-gui`)
### **Deterministic C / GTK3 Dual-Pane Binary Inspector (Hex, Octal, Binary & Synchronized ASCII) with Hot-Loadable Plugin ABI**

[![Pillars: HONEST • AUDITABLE • OWNED](https://img.shields.io/badge/AxisOS%E2%84%A2-HONEST%20%E2%80%A2%20AUDITABLE%20%E2%80%A2%20OWNED-brightgreen.svg)](https://axisos.pro)
[![Language: C / GTK3](https://img.shields.io/badge/Stack-Pure%20C%20%E2%80%A2%20GTK3%20%E2%80%A2%20GModule-blue.svg)](hex-viewer/Makefile)
[![Company: Crusan & Co.](https://img.shields.io/badge/Company-Crusan%20%26%20Co.-gold.svg)](https://crusan.net)
[![Sponsor @mcrusan](https://img.shields.io/badge/Sponsor-%40mcrusan-ea4aaa?logo=githubsponsors)](https://github.com/sponsors/mcrusan)

**Parent Enterprise:** Crusan & Co.  
**Flagship Platform:** **AxisOS™** (*U.S. Trademark Application Serial No. `99878469`*)  
**Architect:** Marc F. Crusan (w/ Pocket Professor & AGY)  
**Website:** [https://axisos.pro](https://axisos.pro)  
**Sponsor Open-Source R&D:** [https://github.com/sponsors/mcrusan](https://github.com/sponsors/mcrusan)  

> **Intellectual Property & Proprietary Core Exclusion Notice:** This repository provides the **AxisOS™ Viewer Suite (`axis-view-gui`)** desktop binary inspection utility and `AxisPluginInfo` shared-object plugin ABI engineered by **Crusan & Co.** The underlying **AxisOS™ Native Bare-Metal Kernel** (`axisos-kernel.img`), the **freestanding C99 direct kernel syscall userland** (`svc #0`), the **Sovereign Seven (`Sov-7`)** autonomous embedded daemon suite, `RAMGAK` deterministic memory bracket tooling, and commercial AxisOS™ hardware distributions remain the exclusive, proprietary intellectual property of **Crusan & Co.** (Marc F. Crusan). All Rights Reserved.

---

## 1. Overview

The **AxisOS™ Viewer Suite** is a dual-pane binary inspection workbench built in C for deterministic byte-level verification of kernel images, ELF executables, UF2 microcontroller payloads, and raw disk sectors.

It includes:
- **Hex Viewer** — 16-byte aligned hexadecimal inspection pane
- **Octal Viewer** — Octal-formatted numeric inspection pane
- **Binary Viewer** — Bit-level binary inspection pane
- **Synchronized ASCII Gutter** — Lock-step vertical scrolling and selection sync (`viewer_selection_sync.c`)
- **AxisOS Plugin ABI v1.0** — Runtime dynamic `.so` plugin discovery via `GModule` (`plugin.c`)

---

## 2. Repository Layout

```text
hex-viewer/
├── Makefile                    # Primary C / GTK3 build specification
├── Auto_discover.Makefile      # Automatic module discovery build rules
├── include/                    # Header files (viewer.h, plugin.h, pp_ptr_list.h, etc.)
├── src/                        # C implementation modules (viewer.c, gui_wrapper.c, etc.)
├── plugins/                    # Hot-loadable shared-object plugins (hello_plugin.c)
├── doc/                        # Onboarding Guide, SOP v1.2, and Privacy Policy
└── res/                        # Crusan & Co. / AxisOS™ icons and workbench screenshots
```

---

## 3. Building & Running

### Prerequisites
- `gcc` or `clang`
- `gtk+-3.0` & `gmodule-2.0` (`pkg-config`)

### Compile & Launch
```bash
cd hex-viewer
make
./bin/axis-view-gui <filename>
```

---

## 4. Plugin ABI (`AxisPluginInfo`)

Shared-object plugins placed in `hex-viewer/plugins/` are discovered automatically at runtime and mounted under the **Plugins** menu:

```c
typedef struct {
    const char *name;
    const char *description;
    void (*run)(GtkWidget *parent);
} AxisPluginInfo;

AxisPluginInfo *plugin_info(void);
```

---

**Copyright © 2026 Crusan & Co. (Marc F. Crusan). All Rights Reserved.**  
**AxisOS™** is a trademark of Crusan & Co. (*U.S. Trademark Application Serial No. `99878469`*).
