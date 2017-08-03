// "close requested" event: we close the window
if (event.type == sf::Event::Closed)
{
  manager->kill();
  window.close();
}

// catch the resize events
if (event.type == sf::Event::Resized)
{
  //scale view to new window size
  sf::View view = sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height));
  //set center to old center
  view.setCenter(window.getView().getCenter());
  //propogate
  window.setView(view);
}

//zoom
if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
{
  // create a view half the size of the default view
  sf::View view = window.getView();

  //1.25 = 1/0.8 -- Zooming in then out will show the same thing after
  if (event.mouseWheelScroll.delta <= -1)
    view.zoom(1.25);
  else if (event.mouseWheelScroll.delta >= 1)
    view.zoom(0.8);
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
