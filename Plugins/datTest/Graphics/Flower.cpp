const Flower* ent = static_cast<const Flower*>(&entity);

sf::CircleShape circularEnt(ent->getSize(), 15);
circularEnt.setOrigin(ent->getSize(), ent->getSize());
circularEnt.setOutlineThickness(0.8);
circularEnt.setOutlineColor(sf::Color::Magenta);
circularEnt.setFillColor(sf::Color(255, 165, 0)); //Orange

sf::CircleShape entCenter(0.2, 15);
entCenter.setOrigin(0.2, 0.2);
entCenter.setFillColor(sf::Color::Green);

//Draw circle for petals
circularEnt.setPosition(ent->getX(), ent->getY());
window.draw(circularEnt);

//Draw point for center thing
entCenter.setPosition(ent->getX(), ent->getY());
window.draw(entCenter);
