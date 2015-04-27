<<<<<<< HEAD
# rshell-2.0
Remake of original shell bash terminal emulator.
=======
#Rshell bash terminal emulator
>>>>>>> 9a02ecb3a27d47571458525a44dafdd00f5cdfd9
Rshell is a simple bash terminal emulator that carries out commands similar to a Unix bash terminal.


##Installation
Installation is simple! Just run the following git commands.
```
<<<<<<< HEAD
$ git clone https://github.com/jruel006/rshell.git
$ cd rshell
$ git checkout hw0
$ make
```
*** When exiting rshell with the `exit` command, make will automatically delete the bin folder for you ***

##Bugs, behaviors, and limitations

* ``$ false && false && ls -a || pwd`` : This command will only run `ls -a` when it should instead only run pwd. Same goes for other commands of this nature (i.e. `false && false && ls ; pwd`).

* ``$ rshell `` : Launching a new rshell session within rshell WILL work (just use the `rshell` command), however it will report an error, but it works! 

* ``$ rshell && pwd `` :  Launching a new rshell session AND executing a command will crash rshell. This goes for any linking when FIRST launching a new session AND THEN executing commands. If executing commands FIRST, AND THEN launching a new session at the end WILL work (i.e. `ls && rshell`) as long as `rshell` is the LAST command executed, but it will report an error due to the previous bug. 

* ``$ echo "Message && Message" `` : Will echo `"Message "` and then result in an error when program arrives at the `&&`. Bascically you cannot include connectors when echoing. 

* ``$ cat > FILENAME `` : This command will result in an error instead of creating a file. 

* Arrows for command history not supported (same goes for special commands like `Ctrl - c`)

* ``cd`` not supported.

* If rshell crashes while in session, you can either re-run rshell by typing `bin/rshell` OR delete the `bin` directory with `rf -rf bin` and then using `make` to relaunch rshell. 
Alternatively, you can edit the makefile so it won't delete the `bin` directory upon successful exiting so every time you want to launch a new session OUTSIDE of rshell you run `bin/rshell` from the root directory. 

NOTE: Over all there are MANY bugs in this emulator, but standalone commands work, just need to improve the linking. 

=======
$ git clone https://github.com/jdixo001/rshell.git
$ cd rshell
$ git checkout hw0
$ make
$ bin/rshell
```
##Bugs, behaviors, and limitations

* ``$ ls -a && ls ``:  This command will only execute the last one after the alst '&&' (e.g. `pwd; pwd && pwd` will only print the working directory once)

* ``$ pwd | pwd``   :  Results in an error rather than reading the commands. (this goes for all `|` like commands)

* `` ls; ls``       :  Follows the same behavoir as the `&&` command.

* ``cd`` not supported.

* Cannot support major linkage (e.g. ``pwd && false && ls ; pwd``)

* Arrows for command history not supported (same goes for special commands like `Ctrl - c`)

* Doesn't crash if rshell runs rshell within itself, however, you will need to exit as many times as you opened a new session


NOTE: Over all there are MANY bugs in this emulator, but standalone commands work, just need to improve the linking. 
>>>>>>> 9a02ecb3a27d47571458525a44dafdd00f5cdfd9
