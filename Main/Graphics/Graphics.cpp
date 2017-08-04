#include "../Graphics.h"
using namespace std;

GraphicsInternals::GraphicsInternals(Bin* const bin, ThreadManager* const manager)
  : bin(bin), manager(manager) {}

GraphicsInternals::~GraphicsInternals() {}

void GraphicsInternals::openWindow(const string& name)
{
  //1000x1000 window, by default
  window.create(sf::VideoMode(1000, 1000), name, sf::Style::Default);
}

void GraphicsInternals::drawMap()
{
  auto hexRadius = (*bin->getAllHexes()).getRadius();
  sf::CircleShape hexa(hexRadius, 6); //Each hex will be a circle with 6 sides
  hexa.rotate(30);
  hexa.setOutlineThickness(0.8);
  hexa.setOutlineColor(sf::Color::Blue);
  hexa.setFillColor(sf::Color::White);
  hexa.setOrigin(hexRadius, hexRadius);

  auto center = window.getView().getCenter();
  auto xSize = window.getView().getSize().x/2;
  auto ySize = window.getView().getSize().y/2;
  auto leftBound = center.x - xSize - hexRadius;
  auto rightBound = center.x + xSize + hexRadius;
  auto topBound = center.y - ySize - hexRadius;
  auto bottomBound = center.y + ySize + hexRadius;

  for (const Bin::Hex& hex : bin->getAllHexes())
  {
    if ( (hex.getX() < rightBound) && (hex.getX() > leftBound) )
        if ( (hex.getY() < bottomBound) && (hex.getY() > topBound) )
        {
            hexa.setPosition(hex.getX(), hex.getY());
            window.draw(hexa);
        }

  }
}

void GraphicsInternals::drawEntities()
{
    auto center = window.getView().getCenter();
    auto xSize = window.getView().getSize().x/2;
    auto ySize = window.getView().getSize().y/2;
    auto leftBound = center.x - xSize;
    auto rightBound = center.x + xSize;
    auto topBound = center.y - ySize;
    auto bottomBound = center.y + ySize;

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
