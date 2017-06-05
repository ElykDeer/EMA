//This is the program that is supposed to pull together the resources of the
  //various pluggins and compile them before runtime

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
using namespace std;

//c++17
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

//Can paint in various colors on linux
/* Short Color Reference:
 * -30 - Normal
 * -25 - Blink
 * 1 - Red
 * 2 - Green
 * 3 - Yellow
 * 4 - Blue
 */
#ifdef _WIN32
  void startPaint(const int color) {}
  void endPaint() {}
#else
  void startPaint(const int color)
  {
    cout << "\033[" << color+30 << "m";
  }
  void endPaint()
  {
    cout << "\033[0m";
  }
#endif


//Open a file
void readFile(string filename) //Copy, so can be changed
{
  ifstream file(filename);
  while (!file)
  {
    //Prompt for another file, or not
    char tryAgain;
    startPaint(1);
    cerr << filename << " failed to open. Would you like to try another file? (Y/n) ";
    endPaint();
    cin >> tryAgain;

    //If no, exit program
    if (tryAgain == 'n' || tryAgain == 'N')
    {
      startPaint(1);
      cerr << "No alternate file provided. Cannot continue, closing program.\n";
      endPaint();
      exit(1);
    }

    //Otherwise, get a new file
    cout << "Filename: ";
    cin >> filename;
    file.open(filename);
  }
  file.close(); //temporary ////////////////////////////////////////////////////
}


//Make sure that what the calle is looking at is a real plugin
  //does not check if the plugin works, in any fashion
bool verifyPlugin(fs::file_status entry)
{
  //Just a stack of if statements that need to be true
  if(fs::is_directory(entry)) //Makes sure it's actually a folder
    return true;
  return false;
}


//Get a list of all the availible plugins
vector<string> readPlugins()
{
  //Build a vector<string> of all availible plugins
  vector<string> plugins;
  for (auto& entry : fs::directory_iterator("Plugins/"))
  {
    //Verifies that this is a conforming plugin
    if(verifyPlugin(entry.symlink_status()))
    {
      //Gets the string from the directory_entries, removing "Plugins/"
      string sliceString = entry.path();
      plugins.push_back(sliceString.substr(8)); // 8 = len("Plugins/")
    }
  }

  //Return the result back!
  return plugins;
}


//The help commands=
void help()
{
  string helpScript =
  "-enable <pluginName>  - enables the plugin with specified name\n"
  "-disable <pluginName> - disables the plugin with specified name\n"
  "list \t- lists all plugins\n"
  "-listD\t- lists disabled plugins\n"
  "-listE\t- lists enabled plugins\n"
  "-compile\t- compiles the program\n"
  "-save \t- saves the list of enabled plugins\n"
  "exit \t- exits the program, discarding unsaved changes\n"
  "help \t- lists this menu\n"
  "\n"
  "";

  cout << helpScript;
}

int main()
{
  //Initialize the list of plugins
  vector<string> plugins = readPlugins();

  //Change these two to be sets?
  //Initialize list of plugins that have already been enabled
  vector<string> enabledPlugins;// = readFile(Plugins/enabledPlugins.txt);
  //Initialize list of plugins that have yet to be enabled,
    //the difference of the last two lists
  vector<string> disabledPlugins;// = readFile(Plugins/enabledPlugins.txt);


  //User prompt
  startPaint(3);
  cout << "This is the program that will allow you to choose what plugins to"
          " use, and can compile the program for you.\nFor help, type 'help'\n";
  endPaint();

  //A simple command prompt to interact with the compiler
  string command = "";

  //Write out prompt, in green
  startPaint(2);
  cout << "command: ";
  endPaint();

  //Command prompt, options detailed in the help fuction
  while(cin >> command && command != "exit")
  {
    if (command == "enable")
      cin >> command;

    else if (command == "disable")
      cin >> command;

    else if (command == "list")
      for(string& pluginName : plugins)
        cout << pluginName << endl;

    else if (command == "listD")
      for(string& pluginName : disabledPlugins)
        cout << pluginName << endl;

    else if (command == "listE")
      for(string& pluginName : enabledPlugins)
        cout << pluginName << endl;

    else if (command == "compile") {}

    else if (command == "save") {}

    else if(command == "exit")
    break;

    else if(command == "help")
      help();

    else
      cerr << "Unknown command.\n";

    //Write out prompt, in green
    startPaint(2);
    cout << "command: ";
    endPaint();

    //Clear any extra characters in the cin stream
    cin.ignore(1000,'\n');
    cin.clear();
  }
}
