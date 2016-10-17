all:
	mkdir -p build && cd build && cmake .. && make && cd ..

clean:
	rm -rf build	

################## OLD MAKEFILE ##############################

## This makefile was based almost entirely on Nicholas Hamilton's makefile:
## http://stackoverflow.com/a/27794283
#
##Compiler and Linker
#CC			:= x86_64-w64-mingw32-g++
#
##The Target Binary Program
#TARGET			:= cluster.exe
#
##The Directories, Source, Includes, Objects, Binary and Resources
#SRCDIR			:= src/main/cpp
#INCDIR			:= src/main/cpp/include
#BUILDDIR		:= obj
#TARGETDIR		:= bin
#RESDIR			:= src/main/res
#SRCEXT			:= cpp
#DEPEXT			:= d
#OBJEXT			:= o
#
#
##Flags, Libraries and Includes
#
## compiler flags: 
## -Wall		most suggested warnings
## -g			put in debugging symbols
## -O3			SUPAR OPTIMIZE
#CFLAGS      := -std=c++0x -Wall -O3 -g
## linker flags:
## to link library libexample.so or libexample.a, use -lexample
#LIB         :=
#INC         := -I$(INCDIR) -I/usr/local/include
#INCDEP      := -I$(INCDIR)
#
##-------------------------------------------------------------------------------
##DO NOT EDIT BELOW THIS LINE
##-------------------------------------------------------------------------------
##configure the shell to have some extra functionality
##SHELL:=/bin/bash -O extglob
#
#SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
#OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
#
#RESOURCES		:= $(shell find $(RESDIR) -type f)
#
##Defauilt Make
#all: $(TARGETDIR)/$(TARGET) $(TARGETDIR)
#
##Remake
#remake: cleaner all
#
## manually update resources
#resources: $(TARGETDIR)
#
## make sure TARGETDIR exists, and update the resources if needed
#$(TARGETDIR): $(RESOURCES)
#	mkdir -p $(TARGETDIR)
#	@echo "Updating resources.."
#	rsync -a $(RESDIR)/ $(TARGETDIR)
#	@echo "Resourced updated!"
#	touch $(TARGETDIR)
#
#$(BUILDDIR):
#	mkdir -p $(BUILDDIR)
#
##Make the Directories
##directories:
##	@mkdir -p $(TARGETDIR)
##	@mkdir -p $(BUILDDIR)
#
##Clean only Objects
#clean:
#	rm -rf $(BUILDDIR)
#
##Full Clean, Objects and Binaries
#cleaner: clean
#	rm -rf $(TARGETDIR)
#
##Pull in dependency info for *existing* .o files
#-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))
#
##Link
#$(TARGETDIR)/$(TARGET): $(OBJECTS) | $(TARGETDIR)
#	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)
#
##Compile
#$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT) | $(BUILDDIR)
#	@mkdir -p $(dir $@)
#	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
#	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
#	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
#	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
#	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
#	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp
#
##Non-File targets that function more as commands
#.PHONY: all remake clean cleaner resources
