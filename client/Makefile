
# Project Configuration
TARGET      := build/main
SRC_DIR     := src
INCLUDE_DIR := include
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/obj

# Compilers
CC  := clang
CXX := clang++
AS  := clang

# Compiler Flags
WARNINGS := -Wall -Wextra -Wpedantic

CFLAGS   := -std=c23 $(WARNINGS) -I$(INCLUDE_DIR) -MMD -MP
CXXFLAGS := -std=c++23 $(WARNINGS) -I$(INCLUDE_DIR) -MMD -MP
ASFLAGS  := -I$(INCLUDE_DIR) -MMD -MP

LDFLAGS  :=
LDLIBS   := -lcurses

# Source Discovery
C_SOURCES   := $(shell find $(SRC_DIR) -type f -name '*.c')
CPP_SOURCES := $(shell find $(SRC_DIR) -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' \))
ASM_SOURCES := $(shell find $(SRC_DIR) -type f \( -name '*.s' -o -name '*.S' \))

# Object Files
C_OBJECTS   := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.c.o,$(C_SOURCES))
CPP_OBJECTS := $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(patsubst $(SRC_DIR)/%,%,$(CPP_SOURCES))))
ASM_OBJECTS := $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(patsubst $(SRC_DIR)/%,%,$(ASM_SOURCES))))

OBJECTS := $(C_OBJECTS) $(CPP_OBJECTS) $(ASM_OBJECTS)
DEPS    := $(OBJECTS:.o=.d)

# Linker Selection
ifneq ($(strip $(CPP_SOURCES)),)
LINKER := $(CXX)
else
LINKER := $(CC)
endif

# Targets
.PHONY: all clean run rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(LINKER) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

# C Compilation
$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# C++ Compilation
$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.cc.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.cxx.o: $(SRC_DIR)/%.cxx
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Assembly Compilation
$(OBJ_DIR)/%.s.o: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(AS) -c $< -o $@

$(OBJ_DIR)/%.S.o: $(SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# Run
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Rebuild
rebuild:
	$(MAKE) clean
	$(MAKE) all

# Header Dependencies
-include $(DEPS)
