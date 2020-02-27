# Don't print the commands unless explicitely requested with `make V=1`
ifneq ($(V),1)
Q = @
V = 0
endif

# Compiler
CXX := g++
CXX_FLAGS := -Wall -Werror -std=c++11

# Current directory
CUR_PWD := $(shell pwd)

# Main program
program := main.out
objs := main.o
matlib := -I matrix.h

# Include path
MATLIB := matlib
MATLIB_PATH := $(MATLIB)
INCLUDE := -I $(MATLIB_PATH)

all: $(program)

# Rule for main program
$(program): $(objs)
	@echo "MAKE     $@"
	$(Q)$(CXX) $(CXX_FLAGS) -o $@ $<

# Generic rule for compiling objects
%.o: %.cpp
	@echo "CXX       $@"
	$(Q)$(CXX) $(CXX_FLAGS) $(INCLUDE) -c -o $@ $<

# Cleaning rule
clean:
	@echo "CLEAN    $(CUR_PWD)"
	$(Q)rm -f $(program) $(objs)

.PHONY: clean $(program)