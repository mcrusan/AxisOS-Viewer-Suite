# Auto-discover all .c files in src/
SRC := $(wildcard src/*.c)

# Convert to object files
OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))
