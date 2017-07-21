if (typeid(*&entity).hash_code() == typeid(Flower).hash_code())
{
  #include "../Plugins/datTest/Graphics/Flower.cpp"
}
else if (typeid(*&entity).hash_code() == typeid(Dog).hash_code())
{
  #include "../Plugins/datTest/Graphics/Dog.cpp"
}
else
{
  sf::CircleShape circularEnt(2, 30); //Each ent will be a circle of radius x
  circularEnt.setOrigin(2, 2);
  circularEnt.setOutlineThickness(0.8);
  circularEnt.setOutlineColor(sf::Color::Red);
  circularEnt.setFillColor(sf::Color::Transparent);

  sf::CircleShape entCenter(0.2, 30); //Each ent will be a circle of radius
  entCenter.setOrigin(0.2, 0.2);
  entCenter.setFillColor(sf::Color::Red);

  //Draw circle for entitiy
  circularEnt.setPosition(entity.getX(), entity.getY());
  window.draw(circularEnt);

  //Draw point for center
  entCenter.setPosition(entity.getX(), entity.getY());
  window.draw(entCenter);
}
