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
	if (username == NULL){
		perror("Error getting login");
		exit(1);
	}
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
pid_t wpid = 0;
int status;
// returns -1 if failed. otherwise returns 1
int executeCommands(std::vector<char*> & vec){
	
	// supports up to 100,000 commands
	char * argv[10000] = {0};
	char EXIT[5] = {'e','x','i','t','\0'};
	
	unsigned i;
	for (i = 0; i < vec.size(); i++){ argv[i] = vec.at(i);}
	argv[i+1] = NULL;
	
	if (argv[0] == EXIT){return 0;}
		
	int pid = fork();
	unsigned index = 0;

	if (pid == -1){
		perror("There was an error with fork()");
		exit(1);
		return -1;
	}

	else if (pid == 0){
		
		//std::cout << "COMMAND IS: " << argv[0] << std::endl;	
		if (argv[0] == EXIT) {return 0;}
		if (-1 == execvp(argv[index], argv)){
			perror("There was an error in execvp");
			for (unsigned i = 0; i < vec.size(); i++){
			std::cout << "-bash: " << argv[i] << ": command not found" << std::endl;
			}
			return -1;
		}
		exit(1);
	}
	do{
		wpid = wait(&status);
	}while(wpid == -1 && errno == EINTR);
	if(wpid == -1){perror("wait error"); return -1;}
	/*else {		
		if (wait(0) == -1){
			perror("There was an error with wait() in the parent process");
			return -1;
		}
	}*/



	/*
	else if (pid > 0){
		
		int wpid;
		int status = 0;
		do{
			wpid = wait(&status);
		}while(wpid == -1 && errno == EINTR);
		if (wpid == -1){perror("wait error"); return -1;}
		else {
		
			if (wait(0) == -1){
				perror("There was an error with wait() in the parent process");
				return -1;
			}
		}
		if (argv[0] == EXIT){
			return 0;
		}
	}*/

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
	if (v.size() > 1){
		for (unsigned i = 1; i < v.size(); i++){	
			vec.push_back(v.at(i));
		}
	}
	cout << "COMMANDS AFTER ONE POP_BACK: " << endl;
	printVec(vec);
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
		while(strcmp(v.at(i),"&&") != 0 && strcmp(v.at(i),"||") != 0  && i < v.size()){
			CurrentCommand->push_back(v.at(i));
			i++;
		}
		cout << "POP_BACK GONNA BE CALLED " << i << "times" << endl;
		for (unsigned k = 0; k < i; k++){
			v = pop_front(v);
		}
		std::cout << "VECTOR AFTER POPPING OFF COMMANDS: ";
		printVec(v);
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
				if (executeCommands(*CurrentCommand) == -1){
					cout << "FAILED!" << endl;
				}
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
			else{
				executeCommands(*CurrentCommand);
				return;
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
void processOutInAppend(vector<char*>v, vector<char*>&inf, vector<char*>&outf, vector<char*>&outAppen,vector<char*>&trippleIn, vector<char*> & NumOut, vector<char*>& NumOutAppend, vector<char*>&newCommands){

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
			//cout << "Current Command:!!!: " << v.at(i) << endl;
			if (strcmp(v.at(i+1), "<<<") == 0){/*cout << "we have more than one tripple input!" << endl;*/ break;}
			if (strcmp(v.at(i+1), "<") == 0){/*cout << "we have other input and stuff" << endl;*/ continue;}
			if (strcmp(v.at(i+1), ">") == 0){/*cout << "we have other input and stuff" << endl;*/ continue;}
			if (strcmp(v.at(i+1), ">>") == 0){/*cout << "we have other input and stuff" << endl;*/ continue;}	
			if (v.at(i+1)[0] >= '0' && v.at(i+1)[0] <= '9'){continue;}
			trippleIn.push_back(v.at(i+1));
			v.erase(v.begin() + i + 1);
			i--;
			continue;
			// cout << "TrippleIn file is: " << v.at(i+1) << end
			//l;
		}
		if (v.at(i)[0] >= '0' && v.at(i)[0] <= '9'){
			if (v.at(i)[1] == '>' && i+1 < v.size()){
				if (v.at(i)[2] == '>'){}
				else{
					NumOut.push_back(v.at(i+1));
					v.erase(v.begin()+i+1);
					continue;
				}
			}
		}
		if (v.at(i)[0] >= '0' && v.at(i)[0] <= '9'){
			if (v.at(i)[1] == '>' && i+1 < v.size()){
				if(v.at(i)[2] != '\0' && v.at(i)[2] == '>'){
					NumOutAppend.push_back(v.at(i+1));
					v.erase(v.begin()+i+1);
					continue;
				}		
			}
		}
		if (strcmp(v.at(i), "<<<") == 0){continue;}
		//cout <<"Processed Command is: " << v.at(i) << endl;
		newCommands.push_back(v.at(i));
	}	
}



