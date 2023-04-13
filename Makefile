PROJECTNAME=raycaster

PLATFORM?=native
BUILDTYPE?=debug
CC?=
CFLAGS?=-Wall -std=c11 -I include -I third-party/glad/include -I third-party/stb/include -I third-party/cglm/include
LDFLAGS?=-lglfw3
ASSETSDIR=assets
EXECUTABLE=$(BINDIR)/$(PROJECTNAME)
BUILDDIR?=bin
BINDIR=$(BUILDDIR)/$(PLATFORM)

ifeq ($(PLATFORM),native)
	CC=clang
else ifeq ($(PLATFORM),web)
	CC=emcc
	EXECUTABLE=$(BINDIR)/$(PROJECTNAME).html
endif

ifeq ($(BUILDTYPE),debug)
	CFLAGS += -g
else ifeq ($(BUILDTYPE),release)
	CFLAGS += -O1
endif

SRCDIRS=src third-party/glad/src third-party/stb/src third-party/cglm/src
SOURCES=$(shell find $(SRCDIRS) -name '*.c')

OBJDIR=$(BINDIR)/obj
OBJECTS=$(foreach file,$(SOURCES),$(patsubst %.c,$(OBJDIR)/%.o,$(file)))

all: buildinfo prebuild $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(info Linking $@)
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c
	$(info $<)
	@mkdir -p $(shell dirname $@)
	@$(CC) -c $(CFLAGS) $< -o $@

buildinfo:
	$(info === Building $(PROJECTNAME) ($(BUILDTYPE)) ===)
	$(info C Compiler: $(CC))
	$(info Platform: $(PLATFORM))

prebuild:
	$(info === Running Prebuild Commands ===)
	mkdir -p $(BUILDDIR) $(BINDIR) $(OBJDIR)
	cp -r $(ASSETSDIR) $(BINDIR)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	$(info === Removing $(BUILDDIR) ===)
	rm -rf $(BUILDDIR)

.PHONY: buildinfo prebuild run clean
