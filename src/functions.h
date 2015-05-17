#ifndef _FUNCTIONS_H_  
#define _FUNCTIONS_H_

#include <iostream>
#include <fcntl.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <term.h>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <errno.h>
#include <string.h>
#include <fstream>

using namespace std;

void DisplayUserHost(unsigned loopCounter){

	char * username = getlogin();
	std::cout << username;
	char hostname[100];
	int result;

	result = gethostname(hostname, 100);
	
	if (result == -1 && loopCounter < 1) {
		perror("Could not retrieve host name");
	}
	else {
		std::cout <<"@";
		unsigned i = 0;
		while (hostname[i] != '\0'){
			std::cout << hostname[i]; i++;
		}
	}
	std::cout << "$ ";
}

void printArgv(std::vector<char*> & v){

	for (unsigned i = 0; i < v.size(); i++){
		std::cout << v.at(i) << " ";
	}
	std::cout << std::endl;
}

void clearScreen() {

	#define del() printf("\033[H\033[J");
	del();
}

void rshellMessage() {
	
	std::cout << "              ==================================================               " << std::endl;
	std::cout << "                              Welcome to rshell! :)                            " << std::endl;
	std::cout << "              ==================================================               " << std::endl;
	std::cout << "                                                                               " << std::endl;
	std::cout << "===============================================================================" << std::endl;
	std::cout << "|                                                                             |" << std::endl;	
	std::cout << "| You have enabled settings specific for my cs100 hw0 w/ Mike Izbicki         |" << std::endl;
	std::cout << "| I will not be recording anything because I don't know how to.               |" << std::endl;
	std::cout << "|                                                                             |" << std::endl;
	std::cout << "| Important commands for this bash emulator                                   |" << std::endl;
	std::cout << "|   * gradeWishlist       displays the grade I want in your class             |" << std::endl;
	std::cout << "|   * typeSlow            practice typing as slow as possbile                 |" << std::endl;
	std::cout << "|                                                                             |" << std::endl;
	std::cout << "| Important commands for general A+- programming:                             |" << std::endl;
	std::cout << "|   * cake                  displays a picture of a char cake                 |" << std::endl;
	std::cout << "|   * std                   don't catch one of those                          |" << std::endl;
	std::cout << "|   * onTheGrind            that's what i've been doing all week              |" << std::endl;
	std::cout << "|   * pcpset                i've been halucinating about finishing this       |" << std::endl;
	std::cout << "|   * woman                 don't find out about commands. She wont tell you  |" << std::endl;
	std::cout << "|                                                                             |" << std::endl;
	std::cout << "|                   Type the command 'exit' to exit rshell                    |" << std::endl;
	std::cout << "===============================================================================" << std::endl;
}

// returns -1 if failed. otherwise returns 1
int executeCommands(std::vector<char*> & vec){
	
	// supports up to 100,000 commands
	char * argv[10000] = {0};
	char EXIT[4] = {'e','x','i','t'};
	
	unsigned i;
	for (i = 0; i < vec.size(); i++){ argv[i] = vec.at(i);}
	argv[i+1] = NULL;
	
	int pid = fork();
	unsigned index = 0;

	if (argv[0] == EXIT){return 0;}
	
	if (pid == -1){
		perror("There was an error with fork()");
		exit(1);
		return -1;
	}

	else if (pid == 0){
		
		//std::cout << "COMMAND IS: " << argv[0] << std::endl;	
		if (argv[0] == EXIT) {return 0;}
		if (-1 == execvp(argv[index], argv)){
			//perror("There was an error in execvp");
			for (unsigned i = 0; i < vec.size(); i++){
			std::cout << "-bash: " << argv[i] << ": command not found" << std::endl;
			}
			return -1;
		}
		exit(1);
	}
	else if (pid > 0){
				
		if (wait(0) == -1){
			perror("There was an error with wait() in the parent process");
			return -1;
		}
		if (argv[0] == EXIT){
			return 0;
		}
	}
	return 1;
}

void printVec(std::vector<char*> & v){

	for (unsigned i = 0; i < v.size(); i++){ std::cout << v.at(i) << " ";}
	std::cout << std::endl << std::endl;
}
std::string commentChecker(std::string commands){

	for (unsigned i = 0; i < commands.size(); i++){
		if (commands.at(i) == '#'){ commands.erase (commands.begin()+i, commands.end());}
	} return commands;
}
std::string connectorChecker(std::string commands){

	std::string AND = "&& ";
	for (unsigned i = 0; i < commands.size(); i++){
		if (commands.at(i) == ';' && i == commands.size() -1){ commands.at(i) = ' ';}
		if (commands.at(i) == ';'){commands.at(i) = ' ';commands.insert(i+1,AND);}
	}	
	//std::cout << "FINISHED STRING IS: " << commands << std::endl;
	return commands;
}

