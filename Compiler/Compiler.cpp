//This is the program that is supposed to pull together the resources of the
  //various pluggins and compile them before runtime

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

//Auto-completion:
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

//c++17
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

//Command Prompt Colors
#include "colorPrompt.h"

void enable(const vector<string>& plugins, unordered_set<string>& enabledPlugins, unordered_set<string>& disabledPlugins, const vector<string>& command)
{
  //Check if plugin exists
  bool pluginExists = false;
  for (string pluginName : plugins)
    if (pluginName == command[1])
    {
      pluginExists = true;
      enabledPlugins.insert(command[1]);
      disabledPlugins.erase(command[1]);
      break;
    }
  if (!pluginExists)
    cerr << "The plugin '" << command[1] << "' is not availible.\n";
}


void disable(const vector<string>& plugins, unordered_set<string>& enabledPlugins, unordered_set<string>& disabledPlugins, const vector<string>& command)
{
  //Check if plugin exists
  bool pluginExists = false;
  for (string pluginName : plugins)
    if (pluginName == command[1])
    {
      pluginExists = true;
      disabledPlugins.insert(command[1]);
      enabledPlugins.erase(command[1]);
      break;
    }
  if (!pluginExists)
    cerr << "The plugin '" << command[1] << "' is not availible.\n";
}


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
    ofstream file("Compiler/enabledPlugins.conf");
    if (!file)
    {
        startPaint(1);
        cerr << "Could not create file.\n";
        endPaint();
        return;
    }

    for (const string& pluginName : enabledPlugins)
        file << pluginName << endl;

    file.close();
}


//Make sure that what the calle is looking at is a real plugin
  //does not check if the plugin works, in any fashion
bool verifyPlugin(const fs::directory_entry& entry)
{
  //Just a stack of if statements that need to be true
  if(fs::is_directory(entry.symlink_status())) //Makes sure it's actually a folder
    if((string(entry.path()).substr(8) != "Environment"))  //Ignores the enviornment
      if((string(entry.path()).substr(8) != "Graphics"))  //Ignores the enviornment
        return true;
  return false;
}


//Get a list of all the availible plugins
vector<string> readPlugins()
{
  //Build a vector<string> of all availible plugins
  vector<string> plugins;
  for (const fs::directory_entry& entry : fs::directory_iterator("Plugins/"))
  {
    //Verifies that this is a conforming plugin
    if(verifyPlugin(entry))
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
  "compile\t- compiles the program\n"
  "save \t- saves the list of enabled plugins\n"
  "exit \t- exits the program, discarding unsaved changes\n"
  "help \t- lists this menu\n"
  "\n"
  "";

  cout << helpScript;
}


string getDependencies(const string& pluginName)
{
    //open the file
    string filename = pluginName + "/depend.txt";
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
        return "";
      }

      //Otherwise, get a new file
      cout << "Filename: ";
      cin >> filename;
      file.open(filename);
    }

    //Get all dependiencies and make a string of them
    string dependency;  //Each one
    string dependencies;  //All of them
    while(file >> dependency)
        dependencies += pluginName + '/' + dependency + ' ';

    return dependencies;
}

bool buildPluginTypes(const unordered_set<string>& plugins)
{
  //Open the types file
  ofstream typesFile("Compiler/pluginTypes.h");
  if (!typesFile)
  {
      startPaint(1);
      cerr << "Could not create file.\n";
      endPaint();
      return false;
  }

  //Beginning and end of the file
  string begin =
  "#ifndef SIM_PLUGIN_TYPES\n"
  "#define SIM_PLUGIN_TYPES 1\n\n";

  string end =
  "\n#endif\n";

  //Write header to file
  typesFile << begin;
  //Write Includes
  for (const string& pluginName : plugins)
      typesFile << "#include " << "\"../Plugins/" << pluginName << '/' << pluginName << "Types.h" << '"' << endl;

  typesFile << end;  //Write end portion
  typesFile.close();  //Close File

  return true;
}

