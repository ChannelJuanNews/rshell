#Rshell bash terminal emulator
Rshell is a simple bash terminal emulator that carries out commands similar to a Unix bash terminal.

##Installation
Installation is simple! Just run the following commands.
```
$ git clone https://github.com/jruel006/rshell.git
$ cd rshell
$ git checkout hw0
$ make
$ bin/rshell
```
*** When exiting rshell with the `exit` command, make will automatically delete the bin folder for you ***

##Bugs, behaviors, and limitations

* ``$ false && false && ls -a || pwd`` : This command will only run `ls -a` when it should instead only run pwd. Same goes for other commands of this nature (i.e. `false && false && ls ; pwd`).

* ``$ rshell `` : Launching a new rshell session within rshell WILL work (just use the `rshell` command), however it will report an error, but it works! 

* ``$ rshell && pwd `` :  Launching a new rshell session AND executing a command will crash rshell. This goes for any linking when FIRST launching a new session AND THEN executing commands. If executing commands FIRST, AND THEN launching a new session at the end WILL work (i.e. `ls && rshell`) as long as `rshell` is the LAST command executed, but it will report an error due to the previous bug. 

* ``$ echo "Message && Message" `` : Will echo `"Message "` and then result in an error when program arrives at the `&&`. Bascically you cannot include connectors when echoing. 

* ``$ cat > FILENAME `` : This command will result in an error instead of creating a file. 

* ``$ # this is a comment `` : This command will crash rshell. Comments will only work if there is a command before it. 

* Arrows for command history not supported (same goes for special commands like `Ctrl - c`)

* ``cd`` not supported.

* If rshell crashes while in session, you can either re-run rshell by typing `bin/rshell` OR delete the `bin` directory with `rf -rf bin` and then using `make` to relaunch rshell. 
Alternatively, you can edit the makefile so it won't delete the `bin` directory upon successful exiting so every time you want to launch a new session OUTSIDE of rshell you run `bin/rshell` from the root directory. 

NOTE: While this may not be a perfect implementation of an actual shell/terminal, it is pretty chill. If you would like to contribute to this just fork it and fix my bugs LOLOLOLOLOL
