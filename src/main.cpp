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



int main(int argc, char * argv[] ) {
		
	clearScreen();
	rshellMessage();
	string commands;
	unsigned loopCounter = 0;
	
	if (SIG_ERR == signal(SIGINT, handleSig)) {
		perror("Trapping SIGINT");
		exit(1);
	}
	if (SIG_ERR == signal(SIGTSTP, handleSig)) {
		perror("Trapping SIGTSTP");
		exit(1);
	}
	
	while(true){
	
		DisplayUserHost(loopCounter);
		getline(std::cin, commands);
		if (commands ==  "exit"){exit(0);}
		if (tokenizeInput(commands) == true){exit(0);}
		loopCounter++;
	}
	
	
	return 0;
}
