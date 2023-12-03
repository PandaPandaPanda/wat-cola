OUTPUT := OUTPUT

CXX = u++                                  # compiler
CXXFLAGS = -g -multi -Wall -Wextra -MMD -D"${OUTPUT}" # compiler flags
ifeq ("${OUTPUT}","NOOUTPUT")
	CXXFLAGS += -O2 -nodebug
endif
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}    # makefile name

OBJECTS = main.o config.o bank.o parent.o printer.o nameServer.o vendingmachine.o truck.o plant.o watcardoffice.o watcard.o student.o groupoff.o # list of object files
EXEC = wat-cola

DEPENDS = ${OBJECTS:.o=.d}                 # substitute ".o" with ".d"

#############################################################

.PHONY : all clean
.ONESHELL :

all : ${EXEC}                              # build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}              # OPTIONAL : changes to this file => recompile

-include ${DEPENDS}                        # include *.d files containing program dependences

clean :                                    # remove files that can be regenerated
	rm -f *.d ${OBJECTS} ${EXEC}
