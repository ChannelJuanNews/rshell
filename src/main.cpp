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
#include "functions.h"
#include <signal.h>

using namespace std;

static void sigHandler(int signal, siginfo_t * signalInformation, void * randomPointer){
	
	if (signal == SIGCHLD){
		//kill (getpid(), SIGCHLD);
		while (waitpid(-1, NULL, WNOHANG) > 0) {
			exit(1);
		}
		return;
	}
	if (signal == SIGINT){
		wait(0); // this fixes a bug when calling a program with execvp and then stopping it with the sighandler
		cout << endl;
		return;
	}
	else if (signal == SIGTSTP){
		// do ^Z stuff here	
		cout << endl;
		system("bin/rshell");
		raise(SIGSTOP);
		return;
	}
	else {
		cout << "Error! Cannot support this signal overloading!" << endl;
		return;
	}
	
}

int main(int argc, char * argv[] ) {		
	
	struct sigaction NewAct = {0}; // better way to initialzie the struct. Better then memset.
	struct sigaction OldAct = {0};
	sigset_t block_mask;
	NewAct.sa_mask = block_mask;
	NewAct.sa_sigaction = sigHandler; // this assigns the sigHandler function as the defualt function
	//NewAct.sa_flags = SA_RESTART;
		
	if (sigaction(SIGINT, &NewAct, &OldAct) == -1){  // calls and error checks sighandler function for SIGINT
		perror("SIGINT sigaction");
	} 
	if (sigaction(SIGTSTP, &NewAct, &OldAct) == -1){ // calls and error checks sighandler function for SIGTSTP
		perror("SIGTSTP sigaction");
	}
	
	if (sigaction(SIGCHLD, &NewAct, &OldAct) == -1){ // calls and error checks sighandler function for SIGCHLD 
		perror("SIGCHLD sigaction");
	}
	

	//clearScreen();
	//rshellMessage();
	string commands = "";
	unsigned loopCounter = 0;

	while(true){
		
		cin.clear();
		printCWD();
		//DisplayUserHost(loopCounter);
		getline(std::cin, commands);
		if (commands == "exit"){
		cout << "you have looped " << loopCounter << " times" << endl;
			exit(0);
		}
		if (tokenizeInput(commands) == true){exit(0);}
		loopCounter++;
	}
	
	
	return 0;
}
