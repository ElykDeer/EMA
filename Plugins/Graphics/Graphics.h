#include <sstream>

class Graphics : public GraphicsInternals
{
public:
  using GraphicsInternals::GraphicsInternals;

  Graphics(Bin* const bin, ThreadManager* const manager) : GraphicsInternals(bin, manager)
  {
    font.loadFromFile("Plugins/Graphics/Fonts/2.ttf");
    warningText.setString("Warning, unsaved progress will be lost.\nPress Enter to continue or Escape to go back.");
    warningText.setFont(font);
  }

  //Required event loop function
  void eventLoop();

  //Menus
  void pauseMenu();
  void game();
  void load();
  void save();
  void quit();
  void options();
  void about();
  void credits();

  //Helper for sub-pause menus
  void subMenuDefaultActions();
  void backButton();

  void textualGraphics() const;

private:
  int menu = 0;
  sf::Font font;

  sf::Text warningText;
};


/*

Optimize visual object creation
menus

*/
