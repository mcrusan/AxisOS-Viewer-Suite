# -----------------------------------------------------------------------------
# File:        hex-viewer/Makefile
# Description: Build rules for Crusan & Co. AxisOS Viewer Suite (axis-view-gui) binary & plugins.
# Author:      Marc F. Crusan (MFC) / Crusan & Co. w/ PP & AGY (AXEL)
# Date:        2026111816
# Version:     v1.3.0-Silicon
# -----------------------------------------------------------------------------
# 2026111816 (MFC/AGY) Enforced canonical 5-Field SOP Header and added -ffile-prefix-map for clean-room reproducible binaries.
# 2026060401 (MFC/PP) Initial Makefile with obj/ & plugin auto-build rules.

CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -ffile-prefix-map=$(CURDIR)=. -fPIC `pkg-config --cflags gtk+-3.0`
LDFLAGS := `pkg-config --libs gtk+-3.0 gmodule-2.0`

INCLUDES := -Iinclude

# Core Viewer Suite sources
SRC := \
    src/main.c \
    src/gui_wrapper.c \
    src/viewer.c \
    src/about.c \
    src/syntax_highlighter.c \
    src/viewer_offsets.c \
    src/viewer_geometry.c \
    src/viewer_geometry_utils.c \
    src/viewer_metrics.c \
    src/viewer_selection_sync.c \
    src/ascii_color.c


OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

# Plugin sources (any .c file in plugins/)
# PLUGIN_SRC := $(wildcard plugins/*.c)
# PLUGIN_OBJ := $(patsubst plugins/%.c,obj/plugins/%.o,$(PLUGIN_SRC))
# PLUGIN_SO  := $(patsubst plugins/%.c,plugins/%.so,$(PLUGIN_SRC))

BIN := bin/axis-view-gui

all: $(BIN) $(PLUGIN_SO)

# Build main binary
$(BIN): $(OBJ)
	@mkdir -p bin
	$(CC) -o $@ $^ $(LDFLAGS)

# Core object build rule
obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Plugin object build rule
obj/plugins/%.o: plugins/%.c
	@mkdir -p obj/plugins
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Plugin shared library build rule
plugins/%.so: obj/plugins/%.o
	$(CC) -shared -o $@ $^ $(LDFLAGS)

clean:
	rm -f obj/*.o obj/plugins/*.o $(BIN) plugins/*.so

.PHONY: all clean
