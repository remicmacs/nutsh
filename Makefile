# Set the compiler to g++ if not set in environment
ifeq ($(CXX),)
CXX := g++
endif

# compiler flags:
#  -g         adds debugging information to the executable file
#  -std=c++17 force using c++17
#  -Wall      turns on most, but not all, compiler warnings
CFLAGS  = -g -std=c++17 -Wall -Wextra -pedantic-errors -Werror -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
# example: LIBS = -lm
LIBS = -lstdc++fs -lreadline

# define any directories containing header files other than /usr/include
# example : INCLUDES = -I../include
INCLUDES =

# define the C source files
SRCS = main.cpp Builtin.cpp CDBuiltin.cpp PWDBuiltin.cpp EchoBuiltin.cpp ExportBuiltin.cpp Builtins.cpp Prompt.cpp Executor.cpp

# define the C object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file if $MAIN is not set
ifeq ($(MAIN),)
MAIN := nutsh
endif

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(MAIN)
	@echo  nutsh has been compiled

$(MAIN): $(OBJS)
	$(CXX) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

install:
	install -m 755 $(MAIN) $(PKGDIR)/usr/bin