#ifndef _LS_H_
#define _LS_H_

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string>
#include <string.h>

using namespace std;



string convert(char * data){
	return string(data);
}



// gets the flags for ls all into one string
string getFlags(int argc, char * argv[]){
	
	string Commands = "";
	string FLAGS = "";
	
	// This converts all the commands into a string
	for (int i = 0; i < argc; i++){
		Commands += convert(argv[i]);
		Commands += " ";
	}
	for (unsigned j = 0; j < Commands.size(); j++){
		if ((Commands.at(j) == '-' && j+1 < Commands.size())){
			if ((Commands.at(j+1) == 'a') || (Commands.at(j+1) == 'A') 
			|| (Commands.at(j+1) == 'l') || (Commands.at(j+1) == 'L')
			|| (Commands.at(j+1) == 'r') || (Commands.at(j+1) == 'R')){

				while (Commands.at(j) != ' ' && (
				(Commands.at(j+1) == 'a') || (Commands.at(j+1) == 'A') || 
				(Commands.at(j+1) == 'l') || (Commands.at(j+1) == 'L') || 
				(Commands.at(j+1) == 'r') || (Commands.at(j+1) == 'R'))){
					
					FLAGS += Commands.at(j += 1);
				}
			}
		}
	}
	// Now all the flags are captured, so put them in an array
	cout << "THE FLAGS ARE: " << FLAGS << endl;
	return FLAGS;
}
	
void removeIndex(vector<char *> & v, int index){
	v.erase(v.begin() + index);
}
string getDirectory(int argc, char * argv[]){
	vector <char *> COMMANDS;
	string Commands = "";
	string DIRECTORY = "";
	
	// Moves the argv command line into a vector	
	for (int k = 1; k < argc; k++){
		COMMANDS.push_back(argv[k]);
	}
	// deletes any index in the vector that starts with the '-'
	for (unsigned l = 0; l < COMMANDS.size(); l++){
		cout << "COMMANDS: " << COMMANDS.at(l) << endl;
		if (COMMANDS.at(l)[0] == '-'){
			removeIndex(COMMANDS,l);
			l--;
		}
	}
	// This Converts the commands vector into a string
	for (unsigned i = 0; i < COMMANDS.size(); i++){
		Commands += convert(COMMANDS[i]);
		Commands += " ";
	}
	cout << "ONCE FLAGS ARE DELETED: " << Commands << endl;
	
	// Useless code now that the functions implemented above are implemented 
	for (unsigned j = 0; j < Commands.size(); j++){
		if ((Commands.at(j) != '-' && Commands.at(j) != ' ' && j+1 < Commands.size()) ){ 
			if ( (Commands.at(j+1) != 'a') || (Commands.at(j+1) != 'A') ||
			(Commands.at(j+1) != 'l') || (Commands.at(j+1) != 'L') || 
			(Commands.at(j+1) != 'r') || (Commands.at(j+1) != 'R') ){
				
				while((Commands.at(j) != ' ') && (j < Commands.size())){
					
					if ( (Commands.at(j+1) != 'a') || (Commands.at(j+1) != 'A') ||
					(Commands.at(j+1) != 'l') || (Commands.at(j+1) != 'L') || 
					(Commands.at(j+1) != 'r') || (Commands.at(j+1) != 'R')){
						
						DIRECTORY += Commands.at(j);
						j++;
					}
				}
			}
		}		
	}
	if (DIRECTORY.size() == 0){
		return ".";
	}
	else{
		cout << "THE DIRECTORY IS: " << DIRECTORY << endl;
		return DIRECTORY;
	}
}



void fillDirectories_files(char * CurrDirectory, vector<string> & v){
	
	DIR * dir;
	if(NULL == (dir = opendir(CurrDirectory))){
		perror("There was an error with opendir().");
		exit(1);
	}
	struct dirent * filespecs;
	errno = 0;
	while (NULL != (filespecs = readdir(dir))){
		v.push_back(filespecs->d_name);
		//else {cout << filespecs->d_name << " ";}
	}
	if (errno != 0){
		perror("There was an error with readdir().");
		exit(1);
	}
	cout << endl;
	if (-1 == closedir(dir)){
		perror("There was an error with closedir(). ");
		exit(1);
	}
}
void outputFiles(vector<string> & v){
	for (unsigned i = 0; i < v.size(); i++){
		if (v.at(i).at(0) == '.'){ }
		else { cout << v.at(i) << " ";}
	}
	cout << endl;
}
void outputFilesA(vector<string> & v){
	for (unsigned i = 0; i < v.size(); i++){
		cout << v.at(i) << " ";
	}
	cout << endl;
}

void outputFilesL(vector<string> & v){
	
	
	cout << "total " << "#" << endl;
	
		struct stat s;
		unsigned max = 0;
	
	for (unsigned i = 0; i < v.size(); i++){
		
		// ignore hidden files in this one
		if (v.at(i)[0] == '.'){ }
		else {
			
			
			
		}
		
	}
	
	
	
	
	
	
}
// sort the vector before you call print function
void sortVector(vector<string> & v){
	
	
	
}
void ExecuteCommands(string Directory, string FLAGS){
	
	bool A = false;
	bool L = false;
	bool R = false;
	vector<string> files_Directories;
		
	// Checks to see which flags have been passed in
	for (unsigned i = 0; i < FLAGS.size(); i++){
		if (FLAGS.at(i) == 'a' || FLAGS.at(i) == 'A'){
			A = true;
		}
		if (FLAGS.at(i) == 'l' || FLAGS.at(i) == 'L'){
			L = true;
		}
		if (FLAGS.at(i) == 'r' || FLAGS.at(i) == 'R'){
			R = true;
		}
	}
	char * DIRECTORY = new char[Directory.size() + 1];
	DIRECTORY[Directory.size()] = 0;
	memcpy(DIRECTORY,Directory.c_str(), Directory.size());
	cout << "CONVERTED DIRECTORY: " << DIRECTORY << endl; 

	// sort the vector into heigharchy before printing stuff
	sortVector(files_Directories);


	// ls
	if (A == false && L == false && R == false){
		fillDirectories_files(DIRECTORY,files_Directories);
		outputFiles(files_Directories);
	} 
	// ls -a
	else if (A == true && L == false && R == false){
		fillDirectories_files(DIRECTORY, files_Directories);
		outputFilesA(files_Directories);
	}
	// ls -l
	else if (A == false && L == true && R == false){
		fillDirectories_files(DIRECTORY, files_Directories);
		
	}
	// ls -R
	else if (A == false && L == false && R == true){
	
	}
	// ls -a -l
	else if (A == true && L == true && R == false){
	
	}
	// ls -a -R
	else if (A == true && L == false && R == true){
	
	}
	// ls -a -l -R
	else if (A == true && L == true && R == true){
	
	}
	// ls -l -R
	else if (A == false && L == true && R == true){
	
	}
	
	// deallocates dynamic memory
	delete DIRECTORY;	
}




#endif
