#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector> 
#include <cstdlib>
#include <cstdio>
#include <dirent.h>


using namespace std;

int main(int argc, char** argv){

	string first, second;
	struct stat buffer;
	if(argc <= 2){
		cout << "Error: Not enough arguments!" << endl;
		exit(1);  
	}
	first = argv[1];
	if(stat(argv[1], &buffer) == -1){
		cerr << "File does not exist!" << endl;
		exit(1);//the first argument is not a file
	}

	second = argv[2];
	if(stat(argv[2], &buffer) == 0){
		if(S_ISDIR(buffer.st_mode)){
			//move into dir
			second = second + "/" + first;
			if(link(first.c_str(), second.c_str()) != -1){
				if(unlink(first.c_str()) == -1){
					perror("unlink()");
					exit(1);
				}
				return 0;
			}
			else {
				perror("link()");
				exit(1);
			}

			return 0;
		}
		// second file already exists!
		else {	
			cerr << "Error, trying to overwrite an existing file!" << endl;
			exit(1);//the second file exists already
		}
	}
	//if it reaches here then move is authorized
	//link the two files 
	if(link(first.c_str(), second.c_str()) != -1){
		if(unlink(first.c_str()) == -1){
			perror("unlink()");
			exit(1);
		}
		return 0;
	}
	else{
		perror("link()");
		exit(1);
	}
	return 0;
}
