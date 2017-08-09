#include <string>
#include <iostream>
#include <sstream>

class Graphics : public GraphicsInternals
{
public:
  using GraphicsInternals::GraphicsInternals;

  //Required event loop function
  void eventLoop();

  //Menus
  void pauseMenu();
  void game();

  void textualGraphics() const;

private:
  int menu = 0;
};


/*

Optimize visual object creation
menus

*/
