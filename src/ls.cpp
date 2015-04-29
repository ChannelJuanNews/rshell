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

    /*if(argc <= 1) {
        cout << "Nothing passed in to argv." << endl;
        exit(1);
    }
    else{
        DIR *dirp;
        if(NULL == (dirp = opendir(argv[1]))){
            perror("There was an error with opendir(). ");
            exit(1);
        }
        struct dirent *filespecs;
        errno = 0;
        while(NULL != (filespecs = readdir(dirp))){
            cout << filespecs->d_name << " ";
        }
        if(errno != 0){
            perror("There was an error with readdir(). ");
            exit(1);
        }
        cout << endl;
        if(-1 == closedir(dirp)){
            perror("There was an error with closedir(). ");
            exit(1);
        }
    }*/

int main(int argc, char* argv[]) {
	
	string FLAGS = getFlags(argc,argv);	
	string Directory = getDirectory(argc,argv);
	ExecuteCommands(Directory, FLAGS);
	
	return 0;
}

