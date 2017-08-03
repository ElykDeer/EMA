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
