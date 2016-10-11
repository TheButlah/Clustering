# define the compiler to use
CXX = g++

# compiler flags:
# -g 		adds debugging info to the executable
# -Wall	turns on most compiler warnings
CXXFLAGS = -g -Wall

# define the linker to use
LINKER = g++ -o

# linker flags
LFLAGS = -Wall

# directories other than /usr/include to include
INCLUDES = -Iinclude

# define library paths in addition to /usr/lib
# to include libraries not in /usr/lib I'd specify
# their path using -Lpath, something like:
# LFLAGS = -L/home/newhall/lib  -L../lib
LFLAGS = 

# libraries (end in .so or .a) to link into executable:
# for example, to link in libmylib.so and libm.so:
# LIBS = -lmylib -lm
LIBS = 

# define the source files
SRCS = main.cpp

# define the src directory
SRCDIR = 
# define the obj directory
OBJDIR = obj

# the target build executable
TARGET = cluster

############################################################
#       NOTHING BELOW THIS SHOULD NEED TO BE CHANGED       #
############################################################

OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(TARGET)

$(OBJS): $(OBJDIR)/%.o : %(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c %< -o $@
	@echo "Compiled "$<" sucessfully!"

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS)
	@echo "Linking complete!"

.PHONY: clean
clean:
		$(RM) $(OBJDIR)/*.o *~ core $(INCDIR)/*~ 

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
