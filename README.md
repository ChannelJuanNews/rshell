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

##ls: Bugs, Behaviors and limitations

* ``ls optional file directory of not a directory``: will result in an error

* Multiple files and directories are not listed gracefully for a large nummber of files/directories

* ``-R``: Command not supported. This goes for any mixture of flags that contain this flag. 

* The green color for executable files only works for a small amount of time. When make is ran, bin/ls is called on bin and all executable files are green. However succesive calls to ``bin/ls bin`` will result in a blue coloring, rather than green. 

##Piping & I/O Redirection: Bugs, Behaviors and limitations

* `ls -a > file1 > file2 > file3` : will only output to first file and not to the third one like bash handles that case.

* Does NOT support any linkage between piping and I/O redirection
(i.e. ` cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2`)

# Extra credit

* `cat <<< "this is a test"`: works, as well with any variation of that that does not invlolve piping.
(i.e. `grep this <<< "this is a test"` and `grep this <<< "this is a test" > outfile.txt`)
* `g++ error.cpp 2> error.txt`: works, as well as any variant of that with any file descriptor with `>` and `>>`
(i.e. `g++ helloWorld.cpp -o hello.out` && `hello.out 1> hello.txt`. hello.txt will now contain the output of hello.out) 

## New edition: cd and signals

* `cd` command now supported! Alone it will return you to your `home` directory.

* supports `cd <path>` to change to a directory in the path

* supports `cd -` commands to return to previous working directory

* supports the `^C` command

# Known cd && signal bugs

* when going to `home` directory you must place a `/` in front of home

* `^C` signal works just fine. No known bugs.


NOTE: While this may not be a perfect implementation of an actual shell/terminal, it is pretty chill. If you would like to contribute to this just fork it and fix my bugs LOLOLOLOLOL
