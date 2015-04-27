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

using namespace std;

int main(int argc, char * argv[] ) {
		
	clearScreen();
	rshellMessage();
	string commands;
	unsigned loopCounter = 0;
	bool loop = true;
	vector <char *> v(0);
	vector <char *> current(0);

	
	while(loop){
		
		DisplayUserHost(loopCounter);
		getline(std::cin, commands);
		v.clear();
		if (tokenizeInput(commands) == true){exit(0);}
		loopCounter++;
	}
	
	
	return 0;
}
