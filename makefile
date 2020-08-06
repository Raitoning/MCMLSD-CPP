# Makefile written by Raitoning
# Uses the same workflow as Visual Studio's C++ project
# Settings based on "The Cherno"'s recommended settings.
# (Channel: https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw)
# (Project setup video: https://www.youtube.com/watch?v=qeH9Xv_90KM)
# Version 1.1.3 (2020.08.06.19.34)

# Project settings
PROJECT_NAME=MCMLSD-CPP
PLATFORM=Linux

# Configuration is either Debug or Release
CONFIGURATION=Debug

# Paths to sources, binaries, libraries and intermediates files
SOURCES_DIR=src
BINARIES_DIR=bin
LIBRARIES_DIR=lib
BINARIES_OUTPUT_DIR=$(BINARIES_DIR)/$(PLATFORM)/$(CONFIGURATION)
INTERMEDIATES_DIR=$(BINARIES_DIR)/intermediates/$(PLATFORM)/$(CONFIGURATION)

# C++ compiler and flags
CXX=g++
OPENCV_LIBRARY=`pkg-config --cflags --libs opencv`
CXX_COMPILING_FLAGS=-Wall -std=c++11 -I $(LIBRARIES_DIR)
CXX_LINKING_FLAGS=$(CXX_COMPILING_FLAGS) $(OPENCV_LIBRARY)

# Object file to compile, use .o suffix
OBJECT_FILES=Main.o Math.o Kernel.o

# Source files for intermediates and debug purposes
SOURCE_FILES=$(patsubst %.o, %.cpp, $(OBJECT_FILES))

# Add optimization options in the Release configuration
ifeq ($(CONFIGURATION), Release)
	CXX_LINKING_FLAGS += -O2
	CXX_COMPILING_FLAGS += -O2
	else
	# Assume the configuration is Debug
	CONFIGURATION=Debug
	# Add debug symbols in the Debug configuration
	CXX_LINKING_FLAGS += -g
	CXX_COMPILING_FLAGS += -g
endif

$(info Compiling in $(CONFIGURATION) configuration for the $(PLATFORM) platform.)
$(info Intermediates folder is $(INTERMEDIATES_DIR).)
$(info Binaries folder is $(BINARIES_OUTPUT_DIR).)

# Handling the compilation of object files to the intermediate folder
%.o: %.cpp
	$(info $(shell mkdir -p $(INTERMEDIATES_DIR)))
	$(CXX) -c $< -o $(addprefix $(INTERMEDIATES_DIR)/, $(notdir $@)) $(CXX_COMPILING_FLAGS)

$(PROJECT_NAME): $(addprefix $(SOURCES_DIR)/, $(OBJECT_FILES))
	$(info $(shell mkdir -p $(BINARIES_OUTPUT_DIR)))
	$(CXX) $(addprefix $(INTERMEDIATES_DIR)/, $(notdir $^)) -o $(BINARIES_OUTPUT_DIR)/$@ $(CXX_LINKING_FLAGS)

.PHONY: clean intermediates all

# HACK: Overengineered rule, do not modify. Use at your own risk.
intermediates: $(addprefix $(SOURCES_DIR)/, $(SOURCE_FILES))

	$(info $(shell mkdir -p $(INTERMEDIATES_DIR)))

	$(foreach source, $(addprefix $(INTERMEDIATES_DIR)/, $(notdir $(addsuffix .i, $(basename $^)))), $(shell $(CXX) -E $(addprefix $(SOURCES_DIR)/, $(addsuffix .cpp, $(basename $(notdir $(source))))) -o $(source) $(CXX_COMPILING_FLAGS) ))
	$(foreach source, $(addprefix $(INTERMEDIATES_DIR)/, $(notdir $(addsuffix .asm, $(basename $^)))), $(shell $(CXX) -S $(addprefix $(SOURCES_DIR)/, $(addsuffix .cpp, $(basename $(notdir $(source))))) -o $(source) $(CXX_COMPILING_FLAGS) ))

	# $(CXX) -E $^ -o $(addprefix $(INTERMEDIATES_DIR)/, $(notdir $(addsuffix .i, $(basename $<)))) $(CXX_COMPILING_FLAGS)
	# $(CXX) -S $(patsubst %.o, %.cpp, $(SOURCES_DIR)/$(OBJECT_FILES)) -o  $(INTERMEDIATES_DIR)/$(basename $(notdir $^)).asm $(CXX_COMPILING_FLAGS)

clean:
	rm -rf $(addprefix ./, $(BINARIES_DIR))
	clear

all: $(PROJECT_NAME)

# Automatically generating output directories if they don't exit yet.
# https://stackoverflow.com/questions/1950926/create-directories-using-make-file/45048948#45048948