std::vector<char*> pop_front(std::vector<char *> v){
	std::vector<char *> vec(0);
	if (v.size() > 1){ for (unsigned i = 1; i < v.size(); i++){ vec.push_back(v.at(i));}}
	return vec;
}

void divideExecute(std::vector<char *> v){
	
	if (v.size() == 0){return;}
	else if (v.size() == 1) {
		std::vector<char *> * CurrentCommand = new std::vector<char *>;
		CurrentCommand->push_back(v.at(0));
		v = pop_front(v);
		executeCommands(*CurrentCommand);
		divideExecute(v);
		return;	
	}
	else if (v.size() > 1){
		
		std::vector<char *> * CurrentCommand = new std::vector<char*>;
		unsigned i = 0;
		while(strcmp(v.at(i),"&&") != 0 && strcmp(v.at(i),"||") != 0  /*strcmp(v.at(i),"|") != 0*/ && i < v.size()){
			CurrentCommand->push_back(v.at(i));
			i++;
		}
		for (unsigned k = 0; k < i; k++){
			v = pop_front(v);
		}
		//std::cout << "VECTOR AFTER POPPING OFF COMMANDS: ";
		//printVec(v);	
		if (v.size() == 0){
			executeCommands(*CurrentCommand);
			divideExecute(v);
			return;
		}
		else if (v.size() == 1){
			executeCommands(*CurrentCommand);
			return;
		}
		else if (v.size() > 1){
			
			if(strcmp(v.at(0),"&&") == 0){
				v = pop_front(v);
				executeCommands(*CurrentCommand);
				divideExecute(v);
				return;
			}
			else if (strcmp(v.at(0),"||") == 0 ){
				v = pop_front(v);
				if (executeCommands(*CurrentCommand) == -1){
					divideExecute(v);
					return;
				}
				else {
					v = pop_front(v);
					divideExecute(v);
					return;
				}
			
			}
		}
	
	}	
	return;	
}

bool containsLogic(std::vector<char*> &v){
	for (unsigned i = 0; i < v.size(); i++){
		//std::cout << v.at(i) << " ";
		if (strcmp(v.at(i),"&&") == 0 || strcmp(v.at(i),"||") == 0/*|| strcmp(v.at(i),"|") == 0*/){
			//std::cout << "LOGIC EXISTS!" << std::endl;
			return true;
		}
	}return false;
}

void processOutInAppend(vector<char*>v, vector<char*>&inf, vector<char*>&outf, vector<char*>&outAppen,vector<char*>&trippleIn, vector<char*>&newCommands){

	for(unsigned i = 0; i < v.size(); i++){
		if (strcmp(v.at(i), "<") == 0 && i != 0 && i+1 < v.size()){
			inf.push_back(v.at(i+1));
			v.erase(v.begin()+i+1);
			continue;
			//cout << "InRedir file is: " << v.at(i+1) << endl;
		}
		if (strcmp(v.at(i), ">") == 0 && i != 0 && i+1 < v.size()){
			outf.push_back(v.at(i+1));
			//cout << "OUTFILE: " << v.at(i+1) << endl;
			v.erase(v.begin()+i+1);
			continue;
			cout << "OutRedir file is: " << v.at(i+1) << endl;
		}
		if (strcmp(v.at(i),">>") == 0 && i != 0 && i+1 < v.size()){
			outAppen.push_back(v.at(i+1));
			v.erase(v.begin()+i+1);
			continue;
			//cout << "OutRedirAppend file is: " << v.at(i+1) << endl;
		}
		if ( strcmp(v.at(i),"<<<") == 0 && i!= 0 && i+1 < v.size()){
			/*while (i+1 < v.size()){
				trippleIn.push_back(v.at(i+1));
				v.erase(v.begin() + i + 1);
				i++;
			}*/
			//cout << "Current Command:!!!: " << v.at(i) << endl;
			if (strcmp(v.at(i+1), "<<<") == 0){/*cout << "we have more than one tripple input!" << endl;*/ break;}
			if (strcmp(v.at(i+1), "<") == 0){/*cout << "we have other input and stuff" << endl;*/ continue;}
			if (strcmp(v.at(i+1), ">") == 0){/*cout << "we have other input and stuff" << endl;*/ continue;}
			if (strcmp(v.at(i+1), ">>") == 0){/*cout << "we have other input and stuff" << endl;*/ continue;}

			trippleIn.push_back(v.at(i+1));
			v.erase(v.begin() + i + 1);
			i--;
			continue;
			// cout << "TrippleIn file is: " << v.at(i+1) << end
			//l;
		}
		if (strcmp(v.at(i), "<<<") == 0){continue;}
		//cout <<"Processed Command is: " << v.at(i) << endl;
		newCommands.push_back(v.at(i));
	}	
}

