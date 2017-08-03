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
      #include "../Compiler/EntityDrawCode.cpp"
    }
}

void GraphicsInternals::manageEvents()
{
  //drag/drop
  sf::Vector2f oldPos;
  bool moving = false;
  sf::View view = window.getDefaultView();

  //check window events
  sf::Event event;
  while (window.pollEvent(event))
  {
    // "close requested" event: we close the window
    if (event.type == sf::Event::Closed)
    {
      manager->kill();
      window.close();
    }

    // catch the resize events
    if (event.type == sf::Event::Resized)
    {
      // update the view to the new size of the window
      sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
      window.setView(sf::View(visibleArea));
    }

    //zoom
    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
      // create a view half the size of the default view
      sf::View view = window.getView();
      if (event.mouseWheelScroll.delta <= -1)
        view.zoom(1.1);
      else if (event.mouseWheelScroll.delta >= 1)
        view.zoom(0.9);
      window.setView(view);
    }

    //Speed control
    if (event.type == sf::Event::KeyPressed)
    {
        if ((event.key.code == sf::Keyboard::Add) || ( (event.key.code == sf::Keyboard::Equal) && (event.key.shift) ))
        {
          manager->setSpeed(manager->getSpeed()*2);
        }
        if ((event.key.code == sf::Keyboard::Subtract) || (event.key.code == sf::Keyboard::Dash))
        {
          manager->setSpeed(manager->getSpeed()/2);
        }
    }

    //drag/drop
    if (event.type == sf::Event::MouseButtonPressed) // Mouse button is pressed, get the position and set moving as active
        if (event.mouseButton.button == 0)
        {
            moving = true;
            oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        }
    if (event.type == sf::Event::MouseButtonReleased)
        if (event.mouseButton.button == 0) // Mouse button is released, no longer move
            moving = false;
    if (event.type == sf::Event::MouseMoved)
    {
        if (!moving)
            continue;
        // Determine the new position in world coordinates
        const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        // Determine how the cursor has moved
        // Swap these to invert the movement direction
        const sf::Vector2f deltaPos = oldPos - newPos;

        // Move our view accordingly and update the window
        view.setCenter(view.getCenter() + deltaPos);
        window.setView(view);

        // Save the new position as the old one
        // We're recalculating this, since we've changed the view
        oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
    }
    // if (event.type == sf::Event::MouseMoved)
    //     if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //     {
    //         const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
    //         const sf::Vector2f deltaPos = oldPos - newPos;
    //         view.setCenter(view.getCenter() + deltaPos);
    //         window.setView(view);
    //         oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
    //     }
  }
}

void GraphicsInternals::input()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    sf::View view = window.getView();
    view.move(-moveSensitivity, 0);
    window.setView(view);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    sf::View view = window.getView();
    view.move(moveSensitivity, 0);
    window.setView(view);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    sf::View view = window.getView();
    view.move(0, -moveSensitivity);
    window.setView(view);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    sf::View view = window.getView();
    view.move(0, moveSensitivity);
    window.setView(view);
  }
}

#include "../Plugins/Graphics/Graphics.cpp"
