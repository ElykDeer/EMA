# EMA
E.xtremely M.odular A.PI

### How to compile this project:

Mac, Linux, and Windows are intended to be supported.  So far, Linux and Windows work.

#### Required
 - A version of g++ that support c++17 (I use 7.2.0)
 - apt (you'll need to edit the Makefile for other package managers)

#### All OS's
Clone the repo.  From inside EMA/, run the command "make" (or "make linux" if not compile on the Bash For Windows Subsystem), this will build the PluginManager/Compiler, which will assist in building the rest of the game.

#### Windows
 - First time:
 Run: ```make firstTimeLXW; make LXW```
 - Subsequent times:
 Run: ```make LXW```
 - Explanation:
 ```make firstTimeLXW``` gets the necessary dependencies to compile the compiler.
 ```make LXW``` compiles the compiler

#### Linux
- First time:
Run: ```make firstTimeLXL; make LXL```
- Subsequent times:
Run: ```make LXL```
- Explanation:
```make firstTimeLXL``` gets the necessary dependencies to compile the compiler.
```make LXL``` compiles the compiler

#### All OS's
Now that you have the compiler, you can use the help menu in that interface to learn about the various commands that you can use.  In short: ```enable <pluginName>``` for whatever plugins you want to use, ```save``` that list so you don't have to enable all the plugins you want every time, ```compile```, then ```exit```.

---

### Alternatively,
one can create their own compile command in the structure of:
```bash
g++ -Wall -Wextra -pedantic -std=c++1y <Main/Internal Dependencies> <Plugin Dependencies> -o main
```
...making sure that "Compiler/pluginTypes.h" has/includes all types defined in desired plugins, for example use this file:
```c++
    #ifndef SIM_PLUGIN_TYPES
    #define SIM_PLUGIN_TYPES 1
    #include "../Plugins/datTest/datTestTypes.h"
    #endif
```
...with this command:
```bash
g++ -Wall -Wextra -pedantic -std=c++1y Main/main.cpp Main/dataStructure.cpp Main/Entity.cpp Plugins/datTest/datTestTypes.cpp -o main
```
(please just use the compiler)