bool buildEntityDrawCode(const unordered_set<string>& plugins)
{
  //Open the types file
  ofstream graphicsFile("Compiler/EntityDrawCode.cpp");
  if (!graphicsFile)
  {
      startPaint(1);
      cerr << "Could not create file.\n";
      endPaint();
      return false;
  }

  //Beginning of each link in the if-chain:
  string ifLinkP1 =
  "if (typeid(*&entity).hash_code() == typeid("; //<PluginName>

  //Middle:
  string ifLinkP2 =
  ").hash_code())\n"
  "{\n"
  "  #include \"../Plugins/";

  string ifLinkP3 = "/Graphics/"; //<PluginName>

  //End of each link:
  string ifLinkP4 =
  ".cpp\"\n"
  "}\n"
  "else ";

  //Write Includes
  for (const string& pluginName : plugins)
  {
    try  //Trying going into it's graphics folder.. If it's not there, whatever
    {
      //Build a vector<string> of all availible plugins
      for (const fs::directory_entry& entry : fs::directory_iterator("Plugins/" + pluginName + "/Graphics/"))
      {
        //Gets the string from the directory_entries, removing "Plugins/"
        string sliceString = entry.path();
        string className = sliceString.substr(18+pluginName.size(), sliceString.size() - (18+pluginName.size()+4)); // 18 = len("Plugins/" + "/Graphics/")
        graphicsFile << ifLinkP1 << className << ifLinkP2 << pluginName << ifLinkP3 << className << ifLinkP4;
      }
    }
    catch(...)
    {
      continue;
    }
  }

  //Write default case:
    //erase extra character
  graphicsFile << "\n{\n  #include \"../Plugins/Graphics/EntityDefaultDrawCode.cpp\"\n}\n";

  graphicsFile.close();  //Close File

  return true;
}


bool buildInit(const unordered_set<string>& plugins)
{
  //Open the types file
  ofstream initFile("Compiler/init.cpp");
  if (!initFile)
  {
      startPaint(1);
      cerr << "Could not create file.\n";
      endPaint();
      return false;
  }

  //File header:
  initFile << "void init(Bin& bin)\n{\n";

  //Beginning of each include:
  string linkP1 =
  "  {\n"
  "    #include \"../Plugins/"; //<PluginName>

  //End of each link:
  string linkP2 =
  ".cpp\"\n"
  "  }\n";

  //Write Includes
  for (const string& pluginName : plugins)
  {
    initFile << linkP1 << pluginName << "/" << pluginName << linkP2;
  }

  //File ender
  initFile << "}\n";

  initFile.close();  //Close File

  return true;
}


void compile(const unordered_set<string>& plugins)
{
    //Build dependencies:
    if (!buildPluginTypes(plugins))
      return;
    if (!buildEntityDrawCode(plugins))
      return;
    if (!buildInit(plugins))
      return;

    //Create the make command
    string dependencies = getDependencies("Main");;  //List of the main dependencies
    for (const string& dep : plugins)
        dependencies += getDependencies("Plugins/" + dep);


    #if defined(LINUX_X_LINUX)
    string compiler = "g++ ";
    string gccOptions = "-DLINUX_X_LINUX -Wall -Wextra -pedantic -std=c++1y ";
    string programName = "-o mainP ";
    string links = "-pthread -lsfml-graphics -lsfml-window -lsfml-system ";  //Linker dependencies

    #elif defined(MAC_X_MAC)
    string compiler = "/usr/local/bin/g++-7 ";
    string gccOptions = "-DMAC_X_MAC -Wall -Wextra -pedantic -std=c++1y ";
    string programName = "-o mainP ";
    string links = "-pthread -lsfml-graphics -lsfml-window -lsfml-system ";  //Linker dependencies

    #elif defined(LINUX_X_WINDOWS)
    string compiler = "x86_64-w64-mingw32-g++ ";
    string gccOptions = "-static -DLINUX_X_WINDOWS -DSFML_STATIC -Wall -Wextra -pedantic -std=c++1y ";
    string programName = "-o mainP.exe ";
    string links = "-pthread -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -ljpeg -lwinmm -lgdi32 ";  //Linker dependencies

    #else
    cerr << "No compilation target specified.\n";
    exit();

    #endif

    string command =
    compiler + gccOptions + dependencies + programName + links;

    startPaint(1);
    cout << "Command: " << command;
    endPaint();
    cout << endl;

    //The rest of this is modified from "stackoverflow.com/questions/478898"
    array<char, 128> buffer;
    shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) //If it fails
    {
        cerr << "\nCould not run command.  Command is: \n" << command << endl;
        return;
    }
    while (!feof(pipe.get()))
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            cout << buffer.data();
}


