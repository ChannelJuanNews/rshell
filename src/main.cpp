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
	
	
	
}

struct sigaction act;

int main(int argc, char * argv[] ) {
		
	clearScreen();
	rshellMessage();
	string commands;
	unsigned loopCounter = 0;
	
	/*
	memset(&act, '\0', NULL);
	act.sa_sigaction = sigHandler;
	act.sa_flags = SA_SIGINFO;
	if (sigaction (SIGINT, &act, NULL) == -1){
		perror("SIGINT sigaction");
	}*/


	
	while(true){
	
		DisplayUserHost(loopCounter);
		getline(std::cin, commands);
		if (commands ==  "exit"){exit(0);}
		if (tokenizeInput(commands) == true){exit(0);}
		loopCounter++;
	}
	
	
	return 0;
}
