#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include "ls.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	string FLAGS = getFlags(argc,argv);	
	string Directory = getDirectory(argc,argv);
	ExecuteCommands(Directory, FLAGS);
	
	return 0;
}

