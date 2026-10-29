# OS detection

ifeq ($(OS), Windows_NT)
    DETECTED_OS := $(OS)
else
    DETECTED_OS := $(shell uname -s)
endif

# Build configuration

CC     ?= gcc
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

# Flags

INC_FLAGS  := $(foreach D,$(SRC_DIRS),-I$(D))
DEP_FLAGS  := -MMD -MP
C_STANDARD := -std=c2x

WARN_FLAGS := \
    -Wall \
    -Wextra \
    -Wpedantic \
    -Wshadow \
    -Wformat=2 \
    -Wstrict-prototypes \
    -Wmissing-prototypes

ifeq ($(CONFIG), release)
    CONFIG_FLAGS += -O2
else ifeq ($(CONFIG), debug)
    CONFIG_FLAGS += -O0 -g
else
    $(error Invalid CONFIG value: $(CONFIG). Use 'release' or 'debug'.)
endif

DEFAULT_CPPFLAGS := $(INC_FLAGS) $(DEP_FLAGS)
DEFAULT_CFLAGS   := $(C_STANDARD) $(WARN_FLAGS) $(CONFIG_FLAGS)
DEFAULT_LDFLAGS  :=
DEFAULT_LDLIBS   := -lncurses

ifeq ($(DETECTED_OS), Windows_NT)
    DEFAULT_CPPFLAGS += -DNCURSES_STATIC
endif

CPPFLAGS ?= $(DEFAULT_CPPFLAGS)
CFLAGS   ?= $(DEFAULT_CFLAGS)
LDFLAGS  ?= $(DEFAULT_LDFLAGS)
LDLIBS   ?= $(DEFAULT_LDLIBS)

# Targets

.PHONY: all clean

all: $(BINARY)

$(BINARY): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Include dependencies

-include $(DEP_FILES)

