//This is the program that is supposed to pull together the resources of the
  //various pluggins and compile them before runtime

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <unordered_set>
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


unordered_set<string> load()
{
    //open the file
    string filename = "Compiler/enabledPlugins.conf";
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
        return unordered_set<string>();
      }

      //Otherwise, get a new file
      cout << "Filename: ";
      cin >> filename;
      file.open(filename);
    }

    //Raed into set and return
    string pluginName;
    unordered_set<string> enabledPlugins;
    while(file >> pluginName)
        enabledPlugins.insert(pluginName);

    file.close();

    return enabledPlugins;
}


void save(const unordered_set<string>& enabledPlugins)
{
    //Open the save file
    string filename = "Compiler/enabledPlugins.conf";
    ofstream file(filename);
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

    for (const string& pluginName : enabledPlugins)
        file << pluginName << endl;

    file.close();
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
  "enable <pluginName>  - enables the plugin with specified name\n"
  "disable <pluginName> - disables the plugin with specified name\n"
  "clear\t- disables all plugins\n"
  "list \t- lists all plugins\n"
  "listD\t- lists disabled plugins\n"
  "listE\t- lists enabled plugins\n"
  "-compile\t- compiles the program\n"
  "-save \t- saves the list of enabled plugins\n"
  "exit \t- exits the program, discarding unsaved changes\n"
  "help \t- lists this menu\n"
  "\n"
  "";

  cout << helpScript;
}


void compile(const unordered_set<string>& plugins)
{
    //Open the save file
    string filename = "Compiler/pluginTypes.h";
    ofstream file(filename);
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

    //Beginning and end of the file
    string begin =
    "#ifndef SIM_PLUGIN_TYPES\n"
    "#define SIM_PLUGIN_TYPES 1\n\n";

    string end =
    "\n#endif\n";

    //Write header to file
    file << begin;

    //Write Includes
    for (const string& pluginName : plugins)
        file << "#include " << '"' << pluginName << "Types.h" << '"' << endl;

    //Write endif
    file << end;

    //Close File
    file.close();
}


int main()
{
  //Initialize the list of plugins
  vector<string> plugins = readPlugins();

  //Initialize list of plugins that have already been enabled
  unordered_set<string> enabledPlugins = load();

  //Initialize list of plugins that have yet to be enabled,
    //the difference of the last two lists
  unordered_set<string> disabledPlugins;// = readFile(Plugins/enabledPlugins.txt);
  for (string pluginName : plugins)
    if(enabledPlugins.count(pluginName) == 0)
      disabledPlugins.insert(pluginName);

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
    {
        //Get name of plugin
        cin >> command;

        //Check if plugin exists
        bool pluginExists = false;
        for (string pluginName : plugins)
          if (pluginName == command)
          {
            pluginExists = true;
            enabledPlugins.insert(command);
            disabledPlugins.erase(command);
            break;
          }
        if (!pluginExists)
          cerr << "The plugin '" << command << "' is not availible.\n";
    }

    else if (command == "disable")
    {
        //Get name of plugin
        cin >> command;

        //Check if plugin exists
        bool pluginExists = false;
        for (string pluginName : plugins)
          if (pluginName == command)
          {
            pluginExists = true;
            disabledPlugins.insert(command);
            enabledPlugins.erase(command);
            break;
          }
        if (!pluginExists)
          cerr << "The plugin '" << command << "' is not availible.\n";
    }

    else if (command == "list")
    {
      for(string& pluginName : plugins)
        cout << pluginName << endl;
    }

    else if (command == "listD")
    {
      for(string pluginName : disabledPlugins)
        cout << pluginName << endl;
    }

    else if (command == "listE")
    {
      for(string pluginName : enabledPlugins)
        cout << pluginName << endl;
    }

    else if (command == "clear")
    {
      enabledPlugins.clear();

      for (const string& pluginName : plugins)
        disabledPlugins.insert(pluginName);
    }

    else if (command == "compile")
    {
        compile(enabledPlugins);
    }

    else if (command == "save")
    {
        save(enabledPlugins);
    }

    else if(command == "exit")
    {
        break;
    }

    else if(command == "help")
    {
        help();
    }

    else
    {
        cerr << "Unknown command.\n";
    }

    //Write out prompt, in green
    startPaint(2);
    cout << "command: ";
    endPaint();

    //Clear any extra characters in the cin stream
    cin.ignore(1000,'\n');
    cin.clear();
  }
}