vector<string> vectorize(const string& commandString)
{
    if (commandString.length() == 0)
        return {""};
    istringstream commandStream(commandString);

    string word = "";
    vector<string> commandVector;
    while(commandStream >> word)
      commandVector.push_back(word);

    return commandVector;
}


//auto-completion
static char** my_completion(const char*, int, int);
char* my_generator(const char*,int);
std::vector<std::string> cmd = { "enable", "disable", "clear", "list", "listD" ,"listE", "compile", "save", "exit", "help" };


int main(int argc, char* argv[])
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

  if (argc == 2)
    if (*argv[1] == 'c')
    {
      compile(enabledPlugins);
      return 1;
    }

  //User prompt
  startPaint(3);
  cout << "This is the program that will allow you to choose what plugins to"
          " use, and can compile the program for you.\nFor help, type 'help'\n";
  endPaint();

  //A simple command prompt to interact with the compiler
  string rawCommand = "";
  vector<string> command;
  //Auto-completion:
  rl_attempted_completion_function = my_completion;

  //Need readline so that it can parse tabs, should only equal null on error
  //Command prompt, options detailed in the help fuction
  //prints in green
  while((rawCommand = readline(commandPrompt.c_str())).c_str() != NULL )
  {
    //enable auto-complete
    rl_bind_key('\t', rl_complete);

    //Make every word of the command into a different item in a vector
    command = vectorize(rawCommand);

    if (command[0] == "enable")
    {
        enable(plugins, enabledPlugins, disabledPlugins, command);
    }

    else if (command[0] == "disable")
    {
        disable(plugins, enabledPlugins, disabledPlugins, command);
    }

    else if (command[0] == "list")
    {
      for(string& pluginName : plugins)
        cout << pluginName << endl;
    }

    else if (command[0] == "listD")
    {
      for(string pluginName : disabledPlugins)
        cout << pluginName << endl;
    }

    else if (command[0] == "listE")
    {
      for(string pluginName : enabledPlugins)
        cout << pluginName << endl;
    }

    else if (command[0] == "clear")
    {
      enabledPlugins.clear();

      for (const string& pluginName : plugins)
        disabledPlugins.insert(pluginName);
    }

    else if (command[0] == "compile")
    {
        compile(enabledPlugins);
    }

    else if (command[0] == "save")
    {
        save(enabledPlugins);
    }

    else if(command[0] == "exit")
    {
        break;
    }

    else if(command[0] == "help")
    {
        help();
    }

    else if (command[0] == "")
    {
        startPaint(1);
        cerr << "No entered command.\n";
        endPaint();
    }

    else
    {
        startPaint(1);
        cerr << "Unknown command.\n";
        endPaint();
    }

    if (rawCommand != "")
        add_history(rawCommand.c_str());
  }
}


//Does completions
static char** my_completion( const char * text , int start, int end)
{
    char **matches;

    matches = (char **)NULL;

    if (start == 0)
        matches = rl_completion_matches ((char*)text, &my_generator);
    else
        rl_bind_key('\t',rl_abort);

    return (matches);

    end += 1; //////////////////////////////////////////////////////////////////
}


//Gets matches
char* my_generator(const char* text, int state)
{
  static std::size_t list_index, len;
  std::string name;

  if (!state) {
      list_index = 0;
      len = strlen (text);
  }

  while (list_index < cmd.size()) {
      name = cmd[list_index];
      list_index++;

      if (strncmp (const_cast<char*>(name.c_str()), text, len) == 0)
      {
          char* copy = static_cast<char*>(malloc(name.length() + 1));
          strcpy(copy, const_cast<char*>(name.c_str()));
          return copy;
      }
  }

    /* If no names matched, then return NULL. */
    return (char *)NULL;
}
