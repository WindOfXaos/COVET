.DEFAULT_GOAL := all
# Third-party sources
include vendor/vendor.mk
# Source sources
include src/src.mk
# Test sources
include test/test.mk

# Project Name
EXE = COVET

# Directories
BUILDDIR = build
BINDIR = bin

# Object and dependency files
OBJS := $(SRCS:%.cpp=$(BUILDDIR)/%.o)
DEPS := $(SRCS:%.cpp=$(BUILDDIR)/%.d)

# Compiler:
CXX = g++

#Linker:
LD  = g++

# -MMD and -MP asks clang++ to generate a .d file listing the headers used in the source code for use in the Make process.
DEPFLAGS = -MMD -MP

# Provide lots of helpful warning/errors:
WARNINGS = -pedantic -Wall -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable

# Flags for compile:
CXXFLAGS = -std=c++17 -g -c -O0 $(WARNINGS) $(DEPFLAGS) $(INCDIR)

# Flags for libraries
LIBS = --static -Llib -lpthread -lglfw3

##-------------------------
## BUILD FLAGS PER PLATFORM
##-------------------------

ifeq ($(OS), Windows_NT) #Windows
	LIBS += -lgdi32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux) #LINUX
		LIBS += -lGL
	endif
endif

# Flags for linking:
LDFLAGS =  $(LIBS)

all: $(EXE)

# Rule for creating build directories:
# Matches %.folder patterns AKA directories
# $(@D) to get file directory
%.folder:
	@mkdir -p "$(BUILDDIR)/$(@D)"
	@mkdir -p "$(BINDIR)"

# Rule for linking the final executable:
# - $(EXE) depends on all object files in $(OBJS)
$(EXE): $(OBJS)
	@echo " Linking..."
	$(LD) $^ $(LDFLAGS) -o $(BINDIR)/$@

# Rules for compiling source code:
# - Compile object files required by $(EXE) one by one
# - %.folder Here we add '.folder' to match build directories rule
$(BUILDDIR)/%.o: %.cpp | %.folder
	$(CXX) $(CXXFLAGS) $< -o $@
$(BUILDDIR)/%.o: %.c | %.folder
	$(CXX) $(CXXFLAGS) $< -o $@

# Rule for linking test files except main.cpp:
$(TEST): $(filter-out %main.o, $(OBJS)) $(TESTOBJS)
	@echo " Testing..."
	$(LD) $^ $(LDFLAGS) -o $(BINDIR)/$@
	cd "$(BINDIR)"; ./$@ -s -d

clean:
	@echo " Cleaning..."
	rm -rf $(BINDIR)/$(EXE) $(BINDIR)/$(TEST) $(BUILDDIR)/*

.PHONY: all test clean

# Additional dependencies for object files are included in the clang++
# generated .d files (from -MD -MP):
-include $(DEPS)
