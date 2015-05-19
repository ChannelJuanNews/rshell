#ifndef _LS_H_
#define _LS_H_

#include <cstdlib>
#include <algorithm>
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
#include <pwd.h>
#include <grp.h>
//#include <uuid/uuid.h>
#include <string.h>
#include <iomanip>

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
	//cout << "THE FLAGS ARE: " << FLAGS << endl;
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
		//cout << "COMMANDS: " << COMMANDS.at(l) << endl;
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
	//cout << "ONCE FLAGS ARE DELETED: " << Commands << endl;
	
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
		//cout << "THE DIRECTORY IS: " << DIRECTORY << endl;
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
char blue []  = {"\033[1;34m"};
char white[]  = {"\033[100m"};
char green[]  = {"\033[1;32m"};
char RESET[]  = {"\033[0m"}; 

char directory   [] = {"\033[1;34m"};
char hidden      [] = {"\033[1;34m\033[1;40m"};
char executable  [] = {"\033[1;32m"};

void outputFiles(vector<string> & v){	
	// captures the max width for priting and shit
	unsigned MAX = 0;
	for(unsigned i = 0; i < v.size(); i++){
		if (v.at(i)[0] == '.'){continue;}
		if (v.at(i).size() > MAX){
			MAX+=v.at(i).size();
		}
	}
	for (unsigned i = 0; i < v.size(); i++){
		struct stat s;	
		if (stat(v.at(i).c_str(), &s) == 1){
			perror("Shit went wront when opening file/directory before printing");
			exit(1);
		}
		if (v.at(i).at(0) == '.'){continue;}
		else if(S_ISDIR(s.st_mode)){
			cout <<  directory << setw(MAX) << left <<  v.at(i) << "\033[0m" << " ";
		}
		else if (S_ISREG(s.st_mode) && (s.st_mode & S_IXUSR)){
			cout << executable << setw(MAX) << left << v.at(i) << "\033[0m" << " ";
		}
		else {
			cout << setw(MAX) << left << v.at(i) << " ";
		}
		// if we have five columns then print newline
		if ((i%5) == 0){cout << endl;}
	}
	cout << endl;
}
void outputFilesA(vector<string> & v){
	// captures the max width for priting and shit
	unsigned MAX = 0;
	for(unsigned i = 0; i < v.size(); i++){
		if (v.at(i).size() > MAX){
			MAX+=v.at(i).size();
		}
	}
	for (unsigned i = 0; i < v.size(); i++){
		struct stat s;	
		if (stat(v.at(i).c_str(), &s) == 1){
			perror("Shit went wront when opening file/directory before printing");
			exit(1);
		}
		if (v.at(i)[0] == '.'){
			cout << hidden << setw(MAX) << left << v.at(i) << "\033[0m\033[0m" << " ";
		}
		else if(S_ISDIR(s.st_mode)){
			cout <<  directory << setw(MAX) << left <<  v.at(i) << "\033[0m" << " ";
		}
		else if (S_ISREG(s.st_mode) && (s.st_mode & S_IXUSR)){
			cout << executable << setw(MAX) << left << v.at(i) << "\033[0m" << " ";
		}
		else {
			cout << setw(MAX) << left << v.at(i) << " ";
		}
		// if we have five columns then print newline
		if ((i%5) == 0){cout << endl;}
	}
	cout << endl;
}
void outputFilesL(vector<string> & v){
	
	int total = 0;
	for (unsigned i = 0; i < v.size(); i++){
		struct stat buff;
		if (stat(v.at(i).c_str(), &buff) == 1){
			perror("There was an error gathering total");
			exit(1);
		}
		total += buff.st_blocks;
	}
	cout << "total " << total/2 << endl;	
	for (unsigned i = 0; i < v.size(); i++){
		
		if (v.at(i)[0] == '.'){ }
		else {
			struct stat s;
			unsigned max = 0;	
				
			if (stat(v.at(i).c_str(), &s) == 1){
				cout << "The file that doesn't work is: " << v.at(i) << endl;
				perror(v.at(i).c_str());
				exit(1);
			}
			for (unsigned j = 0; j < v.size(); j++){
				
				unsigned MAX = 0;
				if (stat(v.at(j).c_str(), &s) == -1){
					perror("Error with stat in outputFilesL");
					exit(1);
				}
				int holdSize = s.st_size;
				while(holdSize > 0){
				
					holdSize = holdSize/10;
					MAX++;
				}
				if (MAX > max){
					max = MAX;
				}
				
			}
			if(stat(v.at(i).c_str(), &s) == -1){
				perror("Error with second stat in outputFilesL");
				exit(1);
			}
			
			struct passwd * pw = getpwuid(s.st_uid);
			struct group  * gr = getgrgid(s.st_gid);
			if (!pw){
				perror("Error with getting owner name");
				exit(1);
			}
			if (!gr){
				perror("Error with getting group name");
				exit(1);
			}
			if (S_ISREG(s.st_mode)){ cout << "-";}
			else if (S_ISDIR(s.st_mode)){cout << "d";}
			else if (S_ISCHR(s.st_mode)){cout << "c";}
			else if (S_ISBLK(s.st_mode)){cout << "b";}
			else if (S_ISFIFO(s.st_mode)){cout << "P";}
			else if (S_ISLNK(s.st_mode)){cout << "l";}
			else if (S_ISSOCK(s.st_mode)){cout << "s";}
			else {cout << "?";}
	
			cout << ((s.st_mode & S_IRUSR) ? "r" : "-") << 
				((s.st_mode & S_IWUSR) ? "w" : "-") <<
				((s.st_mode & S_IXUSR) ? "x" : "-");
	
			cout << ((s.st_mode & S_IRGRP) ? "r" : "-") << 
				((s.st_mode & S_IWGRP) ? "w" : "-") <<
				((s.st_mode & S_IXGRP) ? "x" : "-");
	
			cout << ((s.st_mode & S_IROTH) ? "r" : "-") << 
				((s.st_mode & S_IWOTH) ? "w" : "-") <<
				((s.st_mode & S_IXOTH) ? "x" : "-");
	
			//nlink_t         st_nlink;         /* Number of hard links */
			//struct timespec st_mtimespec;     /* time of last data modification */
			
			// couts the hard links
			cout << " " << s.st_nlink;
			// prints the user and group name
			cout << " " << pw->pw_name << " " <<gr->gr_name;
			// prints out the size of the file
			cout << setw(max + 1) << s.st_size;
			
			// used with the ANSI codes for coloring
			/*
			switch (sb.st_mode & S_IFMT) {
			case S_IFBLK:  printf("block device\n");            break;
			case S_IFCHR:  printf("character device\n");        break;
			case S_IFDIR:  printf("directory\n");               break;
			case S_IFIFO:  printf("FIFO/pipe\n");               break;
			case S_IFLNK:  printf("symlink\n");                 break;
			case S_IFREG:  printf("regular file\n");            break;
			case S_IFSOCK: printf("socket\n");                  break;
			default:       printf("unknown?\n");                break;
			}			
			*/
			struct tm timespecs;
			localtime_r(&s.st_mtime, &timespecs);
			char buff[20];
			strftime((char*)&buff, 20, " %b %d %H:%M", & timespecs);
			printf("%s ", buff);		
			//if (v.at(i)[0] == '.'){
			//	cout << hidden << setw(MAX) << left << v.at(i) << "\033[0m\033[0m" << " ";
			//}
			if(S_ISDIR(s.st_mode)){
				cout <<  directory << v.at(i) << "\033[0m" << " ";
			}
			else if (S_ISREG(s.st_mode) && (s.st_mode & S_IXUSR)){
				cout << executable << v.at(i) << "\033[0m" << " ";
			}
			else {
				cout << v.at(i) << " ";
			}
			cout << endl;
		}
		
	}
	
}

