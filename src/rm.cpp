#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>
#include <string.h>

using namespace std;

string convert(const char * data){return string(data);}

bool containsR(int argc, char * argv[]){
	string c = "";
	for(int i = 0; i < argc; i++){c +=convert(argv[i]);}
	for (unsigned i = 0; i < c.size(); i++){
		if (i+1 < c.size() && c.at(i) == '-' && c.at(i+1) == 'r'){
				return true;
		}
	}
	return false;
}

void rmRdir (const char * file){
	struct stat s;
	if (stat(file, &s) == -1){ perror("Failed to get shit");}
	bool directory = (S_ISDIR(s.st_mode));
	if (directory){
		DIR * dirp;
		if (NULL == (dirp = opendir(const_cast<char*>(file)))){ perror("Error opening directory");}
		struct dirent * filespecs;
		while (NULL != (filespecs =  readdir(dirp))){
			if (strcmp(filespecs->d_name, ".") == 0 || strcmp(filespecs->d_name, "..") == 0){
				continue;
			}
			string new_file = file; new_file.append("/"); new_file.append(filespecs->d_name);
			rmRdir(new_file.c_str());
		}
		int status; status = rmdir(file);
		if (status == -1){ cout << file << endl; perror("Failed to delete directory");}
	}
	else { unlink(file);}
}
void removeShit(int argc, char * argv[], bool containsR){

	for (int i = 1; i < argc; i++){
		// Gathers that status of a file/directory
		struct stat s;
		// if yo
		if (stat(argv[i], &s) == -1){
			if (strcmp(argv[i], "-r") == 0){continue;}
			cout << "rm: cannot remove " << "'" << argv[i] << "': " << flush;
			perror(argv[i]); exit(1);
		}
		if (S_ISDIR(s.st_mode) == -1){ perror(argv[i]); exit(1);}
		// If it is a directory AND it does NOT contains the -r flag then DO NOT DELETE
		if (S_ISDIR(s.st_mode)){
			if (containsR && !S_ISREG(s.st_mode) && S_ISDIR(s.st_mode)){
				// recursively delete
				// cout << "Recursively delete! " << argv[i] << endl;
				if (strcmp(argv[i], "-r") == 0){continue;}
				rmRdir(argv[i]);
				continue;
			}
			else {
				cout << "Warning! You are attempting to remove a directory" << endl;
				continue;
			}
		}
		if (S_ISREG(s.st_mode) ==  -1){	perror(argv[i]); exit(1);}
		if (S_ISREG(s.st_mode) && !(S_ISDIR(s.st_mode))){
			if (unlink(argv[i]) == -1){ perror("shit went wrong"); exit(1);}
		}
	}
}
int main (int argc, char * argv[] ){
	if (argc <= 1) {cout << "Not enough arguments!" << endl; return 0;}
	bool containsFlagR = containsR(argc, argv);
	removeShit(argc, argv, containsFlagR);
	return 0;
}
