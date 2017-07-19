#include "Graphics.h"
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
  for (const Bin::Hex& hex : bin->getAllHexes())
  {
    hexa.setOutlineColor(sf::Color::White);
    hexa.setFillColor(sf::Color::Black);
    hexa.setOutlineThickness(0.8);
    hexa.setPosition(hex.getX(), hex.getY());
    window.draw(hexa);
  }
}

void GraphicsInternals::drawEntities()
{
  sf::CircleShape circularEnt(2, 30); //Each ent will be a circle of radius 5
  for (const Entity& entity : bin->getAll())
  {
    circularEnt.setFillColor(sf::Color::Red);
    circularEnt.setPosition(entity.getX(), entity.getY());
    window.draw(circularEnt);
  }
}

{

}

#include "../Plugins/Graphics/Graphics.cpp"
