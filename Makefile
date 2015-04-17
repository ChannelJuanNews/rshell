sourceCode = main.cpp
object     = main.o
mainOrigin = src/main.cpp
src        = src

CXX        = g++
CPPFLAGS   = -Wall -Werror -ansi -pedantic

#bin (binary) --> output executables go here
#src          --> source code goes here
#test         --> test code files go here
#obj          --> contains all .o (object) files

#builds the bin and obj directories before compiling
all: bin
	
	# goes to source folder where main.cpp is and compiles to executable named rshell
	cd $(src) && $(CXX) $(CPPFLAGS) -o rshell $(sourceCode)
	# moves into src directory and moves rshell.out (executable) into bin directory 
	cd $(src) && mv rshell ../bin
	
rshell:
	
	#BEGINS NEW RSHELL SESSION
	bin/rshell 
	clean	
bin: 
	mkdir bin

clean: 

	rm -rf bin obj
