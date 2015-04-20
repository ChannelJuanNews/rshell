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

void DisplayUserHost(unsigned loopCounter) {
	
	char * userName = getlogin();
	cout << userName;

	// char array stores up to 99 character host name
	// with size[100] reserved for the null character
	char size[100];
	int result;

	result = gethostname(size, 100);

	if ((result == -1) &&(loopCounter < 1)){
		perror("Could not retrieve host name");	
	}
	else {
		cout << '@';
		int i = 0;
		while (size[i] != '\0') {
			cout << size[i];
			i++;	
		}
	}
	cout << "$ ";	
}


int executeCommand(vector<char*> & v){

	// convert vector of char pointers to array of char pointers
	// Can only store up to 10,000 commands
	char * argv[10000] = {0};
	
	// created null terminated array of of commands and arguments
	unsigned i;
	for (i = 0; i < v.size(); i++){ argv[i] = v.at(i);}
	argv[i+1] = NULL;	
	
	// creates a fork
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
			for (unsigned i = 0; i < v.size(); i++){
			cout << "-bash: " << argv[i] << ": command not found";
			return -1 ;
			}		
		}	
	}
	// if pid > 0 then we are not in the child process (e.g. parent)
	else if (pid > 0){
		
		if (wait(0) == -1){
			perror("There was an error with wait() in parent function");
		}
	}		
	return 1;
}

// returns true if any of the commands are linked
string containsLogic(char * v) {
	
	unsigned i = 0;
	char boolAnd[3] = {'&', '&'}; string AND = "&&";
	char boolOr[3] = {'|','|'}; string OR = "||"; 
	/*char connector[2] = {';'};*/ string CONNECTOR = ";";
	string failed = "no logic";
	
	// checks for && or || or ;
	while (v[i] == boolAnd[i]) { if (i == 2) { return AND;} i++; } i = 0;
	while (v[i] == boolOr[i]) { if (i == 2) {return OR;} i++; } i = 0;
	while (v[i] != '\0') { if(v[i] == ';'){ return CONNECTOR;} i++; }
	
	return failed;
}

template <typename T>
void pop_front(vector<T> & v){
	
	if (v.size() > 1) {
		std::rotate(v.begin(),v.begin()+1,v.end());
	}
	v.pop_back();
}	

string convertChar(char * data) {return string(data);}

int divideCommands(vector<char *> & v) {

	string output;
	vector<string> capturedLogic;
	vector<string> commands;	
	vector<char * > currentCommand;
	
	// loop that checks to see if vector of commands contains any connectors
	// and captures them in order in a vector
	for (unsigned i = 0; i < v.size(); i++){
		output = containsLogic(v.at(i));
		currentCommand.push_back(v.at(i));
		
		// if the commands have no connectors then execute the commands and
		// leave
		if (output == "no logic"){;
		} 
		else if (output == ";"){
			
			unsigned moveOver = 0;
			while(v.at(i)[moveOver] != '\0'){
				moveOver++;
			}
			v.at(i)[moveOver - 1] = v.at(i)[moveOver];
			//insertAnd(v, i);
			//cout << "This command contians a link" << endl;
			currentCommand.push_back(v.at(i));
			pop_front<char*>(v);
			//cout << "After popping off: " << v[0] << endl;
			executeCommand(currentCommand);
			divideCommands(v);
			capturedLogic.push_back(";");
			return 1;
		}
		else { capturedLogic.push_back(output);}
		
	}
	

	
	// if no logic has been captured then execute the inputted command
	if (capturedLogic.size() == 0){
		executeCommand(v);
		 return 1;
	}
	

	
	// converts the char arrays into vectors of strings
	for (unsigned index = 0; index < v.size(); index++){
		commands.push_back(convertChar(v.at(index)));
		//cout << commands.at(index) << " ";
	}	
	cout << endl;	

	for ( unsigned x = 0; x < commands.size(); x++){
		
		if (commands.at(x) == "&&"){
			break;	
		}
		else if (commands.at(x) == "||"){
			break;
		}
	
		//cout << "Command to be added: ";
		cout << v[x] << endl;
		if (convertChar(v[x]) == " &&" || convertChar(v[x]) == "||"){
			currentCommand.pop_back();	
		} 
		currentCommand.push_back(v[x]);
		pop_front<char*>(v);
		currentCommand.push_back(v[0]);
		if (convertChar(v[0]) == "&&" || convertChar (v[0]) == "||"){
			currentCommand.pop_back();
			
		}	
		//cout<< "new command at top: " << v[0] << endl;
	}	
	
	//cout << "Current Command: ";	
	for (unsigned cc = 0; cc < currentCommand.size(); cc++){
		//cout << currentCommand[cc];
	}
	
	// puts updated a command array into vector
	commands.clear();
	for (unsigned ind = 0; ind < v.size(); ind++){
		commands.push_back(convertChar(v.at(ind)));
	}	
	
	// executeCommands returns -1 if failed else we are good :)
	if (commands.at(0) == "&&"){
		
		executeCommand(currentCommand);	
		pop_front<char *>(v);
		divideCommands(v);
		return 1;
	}	
	if (commands.at(0) == "||") {
		int status = executeCommand(currentCommand);
		if (status != -1) {
			pop_front<char*>(v);
			pop_front<char*>(v);
			divideCommands(v);
			return 1;
		}
		else { pop_front<char *>(v); divideCommands(v); return 1;}
	}
	
	return 1;
}

bool tokenizeInput(string commands) {

	// supports up to a 9,999 character command/character count of commands
	char tokenArray[10000]  = { 0 };
	const char  deliminator[2] =  { ' ' } ;
	char * token;	
	vector<char *> v(0);
	//char EXIT[5] = {'e','x','i','t'};
	
	// fills the token array with the entire input
	unsigned i;
	for (i = 0; i < commands.size(); i++) {
		tokenArray[i] = commands.at(i);
	}
	tokenArray[i+1] = '0';
	
	// captures the first token and continues until end of string
	// then stores all of the tokens in a char * vector
	token = strtok(tokenArray, deliminator);
	while (token != NULL) {
		//cout << token << " ";
		v.push_back(token);
		// sends token to be executed
		token = strtok(NULL, deliminator);
	}
	// if only one command is entered and it is "exit" then exit
	
	if (commands == "exit") {return false;}
	
	divideCommands(v);
	return true;
}


void displayFarewellMessage() {
	
	
}

int main( int argc, char * argv[] ) {
	
	clearScreen();
	// displays the welcome message
	//rshellMessage();
	string commands;
	unsigned loopCounter = 0;
	bool loop = true;	
	
	while (loop) {

		// userInfo displayed before prompt
		cout << endl;
		DisplayUserHost(loopCounter);
		getline(cin,commands);
		if (commands == "exit") {exit(0);}
		if (tokenizeInput(commands) == false ){return 0;}
		loopCounter++;
	}
	
	displayFarewellMessage();	
		
	return 0;	
}


