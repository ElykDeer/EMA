const Flower* ent = static_cast<const Flower*>(&entity);

double kernalSize = 0.2;

double entSize = ent->getSize();
if (!entSize)
    entSize = kernalSize;


if ( (entity.getX() < rightBound + entSize) && (entity.getX() > leftBound - entSize) )
    if ( (entity.getY() < bottomBound + entSize) && (entity.getY() > topBound - entSize) )
    {
        sf::CircleShape circularEnt(ent->getSize(), 15);
        circularEnt.setOrigin(ent->getSize(), ent->getSize());
        circularEnt.setOutlineThickness(0.8);
        circularEnt.setOutlineColor(sf::Color::Magenta);
        circularEnt.setFillColor(sf::Color(255, 165, 0)); //Orange

        sf::CircleShape entCenter(kernalSize, 15);
        entCenter.setOrigin(kernalSize, kernalSize);
        entCenter.setFillColor(sf::Color::Green);

        //Draw circle for petals
        circularEnt.setPosition(ent->getX(), ent->getY());
        window->draw(circularEnt);

        //Draw point for center thing
        entCenter.setPosition(ent->getX(), ent->getY());
        window->draw(entCenter);
    }
