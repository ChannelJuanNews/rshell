#Rshell bash terminal emulator
Rshell is a simple bash terminal emulator that carries out commands similar to a Unix bash terminal.


##Installation
Installation is simple! Just run the following git commands.
```
$ git clone https://github.com/jdixo001/rshell.git
$ cd rshell
$ git checkout hw0
$ make
$ bin/rshell
```
##Bugs, behaviors, and limitations

* ``$ ls -a && ls ``:  This command will only execute the last one after the alst '&&' (e.g. `pwd; pwd && pwd` will only
*                   :  print the working directory once)

* ``$ pwd | pwd``   :  Results in an error rather than reading the commands. (this goes for all `|` like commands)

* `` ls; ls``       :  Follows the same behavoir as the `&&` command.

* ``cd`` not supported.

* Cannot support major linkage (e.g. ``pwd && false && ls ; pwd``)

* Arrows for command history not supported (same goes for special commands like `Ctrl - c`)

* Doesn't crash if rshell runs rshell within itself, however, you will need to exit as many times as you opened a new session


NOTE: Over all there are MANY bugs in this emulator, but standalone commands work, just need to improve the linking. 
