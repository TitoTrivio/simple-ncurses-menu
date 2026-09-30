# OS detection

ifeq ($(OS), Windows_NT)
    DETECTED_OS := $(OS)
else
    DETECTED_OS := $(shell uname -s)
endif

# Build configuration

CC ?= gcc

CONFIG ?= debug

# Project configuration

TARGET := simple_ncurses_menu

BUILD_DIR := build/$(CONFIG)
BIN_DIR   := bin/$(CONFIG)
SRC_DIRS  := src

ifeq ($(DETECTED_OS), Windows_NT)
    BINARY := $(BIN_DIR)/$(TARGET).exe
else
    BINARY := $(BIN_DIR)/$(TARGET)
endif

# Files

SRC_FILES := $(foreach D,$(SRC_DIRS),$(wildcard $(D)/*.c))
OBJ_FILES := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES := $(patsubst %.c,$(BUILD_DIR)/%.d,$(SRC_FILES))

EXTERNAL_LIBRARIES := ncurses tinfo

# Flags

INC_FLAGS  := $(foreach D,$(SRC_DIRS),-I$(D))
LIB_FLAGS  := $(foreach LIB,$(EXTERNAL_LIBRARIES),-l$(LIB))
DEP_FLAGS  := -MMD -MP
C_STANDARD := -std=c23
WARN_FLAGS := \
    -Wall \
    -Wextra \
    -Wpedantic \
    -Wshadow \
    -Wformat=2 \
    -Wstrict-prototypes \
    -Wmissing-prototypes

CPPFLAGS := $(INC_FLAGS) $(DEP_FLAGS)
CFLAGS   := $(C_STANDARD) $(WARN_FLAGS)
LDFLAGS  := $(LIB_FLAGS)

ifeq ($(CONFIG), release)
    CFLAGS += -O2
else ifeq ($(CONFIG), debug)
    CFLAGS += -O0 -g
else
    $(error Invalid CONFIG value: $(CONFIG). Use 'release' or 'debug'.)
endif

# Targets

all: $(BINARY)

$(BINARY): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean

# Include dependencies

-include $(DEP_FILES)

