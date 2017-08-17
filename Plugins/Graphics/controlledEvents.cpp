//More complex controls for once-click events, not realtime controls

//zoom
if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
{
  // create a view half the size of the default view
  sf::View view = window->getView();

  //1.25 = 1/0.8 -- Zooming in then out will show the same thing after
  if (event.mouseWheelScroll.delta <= -1)
    view.zoom(1.25);
  else if (event.mouseWheelScroll.delta >= 1)
    view.zoom(0.8);
  window->setView(view);
}

//Speed control
if (event.type == sf::Event::KeyPressed)
{
    if ((event.key.code == sf::Keyboard::Add) || ( (event.key.code == sf::Keyboard::Equal) && (event.key.shift) ))
    {
      manager->setSpeed(manager->getSpeed()*2);
    }
    else if ((event.key.code == sf::Keyboard::Subtract) || (event.key.code == sf::Keyboard::Dash))
    {
      manager->setSpeed(manager->getSpeed()/2);
    }
}

//Drag/drop
if (event.type == sf::Event::MouseButtonPressed) // Mouse button is pressed, get the position and set moving as active
    if (event.mouseButton.button == 0)
    {
        moving = true;
        oldPos = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
    }
if (event.type == sf::Event::MouseButtonReleased)
    if (event.mouseButton.button == 0) // Mouse button is released, no longer move
        moving = false;
if (event.type == sf::Event::MouseMoved)
{
    if (!moving)
        return;
    // Determine the new position in world coordinates
    const sf::Vector2f newPos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
    // Determine how the cursor has moved
    // Swap these to invert the movement direction
    const sf::Vector2f deltaPos = oldPos - newPos;

    // Move our view accordingly and update the window
    sf::View view = window->getView();
    view.move(deltaPos);
    window->setView(view);

    // Save the new position as the old one
    // We're recalculating this, since we've changed the view
    oldPos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
}
