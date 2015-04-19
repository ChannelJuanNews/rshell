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

using namespace std;

// function that contains the welcom message. To be called only once per session
void rshellMessage() {
	
	cout << "              ==================================================               " << endl;
	cout << "                              Welcome to rshell! :)                            " << endl;
	cout << "              ==================================================               " << endl;
	cout << "                                                                               " << endl;
	cout << "===============================================================================" << endl;
	cout << "|                                                                             |" << endl;
	cout << "| You have enabled settings specific for my cs100 hw0 w/ Mike Izbicki         |" << endl;
	cout << "| I will not be recording anything because I don't know how to.               |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "| Important commands for this bash emulator                                   |" << endl;
	cout << "|   * gradeWishlist       displays the grade I want in your class             |" << endl;
	cout << "|   * typeSlow            practice typing as slow as possbile                 |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "| Important commands for general A+- programming:                             |" << endl;
	cout << "|   * cake                  displays a picture of a char cake                 |" << endl;
	cout << "|   * std                   don't catch one of those                          |" << endl;
	cout << "|   * onTheGrind            that's what i've been doing all week              |" << endl;
	cout << "|   * pcpset                i've been halucinating about finishing this       |" << endl;
	cout << "|   * woman                 don't find out about commands. She wont tell you  |" << endl;
	cout << "|                                                                             |" << endl;
	cout << "|                   Type the command 'exit' to exit rshell                    |" << endl;
	cout << "===============================================================================" << endl;

}

// function to clear the screen (terminal) 
void clearScreen() {
	#define del() printf("\033[H\033[J");
	del();
}

void DisplayUserHost() {
	
	char * userName = getlogin();
	cout << userName;
	cout << '@';

	// char array stores up to 99 character host name
	// with size[100] reserved for the null character
	char size[100];
	int result;

	result = gethostname(size, 100);

	if (result == -1){
		perror("Could not retrieve host name");	
	}
	int i = 0;
	while (size[i] != '\0') {
		cout << size[i];
		i++;	
	}	
}

void executeCommands(vector<char *> & v) {

	// convert vector of char pointers to array of char pointers
	// Can only store up to 10,000 commands
	char * argv[10000] = {0};

	for (unsigned i = 0; i < v.size(); i++){
		argv[i] = v.at(i);
	}

	int pid = fork();
	unsigned index = 0;
	
	if (pid == -1) {
		// if fork() returns -1 then there was an error
		perror("There was an error with fork()");
		exit(1);
	}
	else if (pid == 0) {
		
		if (-1 == execvp(argv[index], argv)){
			perror("There was an error in execvp");	
		}
			
	}
	// if pid > 0 then we are not in the child process (e.g. parent)
	else if (pid > 0){
		
		if (wait(0) == -1){
			perror("There was an error with wait() in parent function");
		}
	}		
}

void tokenizeInput(string commands) {

	// supports up to a 9,999 character command/character count of commands
	char tokenArray[10000]  = { 0 };
	const char  deliminator[2] =  { ' ' } ;
	char * token;	
	vector<char *> v;

	
	// fills the token array with the entire input
	unsigned i;
	for (i = 0; i < commands.size(); i++) {
		tokenArray[i] = commands.at(i);
	}
	tokenArray[i+1] = '\0';

	// creates the CONST array to be passed into strtok() function

	// captures the first token and continues until end of string
	// then stores all of the tokens in a char * vector
	token = strtok(tokenArray, deliminator);
	while (token != NULL) {
		//cout << token << " ";
		v.push_back(token);
		// sends token to be executed
		token = strtok(NULL, deliminator);
	}
	executeCommands(v);
}


int main( int argc, char * argv[] ) {
	
	clearScreen();
	// displays the welcome message
	rshellMessage();
	string commands;
	
	while (1) {

		// userInfo displayed before prompt
		cout << endl;
		DisplayUserHost();
		cout << "$ ";		
		getline(cin,commands);
		tokenizeInput(commands);
	}	
	return 0;	
}










