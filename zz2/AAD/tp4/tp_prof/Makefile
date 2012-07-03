# ----------------------------------------------------------
# Makefile based on gmake for compiling the project
# still lacks some features (building proto and tarball)
# ----------------------------------------------------------



# ----------------------------------------------------------
# file lists
#C_SRCS = $(wilcard *.c)
C_SRCS = gestion.c graph.c solution.c heuristics.c localsearches.c metaheuristics.c main.c
C_OBJS = $(patsubst %.c, %.o, $(C_SRCS))
EXEC = tp4


# ----------------------------------------------------------
# compiler and related options
CC     = gcc
#CFLAGS = -std=c99 -Wall -ansi -pedantic
CFLAGS =  -std=c99 -Wall -pedantic
LFLAGS = -lm
VFLAGS = -v --tool=memcheck --leak-check=yes --show-reachable=yes

MYDATE := `date +%Y%m%d`
MYDIR  := $(notdir $(CURDIR))/


# ----------------------------------------------------------
# conditional insertion of dependancies
ifeq (Makefile.depend, $(wildcard Makefile.depend))
  all :: $(EXEC)
  include Makefile.depend
else
  all :: depend $(EXEC)
endif


# ----------------------------------------------------------
# compilation rules

%.o : %.c
	@echo "   obj file : "$*.c
	@$(CC) -c $(CFLAGS) $*.c -o $*.o

$(EXEC) : $(C_OBJS)
	@echo "   exe file : "$(EXEC)
	@$(CC) -o  $(EXEC) $(C_OBJS) $(LFLAGS)


debug: CFLAGS += -g
debug:: clean $(C_OBJS)
	@echo "   building the debug version..."
	@$(CC) -o  $(EXEC) $(C_OBJS) $(LFLAGS)

#release: CFLAGS += -fvisibility
release: CFLAGS += -O2
release:: clean $(C_OBJS)
	@echo "   building the release..."
	@echo "   exe file : "$(EXEC)
	@$(CC) -o  $(EXEC) $(C_OBJS) $(LFLAGS)
	strip  $(EXEC)

stddebug: $(EXEC)
	@$(MAKE) valgrind $(VFLAGS) PARAMS='-l2 -u2 TMP_DATA/connex1.dat'

valgrind: $(EXEC)
	@echo " running memory check with "$(PARAMS)
	@valgrind $(VFLAGS) $(EXEC) $(PARAMS)

depend:: Makefile.depend

#Makefile.depend : parameters.c
Makefile.depend :
	@echo "   generating dependencies for ${EXEC}..."
	@$(CC) -MM $(C_SRCS) > Makefile.depend

archive:: clean
#	$(MAKE) clean
	@echo "   archiving working directory "$(MYDIR)"..."
	@cd .. ; tar zcf $(EXEC)_$(MYDATE).tgz $(MYDIR)

clean::
	@echo "   cleaning trash files"
	@rm -f core *~
	@echo "   cleaning obj files"
	@rm -f $(C_OBJS)
	@echo "   cleaning exe files"
	@rm -f $(EXEC)
	@echo "   removing the dependency file"
	@rm -f Makefile.depend
