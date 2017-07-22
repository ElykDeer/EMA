sf::CircleShape circularEnt(2, 30);
circularEnt.setOrigin(2, 2);
circularEnt.setOutlineThickness(0.8);
circularEnt.setOutlineColor(sf::Color::Magenta);
circularEnt.setFillColor(sf::Color::Transparent);

sf::CircleShape entCenter(0.2, 30);
entCenter.setOrigin(0.2, 0.2);
entCenter.setFillColor(sf::Color::Green);

//Draw circle for petals
circularEnt.setPosition(entity.getX(), entity.getY());
window.draw(circularEnt);

//Draw point for center thing
entCenter.setPosition(entity.getX(), entity.getY());
window.draw(entCenter);