bool containsInRedir(vector<char*>&v){
	for (unsigned i = 0; i < v.size(); i++){
		if(strcmp(v.at(i), "<") == 0){return true;}
	}/*cout << "Does not contain <: \n";*/ return false;
}

bool containsOutRedir(vector<char*>&v){
	for (unsigned i = 0; i < v.size(); i++){
		if (strcmp(v.at(i),">") == 0){return true;}
	}/*cout << "Does not contain >: \n";*/ return false;
}

bool containsOutRedirAppend(vector<char*>&v){
	for(unsigned i = 0; i < v.size(); i++){
		if (strcmp(v.at(i),">>") == 0){return true;}
	}/*cout << "Does not contain >>: \n"*/;return false;
}

bool containsTrippleIn(vector<char*>&v){
	for(unsigned i = 0; i < v.size(); i++){
		if(strcmp(v.at(i), "<<<") == 0){return true;}
	}/*cout << "Does not contain <<<: \n";*/return false;
}

void executeIO( char * argv[], bool inRedir, bool outRedir, bool outRedirAppend, bool TrippleIn, vector<char*>&infiles, vector<char*>&outfiles, vector<char*>&outfilesAppend, vector<char*>&TRin){
	
	
	//ofstream outputFile;//("data.txt");
	char temp[9] = {'d','a','t','a','.','t','x','t','\0'};
	int pid = fork();
	if (pid == -1){
		perror("Error with forking stuffs in I/O redir");
		exit(1);
	}

	else if (pid == 0){
		if (outRedirAppend){
			if (close(1) == -1){
				perror("Error closing in executeIO: outRedirAppend");
				exit(1);
			}
			//outputFile.close();
			/*if (TrippleIn){
				close(0);
				if(open(temp,O_RDWR, 0644) == -1){
					perror("Error opening TRIPPLE IN,  in OUTREDIRAPPEND");
					exit(1);
				}
			}*/
			for (unsigned i = 0; i < outfilesAppend.size(); i++){
				if (open(outfilesAppend.at(i), O_CREAT | O_RDWR | O_APPEND, 0644) == -1){
					perror("Error opening in executeIO: outRedirAppend");
					exit(1);
				}
			}
		}

		if (outRedir){
			//cout << "We in nicca!" << endl;
			if (close(1) == -1){
				perror("Error closing in executeIO: outRedir");
				exit(1);
			}
			//cout << "TEST?" << endl;
			/*if (TrippleIn){
				if (open(temp,O_RDWR, 0644) == -1){
					perror("Error opening TRIPPLE IN,  in OUTREDIRAPPEND");
					exit(1);
				}
			}*/
			//outputFile.close();
			for (unsigned i = 0; i < outfiles.size(); i++){
				cout << "OUTFILES ARE: " << outfiles.at(i) << endl << flush;
				if (open(outfiles.at(i), O_CREAT | O_RDWR | O_TRUNC, 0644) == -1){
					perror("Error opening in executeIO: outRedir");
					exit(1);
				}
			}
			//cout << endl;
		}

		if (inRedir){

			if (close(0) == -1){
				perror("Error closing in executeIO: inRedir");
				exit(1);
			}
			for (unsigned i = 0; i < infiles.size(); i++){
				if(open(infiles.at(i), O_RDONLY | O_CREAT) == -1){
					perror("Error opening in executeIO: inRedir");
					exit(1);
				}
			}
		}
		if (TrippleIn){

			//****** THIS OPENS THE CREATED data.txt FILE AND OUTPUTS THE INPUTTED STRING INTO IT ******
			ofstream outputFile;
			outputFile.open("data.txt");
			string temp = "";
			for (unsigned i = 0; i < TRin.size(); i++){temp += TRin.at(i);if(i != TRin.size() - 1){ temp+= " " ;}}
			if (temp.size() > 1 && temp.at(0) == '\"'){temp.erase(temp.begin());} // this erases the first quotes
			if (temp.at(temp.size() - 1) == '\"'){temp.erase(temp.end()-1);}
			outputFile << temp << endl;
			outputFile.close();
			// ***********************************************************************************//////

			if (close(0) == -1){
				perror("Error closing in executeIO: trippleIn");
				exit(1);
			}	
			string data = "data.txt";		
			if (open(data.c_str(), O_RDWR | O_CREAT, 0644 ) == -1){
				perror("Error opening in executableIO: trippleIn");
				exit(1);
			}

			cout << "This is the string being outputed: " << temp << endl; 
			
		}

		//for (unsigned i = 0; i < index; i++){cout<<argv[i] << " ";}cout << endl;
		if (execvp(argv[0], argv) == -1){
			perror("Error with execvp in executeIO");
			exit(1);
		}
		errno = 0;
		exit(0);	
	}
	// if pid is not zero then we are in the parent process!	
	else if (pid > 0){
		if (wait(0) == -1){
			perror("Error waiting for child process!");
			exit(1);
		}
		if (remove( "data.txt" ) != 0 ){
			perror( "Error deleting file" );
		}
		//if (TrippleIn){cout << endl;}
	}	
}

