#===============================================================================
#  FILE:        Makefile
#  PROJECT:     AxisOS — Viewer Suite
#  PURPOSE:     Build rules for axis-view-gui binary with obj/ directory.
#
#  AUTHOR:      Marc & PP (Pocket Professor)
#  CREATED:     2026-06-04
#  VERSION:     1.2
#===============================================================================
#===============================================================================
#  FILE:        Makefile
#  PROJECT:     AxisOS — Viewer Suite
#  PURPOSE:     Build rules for axis-view-gui + plugin auto-build (obj/ aware)
#===============================================================================

CC      := gcc
CFLAGS  := -Wall -Wextra -g -fPIC `pkg-config --cflags gtk+-3.0`
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