void outputFilesAL(vector<string> & v){	
	int total = 0;
	for (unsigned i = 0; i < v.size(); i++){
		struct stat buff;
		if (stat(v.at(i).c_str(), &buff) == 1){
			perror("There was an error gathering total");
			exit(1);
		}
		total += buff.st_blocks;
	}
	cout << "total " << total/2 << endl;	
	for (unsigned i = 0; i < v.size(); i++){
		struct stat s;
		unsigned max = 0;	
		if (stat(v.at(i).c_str(), &s) == 1){
			cout << "The directory that could not be opened was " << v.at(i) << endl;
			perror(v.at(i).c_str());
			exit(1);
		}
		for (unsigned j = 0; j < v.size(); j++){
			
			unsigned MAX = 0;
			if (stat(v.at(j).c_str(), &s) == -1){
				perror(v.at(i).c_str());
				exit(1);
			}
			int holdSize = s.st_size;
			while(holdSize > 0){
			
				holdSize = holdSize/10;
				MAX++;
			}
			if (MAX > max){
				max = MAX;
			}
			
		}
		if(stat(v.at(i).c_str(), &s) == -1){
			perror("Error gatherin stat in outputFilesAL");
			exit(1);
		}
		
		struct passwd * pw = getpwuid(s.st_uid);
		struct group  * gr = getgrgid(s.st_gid);
		if (!pw){
			perror("Error with getting owner name");
			exit(1);
		}
		if (!gr){
			perror("Error with getting group name");
			exit(1);
		}

		if (S_ISREG(s.st_mode)){ cout << "-";}
		else if (S_ISDIR(s.st_mode)){cout << "d";}
		else if (S_ISCHR(s.st_mode)){cout << "c";}
		else if (S_ISBLK(s.st_mode)){cout << "b";}
		else if (S_ISFIFO(s.st_mode)){cout << "P";}
		else if (S_ISLNK(s.st_mode)){cout << "l";}
		else if (S_ISSOCK(s.st_mode)){cout << "s";}
		else {cout << "?";}
	
		cout << ((s.st_mode & S_IRUSR) ? "r" : "-") << 
			((s.st_mode & S_IWUSR) ? "w" : "-") <<
			((s.st_mode & S_IXUSR) ? "x" : "-");

		cout << ((s.st_mode & S_IRGRP) ? "r" : "-") << 
			((s.st_mode & S_IWGRP) ? "w" : "-") <<
			((s.st_mode & S_IXGRP) ? "x" : "-");

		cout << ((s.st_mode & S_IROTH) ? "r" : "-") << 
			((s.st_mode & S_IWOTH) ? "w" : "-") <<
			((s.st_mode & S_IXOTH) ? "x" : "-");
		
		// couts the hard links
		cout << " " << s.st_nlink;
		// prints the user and group name
		cout << " " << pw->pw_name << " " <<gr->gr_name;
		// prints out the size of the file
		cout << setw(max + 1) << s.st_size;

		struct tm timespecs;
		localtime_r(&s.st_mtime, &timespecs);
		char buff[20];
		strftime((char*)&buff, 20, " %b %d %H:%M", & timespecs);
		printf("%s ", buff);
		
		if (v.at(i)[0] == '.'){
			cout << hidden << v.at(i) << "\033[0m\033[0m" << " ";
		}
		else if(S_ISDIR(s.st_mode)){
			cout <<  directory << v.at(i) << "\033[0m" << " ";
		}
		else if (S_ISREG(s.st_mode) && (s.st_mode & S_IXUSR)){
			cout << executable << v.at(i) << "\033[0m" << " ";
		}
		else {
			cout << v.at(i) << " ";
		}
		cout << endl;
	}	
}
// sort the vector before you call print function
//Comparison; not case sensitive.
bool compareNoCase (string first, string second){
	unsigned i=0;
	while ((i < first.length()) && (i < second.length())){
		if (tolower (first[i]) < tolower (second[i])) return true;
		else if (tolower (first[i]) > tolower (second[i])) return false;
			i++;
	}
	if (first.length() < second.length()) return true;
	else return false;
}
// this function sorts the vector alphabetically with any '.' files having priority
void sortVector(vector<string> & v){
	sort(v.begin(), v.end(), compareNoCase);
}
void recursive(vector<string> v){
	cout << "Sorry, this feature is not available yet! :( " << endl;
}
void AllRecursive(vector<string> v){
	cout << "Sorry, this feature is not available yet! :( " << endl;
}
void AllLongRecursive(vector<string> v){
	cout << "Sorry, this feature is not available yet! :( " << endl;
}
void longRecursive(vector<string> v){
	cout << "Sorry, this feature is not available yet! :( " << endl;
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
	//cout << "CONVERTED DIRECTORY: " << DIRECTORY << endl; 

	// ls
	if (A == false && L == false && R == false){
		fillDirectories_files(DIRECTORY,files_Directories);
		sortVector(files_Directories);
		outputFiles(files_Directories);
	} 
	// ls -a
	else if (A == true && L == false && R == false){
		fillDirectories_files(DIRECTORY, files_Directories);
		sortVector(files_Directories);
		outputFilesA(files_Directories);
	}
	// ls -l
	else if (A == false && L == true && R == false){
		fillDirectories_files(DIRECTORY, files_Directories);
		sortVector(files_Directories);
		outputFilesL(files_Directories);	
	}
	// ls -R ******
	else if (A == false && L == false && R == true){
		fillDirectories_files(DIRECTORY, files_Directories);
		sortVector(files_Directories);
		// not yet supported
		recursive(files_Directories);
	}
	// ls -a -l
	else if (A == true && L == true && R == false){
		fillDirectories_files(DIRECTORY, files_Directories);
		sortVector(files_Directories);
		outputFilesAL(files_Directories);
	}
	// ls -a -R ******
	else if (A == true && L == false && R == true){
		fillDirectories_files(DIRECTORY, files_Directories);
		sortVector(files_Directories);
		// not yet supported
		AllRecursive(files_Directories);
	}
	// ls -a -l -R *****
	else if (A == true && L == true && R == true){
		fillDirectories_files(DIRECTORY, files_Directories);
		sortVector(files_Directories);
		// not yet supported
		AllLongRecursive(files_Directories);
	}
	// ls -l -R ****
	else if (A == false && L == true && R == true){
		fillDirectories_files(DIRECTORY, files_Directories);
		sortVector(files_Directories);
		// not yet supported
		longRecursive(files_Directories);
	}
	
	// deallocates dynamic memory
	delete [] DIRECTORY;	
}
#endif
