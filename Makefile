#Initializes the aliases to be used in target recipies

SOURCECODE     = main.cpp
LsSOURCECODE   = ls.cpp
CpSOURCECODE   = cp.cpp
src            = src
CXX            = g++
CPPFLAGS       = -Wall -Werror -ansi -pedantic
EXECUTABLE     = rshell
LsEXECUTABLE   = ls
CpEXECUTABLE   = cp

#bin (binary) --> output executables go here
#src          --> source code goes here
#test         --> test code files go here
#obj          --> contains all .o (object) files

#builds the bin directory before compiling
all: rshell ls cp
	
rshell:
	
	#echo "CREATED BIN DIRECTORY IN ROOT DIRECTORY"
	mkdir bin
	# goes to source folder where main.cpp is and compiles to executable named rshell
	cd $(src) && $(CXX) $(CPPFLAGS) -o $(EXECUTABLE) $(SOURCECODE)
	# moves into src directory and moves rshell.out (executable) into bin directory 
	cd $(src) && mv $(EXECUTABLE) ../bin		
	
	#echo "LAUNCHING NEW RSHELL SESSION"
	#cd bin && rshell
	#DELETES THE BIN DIRECTORY UPON EXITING OF rshell 
	#make clean
	make ls
ls:	
	cd $(src) && $(CXX) $(CPPFLAGS) -o $(LsEXECUTABLE) $(LsSOURCECODE)
	cd $(src) && mv $(LsEXECUTABLE) ../bin
	cd bin && ./ls
	#make cp
cp:	
	cd $(src) && $(CXX) $(CPPFLAGS) -o $(CpEXECUTABLE) $(CpSOURCECODE)
	cd $(src) && mv $(LsEXECUTABLE) ../bin

clean: 
	echo "DELETING BIN DIRECTORY IN ROOT FOLDER"
	rm -rf bin