bool containsOtherLogic(vector<char*>&v){
	for (unsigned i = 0; i < v.size(); i++){
		if (strcmp(v.at(i), "<") == 0){return true;} 
		if (strcmp(v.at(i), ">") == 0){return true;}
		if (strcmp(v.at(i), ">>") == 0){return true;}
		if (strcmp(v.at(i),"<<<") == 0){return true;}
		if (strcmp(v.at(i), "|") == 0){return true;}
	}return false;
}

bool gonnaPipe(vector<char*>&v){
	for(unsigned i = 0; i < v.size(); i++){if(strcmp(v.at(i),"|") == 0){return true;}}
	return false;
}
void piping(vector<char*>v){

		


		
}

bool isntString(vector<char*> & v){
	if(v.size() != 3){cout << "Not enough arguments!" << endl; return false;}
	if((v.at(2)[0]) == '\"'){
		cout << "first is quotes!" << endl;
		int index = 0;
		while(v.at(2)[index] != '\0'){index++;}
		if(v.at(2)[index] != '\"'){cout << "last is not quotes!" << endl;return false;}
		else{return true;}
	}return false;
}
bool tokenizeInput(std::string commands){

	std::vector<char *> v;
	std::vector<int> index;
	std::vector<int> linkers;
		
	// supports up to a 99,999 character command input
	char tokenArray[10000] = {'\0'};
	const char deliminator[2] = {' '};
	char * token;
	std::string modifiedCommands;

	modifiedCommands = commentChecker(commands);
	modifiedCommands = connectorChecker(modifiedCommands);
		

	for (unsigned i = 0; i < modifiedCommands.size(); i++){
		tokenArray[i] = modifiedCommands.at(i);
	}

	token = strtok(tokenArray, deliminator);
	while(token != NULL){
		v.push_back(token);
		token = strtok(NULL, deliminator);
	}
	// if only comments then no need to execute any commands, return
	if (v.size() == 0){return false;}
	// if exit then exit
	if (strcmp(v.at(0), "exit") == 0){return true;}
	if (containsLogic(v)){
		divideExecute(v);
		return false;
	}
	else if (containsOtherLogic(v)){
		
		if (gonnaPipe(v)){
			cout<< "WE GONNA PIPE BETCH!" << endl;
			piping(v);
			return false;
		}	
		
		// cout << "WE ARE IN NICCA!" << endl;	
		// if piping then go to piping function

		bool inRedir  = containsInRedir(v);
		bool outRedir = containsOutRedir(v);
		bool outRedirAppend = containsOutRedirAppend(v); 
		bool comeInside3 = containsTrippleIn(v);

		vector<char*> infiles;
		vector<char*> outfiles;
		vector<char*> outfilesAppend;
		vector<char*> trippleIn;
		vector<char*> newCommands;
	
		processOutInAppend(v,infiles,outfiles,outfilesAppend, trippleIn, newCommands);
		
		//cout << "New commands are: " << endl;
		char * ar[100] = {0};
		for(unsigned i = 0; i < newCommands.size(); i++){ar[i] = newCommands.at(i); /*cout << newCommands.at(i) << " ";*/}
		// cout << endl << endl;
		
		executeIO(ar,inRedir, outRedir,outRedirAppend,comeInside3 ,infiles,outfiles, outfilesAppend, trippleIn);
		return false;
	}
	else {

		if (executeCommands(v) == 0){
		}
		return false;
	}
	return false;	
}

#endif 
