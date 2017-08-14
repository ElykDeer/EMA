#include <string>
#include <iostream>
#include <sstream>

class Graphics : public GraphicsInternals
{
public:
  using GraphicsInternals::GraphicsInternals;
  Graphics(Bin* const bin, ThreadManager* const manager) : GraphicsInternals(bin, manager)
  {
    font.loadFromFile("/usr/share/fonts/truetype/takao-gothic/TakaoPGothic.ttf");
  }

  //Required event loop function
  void eventLoop();

  //Menus
  void pauseMenu();
  void game();

  void textualGraphics() const;

private:
  int menu = 0;
  sf::Font font;
};


/*

Optimize visual object creation
menus

*/
