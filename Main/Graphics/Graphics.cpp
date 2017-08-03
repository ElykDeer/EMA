#include "../Graphics.h"
using namespace std;

GraphicsInternals::GraphicsInternals(Bin* const bin, ThreadManager* const manager)
  : bin(bin), manager(manager) {}

GraphicsInternals::~GraphicsInternals() {}

void GraphicsInternals::openWindow(const string& name)
{
  window.create(sf::VideoMode(bin->getWidth(), bin->getHeight()), name, sf::Style::Default);
}

void GraphicsInternals::drawMap()
{
  sf::CircleShape hexa((*bin->getAllHexes()).getRadius(), 6); //Each hex will be a circle with 6 sides
  hexa.rotate(30);
  hexa.setOutlineThickness(0.8);
  hexa.setOutlineColor(sf::Color::Blue);
  hexa.setFillColor(sf::Color::White);
  hexa.setOrigin((*bin->getAllHexes()).getRadius(), (*bin->getAllHexes()).getRadius());
  for (const Bin::Hex& hex : bin->getAllHexes())
  {
    hexa.setPosition(hex.getX(), hex.getY());
    window.draw(hexa);
  }
}

void GraphicsInternals::drawEntities()
{
  //Every ent will be a red ring with a red dot at it's center
  if (bin->count())
    for (const Entity& entity : bin->getAll())
    {
      #include "../../Compiler/EntityDrawCode.cpp"
    }
}

void GraphicsInternals::manageEvents()
{
  //check window events
  sf::Event event;
  while (window.pollEvent(event))
  {
    #include "Events.cpp"
  }
}

void GraphicsInternals::input()
{
  #include "Input.cpp"
}

#include "../../Plugins/Graphics/Graphics.cpp"
