#ifndef SIM_GRAPHICAL_API
#define SIM_GRAPHICAL_API 1

#include "dataStructure.h"
#include "ThreadManager.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory> //shared pointer

class GraphicsInternals
{
public:
  GraphicsInternals(Bin* const bin, ThreadManager* const manager);
  virtual ~GraphicsInternals();

  virtual void openWindow(const std::string& name);

  virtual void eventLoop() = 0;

  virtual void drawMap();
  virtual void drawEntities();

  //These two should probably be built by the compiler based on some rules I'll think up later
  virtual void basicEvents(sf::Event& event); //Window resizing, closing
  virtual void controlledEvents(sf::Event& event); //Map movement, speed control
  virtual void manageEvents();  //Loops top two
  virtual void input();  //Keyboard, mouse, etc

  void pauseOverlay();

protected:
  Bin* const bin;
  ThreadManager* const manager;

  std::shared_ptr<sf::RenderWindow> window;

private:
  //Arrow keys move
  int moveSensitivity = 2;

  //Drag/drop
  sf::Vector2f oldPos;
  bool moving = false;
};

#include "../Plugins/Graphics/Graphics.h"

#endif
