int entSize = 2;

if ( (entity.getX() < rightBound + entSize) && (entity.getX() > leftBound - entSize) )
    if ( (entity.getY() < bottomBound + entSize) && (entity.getY() > topBound - entSize) )
    {
        sf::CircleShape circularEnt(entSize, 30); //Each ent will be a circle of radius x
        circularEnt.setOrigin(entSize, entSize);
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
