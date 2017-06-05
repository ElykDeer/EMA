//This is the program that is supposed to pull together the resources of the
  //various pluggins and compile them before runtime

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;

//c++17
#include <filesystem>
namespace fs = std::filesystem;

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
}


int main()
{
  for (auto& p : fs::directory_iterator("Plugins/"))
    cout << p << endl;
}
