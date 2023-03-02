PROGRAM=tolower
CXX ?= g++
INSTALL ?= install
RM ?= rm
PREFIX ?= /usr/local
BINDIR ?= bin
CXXFLAGS ?= -std=gnu++23 -march=native -O3 -pipe -D_FILE_OFFSET_BITS=64 -fdata-sections -ffunction-sections -Wall -Wextra -Wpedantic -Wl,--gc-sections -Wl,--print-gc-sections -Wl,-s -licuuc

ifdef _WIN32
OBJECT_EXT ?= .obj
EXECUTABLE_EXT ?= .exe
else
OBJECT_EXT ?= .o
EXECUTABLE_EXT ?= 
endif

all: $(PROGRAM)

tolower: $(PROGRAM)$(OBJECT_EXT)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(PROGRAM)$(OBJECT_EXT)

tolower$(OBJECT_EXT): $(PROGRAM).cpp
	$(CXX) $(CXXFLAGS) -c $(PROGRAM).cpp
clean:
	$(RM) -rf $(PROGRAM)$(OBJECT_EXT) $(PROGRAM)$(EXECUTABLE_EXT)

install: $(PROGRAM)
	$(INSTALL) -d $(PREFIX)/$(BINDIR)
	$(INSTALL) -m 755 $(PROGRAM)$(EXECUTABLE_EXT) $(PREFIX)/$(BINDIR)

uninstall: $(PROGRAM)
	$(RM) -rf $(PREFIX)/$(BINDIR)/$(PROGRAM)$(EXECUTABLE_EXT)
