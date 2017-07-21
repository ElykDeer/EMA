sf::CircleShape circularEnt(2, 30);
circularEnt.setOrigin(2, 2);
circularEnt.setOutlineThickness(0.8);
circularEnt.setOutlineColor(sf::Color(139, 69, 19));
circularEnt.setFillColor(sf::Color::Transparent);

sf::CircleShape entCenter(0.2, 30);
entCenter.setOrigin(0.2, 0.2);
entCenter.setFillColor(sf::Color::Black);

//Draw circle for Face
circularEnt.setPosition(entity.getX(), entity.getY());
window.draw(circularEnt);

//Draw point for nose
entCenter.setPosition(entity.getX(), entity.getY());
window.draw(entCenter);
