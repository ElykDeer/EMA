#include "Graphics.h"
using namespace std;

GraphicsInternals::GraphicsInternals(Bin* const bin, ThreadManager* const manager)
  : bin(bin), manager(manager) {}

GraphicsInternals::~GraphicsInternals()
{
  if (window)
    delete window;
}

void GraphicsInternals::openWindow(const string& name)
{
  //1000x1000 window, by default
  window = new sf::RenderWindow(sf::VideoMode(1000, 1000), name, sf::Style::Default);
  auto view = window->getView();
  view.setCenter(bin->getWidth()/2, bin->getHeight()/2);
  window->setView(view);
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

  auto center = window->getView().getCenter();
  auto xSize = window->getView().getSize().x/2;
  auto ySize = window->getView().getSize().y/2;
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
            window->draw(hexa);
        }

  }
}

void GraphicsInternals::drawEntities()
{
    auto center = window->getView().getCenter();
    auto xSize = window->getView().getSize().x/2;
    auto ySize = window->getView().getSize().y/2;
    auto leftBound = center.x - xSize;
    auto rightBound = center.x + xSize;
    auto topBound = center.y - ySize;
    auto bottomBound = center.y + ySize;

    //Every ent will be a red ring with a red dot at it's center
    if (bin->count())
        for (const Entity& entity : bin->getAll())
        {
          #include "../Compiler/EntityDrawCode.cpp"
        }
}

//Window resizing, closing
void GraphicsInternals::basicEvents(sf::Event& event)
{
  #include "../Plugins/Graphics/events.cpp"
}

//Map movement, speed control
void GraphicsInternals::controlledEvents(sf::Event& event)
{
  #include "../Plugins/Graphics/controlledEvents.cpp"
}

void GraphicsInternals::manageEvents()
{
  //check window events
  sf::Event event;
  while (window->pollEvent(event))
  {
    //Get window events
    basicEvents(event);
    //get controls
    controlledEvents(event);
  }
}

//Keyboard, mouse, etc
void GraphicsInternals::input()
{
    #include "../Plugins/Graphics/input.cpp"
}

void GraphicsInternals::pauseOverlay()
{
    if (manager->getPauseState())
    {
      auto oldView = window->getView();

      window->setView(window->getDefaultView());

      // get the screen bounds
      sf::Vector2i bottomRightPos(window->getSize().x, window->getSize().y);
      // convert it to world coordinates
      sf::Vector2f bottomRight = window->mapPixelToCoords(bottomRightPos);
      sf::Vector2f topLeft = window->mapPixelToCoords(sf::Vector2i(0, 0));

      int windowSize;
      if (bottomRight.x - topLeft.x > bottomRight.y - topLeft.y)
          windowSize = bottomRight.x - topLeft.x;
      else
          windowSize = bottomRight.y - topLeft.y;

      //define the shape and adjust its properties
      sf::CircleShape pauseGraying(windowSize, 4);
      pauseGraying.rotate(45);
      pauseGraying.setOrigin(windowSize, windowSize);
      pauseGraying.setFillColor(sf::Color(0, 0, 0, 200));

      //draw it in the middle of the screen
      pauseGraying.setPosition(bottomRight.x/2, bottomRight.y/2);

      //Draw it
      window->draw(pauseGraying);

      //get the old view back
      window->setView(oldView);
    }
}

#include "../Plugins/Graphics/Graphics.cpp"
