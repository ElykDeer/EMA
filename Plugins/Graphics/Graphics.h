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
  int pauseMenu();
  int game();

  void textualGraphics() const;
};


/*

Optimize visual object creation
menus

*/