bool containsInRedir(const vector<char*>&v){
	for (unsigned i = 0; i < v.size(); i++){
		if(strcmp(v.at(i), "<") == 0){return true;}
	}/*cout << "Does not contain <: \n";*/ return false;
}
bool containsOutRedir(const vector<char*>&v){
	for (unsigned i = 0; i < v.size(); i++){
		if (strcmp(v.at(i),">") == 0){return true;}
	}/*cout << "Does not contain >: \n";*/ return false;
}
bool containsOutRedirAppend(const vector<char*>&v){
	for(unsigned i = 0; i < v.size(); i++){
		if (strcmp(v.at(i),">>") == 0){return true;}
	}/*cout << "Does not contain >>: \n"*/;return false;
}
bool containsTrippleIn(const vector<char*>&v){
	for(unsigned i = 0; i < v.size(); i++){
		if(strcmp(v.at(i), "<<<") == 0){return true;}
	}/*cout << "Does not contain <<<: \n";*/return false;
}
bool containsOutFile(const vector<char*> &v){
	for(unsigned i = 0; i < v.size(); i++){
		if (v.at(i)[0] >= '0' && v.at(i)[0] <= '9'){
			if (v.at(i)[1] == '>'){
				if (v.at(i)[2] == '>'){return false;}
				else{
					return true;
				}
			}
		}
	}return false;
}
bool containsOutFileAppend(const vector<char*> &v){
	for(unsigned i = 0; i < v.size(); i++){
		if (v.at(i)[0] >= '0' && v.at(i)[0] <= '9'){
			if (v.at(i)[1] == '>'){
				if (v.at(i)[2] != '\0' && v.at(i)[2] == '>'){
					return true;
				}
			}
		}
	}return false;
}
void executeIO( char * argv[], bool inRedir, bool outRedir, bool outRedirAppend, bool TrippleIn, bool NumOUT, bool NumOUTA, vector<char*>&infiles, vector<char*>&outfiles, vector<char*>&outfilesAppend, vector<char*>&TRin, vector<char*> NUMoutfiles, vector<char*> NUMoutfilesA, int FileD, int FileDApp, bool pipingAfter){
	
	//ofstream outputFile;//("data.txt");
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
			for (unsigned i = 0; i < outfiles.size(); i++){
				//cout << "OUTFILES ARE: " << outfiles.at(i) << endl << flush;
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
				if(open(infiles.at(i), O_RDONLY) == -1){
					perror("Error opening in executeIO: inRedir");
					exit(1);
				}
			}
		}
	

		if(NumOUT){
			if (close(FileD) == -1){
				perror("error closing fileD");
				exit(1);
			}
			for (unsigned i = 0; i < NUMoutfiles.size(); i++){
				//cout << "OUTFILES ARE: " << NUMoutfiles.at(i) << endl << flush;
				if (open(NUMoutfiles.at(i), O_CREAT | O_RDWR | O_TRUNC, 0644) == -1){
					perror("Error opening in executeIO: outRedir");
					exit(1);
				}
			}
				//cout << endl;
		}
		if(NumOUTA){
			cout << "WE IN?" << endl;	
			if (close(FileDApp) == -1){
				perror("Error closing in executeIO: outRedirAppend");
				exit(1);
			}
			for (unsigned i = 0; i < NUMoutfilesA.size(); i++){
				if (open(NUMoutfilesA.at(i), O_CREAT | O_RDWR | O_APPEND, 0644) == -1){
					perror("Error opening in executeIO: outRedirAppend");
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
			if (open(data.c_str(), O_RDWR | 0644 ) == -1){
				perror("Error opening in executableIO: trippleIn");
				exit(1);
			}

			//cout << "This is the string being outputed: " << temp << endl; 
			
		}

		//for (unsigned i = 0; i < index; i++){cout<<argv[i] << " ";}cout << endl;
		if (execvp(argv[0], argv) == -1){
			perror("Error with execvp in executeIO");
			exit(1);
		}
		//errno = 0;
		exit(0);	
	}
	// if pid is not zero then we are in the parent process!	
	else if (pid > 0){
		if (wait(0) == -1){
			perror("Error waiting for child process!");
			exit(1);
		}if(TrippleIn){
			if (remove( "data.txt" ) != 0 ){
				perror( "Error deleting file" );
			}
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
		if (v.at(i)[0] >= '0' && v.at(i)[0] <= '9'){
			if (v.at(i)[1] == '>'){return true;}
		}
	}return false;
}
bool gonnaPipeOnly(vector<char*>&v){
	
	if(containsInRedir(v)){return false;}
	if(containsOutRedir(v)){return false;}
	if(containsOutRedirAppend(v)){return false;}
	if(containsTrippleIn(v)){return false;}
	if(containsOutFile(v)){return false;}
	if(containsOutFileAppend(v)){return false;}
	for(unsigned i = 0; i < v.size(); i++){if(strcmp(v.at(i),"|") == 0){return true;}}
	return false;
}
bool IOandPiping(vector<char*>&v){
	bool IO = false;
	bool piping = false;
	for(unsigned i = 0; i < v.size(); i++){
		if(strcmp(v.at(i),"|") == 0){piping = true;} 	// piping
		if(v.at(i)[0] >= '0' && v.at(i)[0] <='9'){ 	// fd IO
			if (v.at(i)[1] == '>'){
				IO = true;
			}
		}
		if(strcmp(v.at(i),"<") == 0){IO = true;} 	// inRedir
		if(strcmp(v.at(i),">") == 0){IO = true;} 	// outRedir	
		if(strcmp(v.at(i),">>") == 0){IO = true;} 	// outA Redir
		if (strcmp(v.at(i),"<<<") == 0){IO = true;} 	// string in
	}
	if (IO && piping){return true;}
	return false;
}
void piping(vector<vector<char*> >&v, int amtOfPipes){

	int fdid[2];
	pid_t fid;
	int fd_input = 0;
	char * argv[100] = {0};

	for (int i = 0; i < amtOfPipes+1; i++){
		// resets argv to null pointers
		for(unsigned ind = 0; ind < 100; ind++){argv[ind] = '\0';}
		// fills argv with the .at(i) arguments
		for(unsigned k = 0; k < v.at(i).size(); k++){
			argv[k]  = v.at(i).at(k);
		}
		
		pipe(fdid);
		if ((fid = fork()) == -1){
			perror("Fork failed in piping!");
			exit(1);
		}
		else if (fid == 0){
			if (dup2(fd_input,0) == -1){
				perror("stuff went wrong in dup2() in Piping");
				exit(1);
			}
			if (i < amtOfPipes){
				if (dup2(fdid[1], 1) == -1){
					perror("Shit went wrong int dup2() at the end of pipng");
					exit(1);
				}
			}
			if (close(fdid[0]) == -1){
				perror("Could not close in piping");
				exit(1);
			}
			if (execvp(argv[0], argv) == -1){
				perror("Failure in execvp in piping!");
				exit(1);
			}
			exit(1);
		}
		else {
			if (wait(NULL) == -1){
				perror("Error waiting on child");
				exit(1);
			}
			if (close(fdid[1]) == -1){
				perror("Error closing fdid[1]");
				exit(1);
			}
			fd_input = fdid[0];
		}
	}
}
// this function gets the file descriptor when user inputs #> (i.e. does NOT append to output)
int getFD(vector<char*> & v){
	for(unsigned i = 0; i < v.size(); i++){
		if(v.at(i)[0] >= '0' && v.at(i)[0] <= '9'){
			if (v.at(i)[1] == '>'){
				if (v.at(i)[2] == '>'){return 0;}
				else {
					return v.at(i)[0] - 48;
				}
			}
		}
	}
	return 0;
}
// this functions gets the file descriptor when user inputs #>> (i.e. APPENDS to output)
int getFDA(vector<char*> & v){
	for(unsigned i = 0; i < v.size(); i++){
		if(v.at(i)[0] >= '0' && v.at(i)[0] <= '9'){
			if (v.at(i)[1] == '>'){
				if (v.at(i)[2] == '>'){
					return v.at(i)[0] - 48;
				}
			}
		}
	}
	return 0;
}
bool isNum (char data){
	if (data >= '0' && data <= '9'){return true;} return false;
}
string spaceCheck(string commands){
	
	string newCommands = "";
	for(unsigned i = 0; i < commands.size(); i++){
		if(commands.at(i) == '<' && i+1 < commands.size() && commands.at(i+1) != '<' && i+1+1 < commands.size() && commands.at(i+1+1) != '<'){
			if (i+1 < commands.size() && commands.at(1+i) != '<' && commands.at(i-1) != '<'){
				newCommands+= ' '; // input redir
				newCommands+= '<';
				newCommands+= ' ';
			}
		}
		else if (commands.at(i) == '>' && i+i < commands.size() && commands.at(i+1) != '>' && commands.at(i-1) != '>'){
			if (i-1 > 0 && isNum(commands.at(i-1)) == false) {
				newCommands+= ' '; // output redir
				newCommands+= '>';
				newCommands+= ' ';
				cout << "Added one output carrot" << endl;
			}
		}
		else if (commands.at(i) == '>' && i-1> 0 && !(commands.at(i-1) >= '0') && !(commands.at(i-1) <= '9')){
			if(i+1 < commands.size() && commands.at(i+1) == '>'){ 
				newCommands+= ' '; // output redir append
				newCommands+=">>";
				newCommands+= ' ';
			}
		}
		else if (commands.at(i) == '<' && i+i < commands.size()){
				if(commands.at(i+1) == '<' && i+1+1 < commands.size()){
					if (commands.at(i+1+1) == '<'){ // string input
						newCommands+= ' ';
						newCommands+= "<<<";
						newCommands+= ' ';
					}
				}
		}
		else if (commands.at(i) == '|' && i+1 < commands.size() && commands.at(i+1) != '|'){
			newCommands+= ' ';	// piping
			newCommands+= '|';
			newCommands+= ' ';
		}
		else if(commands.at(i) >= '0' && commands.at(i) <= '9'){
			if (i+1 < commands.size() && commands.at(i+1) == '>' && i+1+1< commands.size() && commands.at(i+1+1) != '>'){
				cout << "WE IN" << endl; // fd out
				newCommands+= ' ';
				newCommands+= commands.at(i);
				newCommands+= '>';
				newCommands+= ' ';
			}
		}
		else if (commands.at(i) >= '0' && commands.at(i) <= '9'){
			if(i+1 < commands.size() && commands.at(i+1) == '>' && i+1+1 < commands.size() && commands.at(i+1+1) == '>'){
				newCommands+= ' ';
				cout << "NUM IS: " << commands.at(i) << endl;
				newCommands+= commands.at(i); // fd out append
				newCommands+= ">>";
				newCommands+= ' ';
			}
		}
		else {
			newCommands+=commands.at(i);
		}
	}
	return newCommands;
}

string mutate(char * data){
	return string(data);	
}

void printCWD(){

	char * username = getlogin();
	if (username == NULL){
		perror("Error getting login");
		exit(1);
	}
	string user = mutate(username);
		
	// this gets the current working directory and prints it
	char buff[1000] = {0};
	char * CWD;
	CWD = getcwd(buff, 1000);
	if (CWD == NULL){
		perror("PRINT WORKING DIRECTORY");
		exit(1);
	}
	string currDir = mutate(CWD);	
	size_t found = currDir.find(user);
	if (found != string::npos){
		currDir.erase (currDir.begin(), currDir.begin()+found+user.size());
		string home = "~";
		//if (currDir.size() == 0){home += "/";}
		home = home + currDir;
		if (home == "~"){
			cout << home << " $ ";
		}
		else {
			cout << home << "$ ";
		}
	}
	else {
		cout << CWD << "$ ";
	}
}

// global variables to be used for cd
char memory [1000] = {0};
char * OLDWD = '\0';	
char home[3] = {'~','/','\0'};

void cd(vector<char*> & v){
	
	// if only cd
	if (v.size() == 1 && strcmp(v.at(0), "cd") == 0){
		for(unsigned i = 0; i < 1000; i++){memory[i] = '\0';}
		OLDWD = getcwd(memory, 1000);
		if (OLDWD == NULL){perror("OLDWD"); return;}
		if (chdir(getenv("HOME")) == -1){
			perror("cd");
			return;
		}	
	} // if got back to last path
	else if (v.size() == 2 && strcmp(v.at(0),"cd") == 0 && strcmp(v.at(1), "-") == 0){

		// if no previous directory then set to home
		if (OLDWD == '\0'){OLDWD = home;}
		
		// get the current working directory
		char newMem[1000] = {0};
		char * NewWd = '\0';
		NewWd = getcwd(newMem,1000);
		if (NewWd == NULL){perror("NewWd"); return;}
		// move old directory into a string
		string directory = "";
		unsigned i = 0;
		while(OLDWD[i] != '\0'){
			directory+= OLDWD[i];
			i++;
		}

		// set new directory to previously visted directory
		if (chdir(directory.c_str()) == -1){
			perror("cd -");
			return;
		}
	
		// set old directory to last visited directory;
		for(unsigned i = 0; i < 1000; i++){
			memory[i] = newMem[i];
		}
		unsigned k = 0;
		while (NewWd[k] != '\0'){
			OLDWD[k] = NewWd[k];
			k++;
		}
	}
	else if (v.size() == 2 && strcmp(v.at(0),"cd") == 0){
		
		for(unsigned i = 0; i < 1000; i++){memory[i] = '\0';}
		OLDWD = getcwd(memory,1000);
		if (OLDWD == NULL){perror("OLDWD");return;}
		// if the path is simple a tilde then go home
		if (strcmp(v.at(1),"~") == 0 || strcmp(v.at(1),"~/") == 0){
			if (chdir(getenv("HOME")) == -1){
				perror("cd ~");
				return;
			}
			return;
			
		}
		// if it's path that starts with ~/ and then has more
		if (v.at(1)[0] == '~' && v.at(1)[1] == '/' && v.at(1)[2] != '\0'){
			unsigned i = 2;
			string dir = "";
			while(v.at(1)[i] != '\0'){
				dir+= v.at(1)[i];
				i++;
			}
			if (chdir(getenv("HOME")) == -1){
				perror("first cd");
				return;	
			}
			if(chdir(dir.c_str()) == -1){
				perror("second cd");
				return;
			}
			return;
		}
		// if a path that doesn't include ~/ then proceed here
		if (chdir(v.at(1)) == -1){
			perror("cd <PATH>");
			return;
		}
		
	}
	else {
		cout << "Error! invalid arguments" << endl;
		return;
	}		
}


bool tokenizeInput(std::string commands){

	std::vector<char *> v;
	std::vector<int> index;
	std::vector<int> linkers;
		
	// supports up to a 99,999 character command input
	char tokenArray[10000] = {'\0'};
	const char deliminator[2] = {' ', '	'};
	char * token;
	std::string modifiedCommands;

	modifiedCommands = commentChecker(commands);
	modifiedCommands = connectorChecker(modifiedCommands);
	//modifiedCommands = spaceCheck(modifiedCommands);

	//cout << "new commands are: " << modifiedCommands << endl;
		
	for (unsigned i = 0; i < modifiedCommands.size(); i++){
		//cout << modifiedCommands.at(i) << endl;
		tokenArray[i] = modifiedCommands.at(i);
	}
	
	//cout << "MOD COMMANDS: " << modifiedCommands << endl;
	
	token = strtok(tokenArray, deliminator);
	while(token != NULL){
		v.push_back(token);
		token = strtok(NULL, deliminator);
	}
	
	//printVec(v);
	
	// if only comments then no need to execute any commands, return
	if (v.size() == 0){return false;}
	// if exit then exit
	if (strcmp(v.at(0), "exit") == 0){return true;}

	if (strcmp(v.at(0),"cd") == 0){
		// goto cd function
		cd(v);
		return false;
	}


	if (containsLogic(v)){
		//cout << "THE COMMANDS AREW: " << endl;
		//printVec(v);
		divideExecute(v);
		return false;
	}
	else if (containsOtherLogic(v)){
		
		if (IOandPiping(v)){
			cout << "ERROR: rshell cannot yet support piping and I/O redirection together!" << endl;
			return false;	
		}
		if (gonnaPipeOnly(v)){
			//cout << "WE here!!!!!" << endl;
			int amtOfPipes = 0;
			for(unsigned i = 0; i < v.size(); i++){
				if (strcmp(v.at(i),"|") == 0){amtOfPipes++;}
			}
			
			//printVec(v);
			vector<vector<char*> > Commands;
			vector<char*> temp;
			
			for (unsigned index = 0; index < v.size(); index++){
				
				if (strcmp(v.at(index),"|") != 0){
					temp.push_back(v.at(index));
				}
				if (strcmp(v.at(index),"|") == 0 || index == v.size() - 1){
					Commands.push_back(temp);
					temp.clear();
				}
			}
			piping(Commands, amtOfPipes);
			return false;
		}	
		
		// cout << "WE ARE IN NICCA!" << endl;	
		// if piping then go to piping function
		bool inRedir  = containsInRedir(v);
		bool outRedir = containsOutRedir(v);
		bool outRedirAppend = containsOutRedirAppend(v); 
		bool comeInside3 = containsTrippleIn(v);	
		bool numOut = containsOutFile(v);
		bool numOutA = containsOutFileAppend(v);
		bool pipingAfter = IOandPiping(v);		

		vector<char*> infiles; 		// vector of all input files
		vector<char*> outfiles;		// vector of all output files
		vector<char*> outfilesAppend;	// vector of all output files that append
		vector<char*> trippleIn;	// vector that contains the input string if <<<
		vector<char*> newCommands;	// vector of new commands
		vector<char*> NumOutFiles;	// vector of fd out files to whatever #> is detected
		vector<char*> NumOutFilesApp;	// vector of fd out files that append to whatever #>> is detected		
		int FDout = getFD(v);
		int FDoutApp = getFDA(v);
		
		// this processes all the information into its respective data containers
		processOutInAppend(v,infiles,outfiles,outfilesAppend, trippleIn,NumOutFiles, NumOutFilesApp, newCommands);	
		// this is the command array. It only supports up to a 99 char command(s)
		char * ar[100] = {0};

		// this puts all the new commands into the array
		for(unsigned i = 0; i < newCommands.size(); i++){ar[i] = newCommands.at(i); /*cout << newCommands.at(i) << " ";*/}
		// this executes all the commands and does all the input/output redirection
		executeIO(ar,inRedir, outRedir,outRedirAppend,comeInside3, numOut, numOutA,infiles,outfiles, outfilesAppend, trippleIn, NumOutFiles, NumOutFilesApp, FDout, FDoutApp, pipingAfter);

		// do piping after shiz
		

		return false;
	}
	else {
		printVec(v);
		if (executeCommands(v) == 0){
		}
		return false;
	}
	return false;	
}

#endif 
