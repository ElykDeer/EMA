#ifndef SIM_GRAPHICAL_API
#define SIM_GRAPHICAL_API 1
#define SFML_STATIC

#include "dataStructure.h"
#include "ThreadManager.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class GraphicsInternals
{
public:
  GraphicsInternals(const Bin* const bin, const ThreadManager* const manager);
  virtual ~GraphicsInternals();

  virtual void openWindow(const std::string& name);

  virtual void spin() = 0; //Perhaps remove this later...

  virtual void drawMap() const;
  virtual void drawEntities() const;

protected:
  const Bin* const bin;
  const ThreadManager* const manager;

  sf::Window window;

};

#include "../Plugins/Graphics/Graphics.h"

#endif
