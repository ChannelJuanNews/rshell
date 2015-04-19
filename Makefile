#Initializes the aliases to be used in target recipies

sourceCode = main.cpp
object     = rshell.out
mainOrigin = src/main.cpp
src        = src
CXX        = g++
CPPFLAGS   = -Wall -Werror -ansi -pedantic

#bin (binary) --> output executables go here
#src          --> source code goes here
#test         --> test code files go here
#obj          --> contains all .o (object) files

#builds the bin directory before compiling
all: bin 
	
	# goes to source folder where main.cpp is and compiles to executable named rshell
	cd $(src) && $(CXX) $(CPPFLAGS) -o rshell $(sourceCode)
	# moves into src directory and moves rshell.out (executable) into bin directory 
	cd $(src) && mv rshell ../bin
	
	make rshell		

rshell:
	
	echo Launching new rshell session
	bin/rshell 
	make clean	
bin: 
	mkdir bin
	echo Created bin directory

clean: bin	
	rm -rf bin
