# EMA
E.xtremely M.odular A.PI

### How to compile this project:

If this is being compiled on the Bash For Windows Subsystem, make sure to follow [these](https://solarianprogrammer.com/2017/05/04/building-gcc-wsl-windows-subsystem-linux/) steps.
If this is being compiled on linux, change "g++-7.1" in the Makefile to "g++"

First, clone the repo.  From inside EMA/, run the command "make", this will build the PluginManager/Compiler, which will assist in building the rest of the game.
 - Note: This will only compile with versions of gcc that support c++17.
 
 Now that you have the compiler, you can use the help menu in that interface to learn about the various commands that you can use.  In short: ```enable <pluginName>``` for whatever plugins you want to use, ```save``` that list so you don't have to enable all the plugins you want every time, ```compile```, then ```exit```.
 
---
 
 Alternatively, one can create their own compile command in the structure of:
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
