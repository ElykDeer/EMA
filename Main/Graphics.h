#ifndef SIM_GRAPHICAL_API
#define SIM_GRAPHICAL_API 1

#include "dataStructure.h"
#include "ThreadManager.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class GraphicsInternals
{
public:
  GraphicsInternals(Bin* const bin, ThreadManager* const manager);
  virtual ~GraphicsInternals();

  virtual void openWindow(const std::string& name);

  virtual void evnetLoop() = 0;

  virtual void drawMap();
  virtual void drawEntities();

  //These two should probably be built by the compiler based on some rules I'll think up later
  virtual void manageEvents();  //Window resizing, closing, scrolling
  virtual void input();  //Keyboard, mouse, etc

  void pauseOverlay();

protected:
  Bin* const bin;
  ThreadManager* const manager;

  sf::RenderWindow window;

private:
  int moveSensitivity = 2;
};

#include "../Plugins/Graphics/Graphics.h"

#endif
