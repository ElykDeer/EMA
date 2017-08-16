using namespace std;

void Graphics::eventLoop()
{
    manager->startDetachedThread(&Graphics::textualGraphics, this);

    GraphicsInternals::openWindow(string("Sim"));

    //Menu numbers"
      // 0 - Pause
      // 1 - Game
    while (window.isOpen())
    {
        if (menu == 0) //paused
        {
            pauseMenu();
        }
        else if (menu == 1) //running the game
        {
            game();
        }
    }
}

void  Graphics::pauseMenu()
{
    //check window events
    sf::Event event;
    while (window.pollEvent(event))
    {
        GraphicsInternals::basicEvents(event); //Get window events

        //Pause control
        if (event.type == sf::Event::KeyPressed)
        {
          if (event.key.code == sf::Keyboard::Space)
          {
            if(manager->getPauseState()) //paused
              manager->resume();
            else
              manager->pause();

            menu = 1; //switch to the game menu
            return;
          }
        }

        //add click for menu options
    }

    //still draw the hexes, but don't have the interactivity of the map
    window.clear();
    GraphicsInternals::drawMap();         //Hex grid
    GraphicsInternals::drawEntities();    //Entites
    GraphicsInternals::pauseOverlay();    //Graying screen

    /* <Menu-Graphics>  */
    auto center = window.getView().getCenter();
    double hexRadius;
    if (window.getView().getSize().x < window.getView().getSize().y)
        hexRadius = window.getView().getSize().x/8;
    else
        hexRadius = window.getView().getSize().y/8;


    //Background hex
    sf::CircleShape hexa(hexRadius*2.6, 6); //Each hex will be a circle with 6 sides
    hexa.setOrigin(hexRadius*2.6, hexRadius*2.6);
    hexa.setPosition(center.x, center.y);
    hexa.setFillColor(sf::Color::Green);
    window.draw(hexa);

    //Reset to normal attributes
    hexa.setRadius(hexRadius);
    hexa.setOrigin(hexRadius, hexRadius);
    hexa.rotate(30);
    hexa.setOutlineColor(sf::Color::Blue);
    hexa.setOutlineThickness(3);
    hexa.setFillColor(sf::Color::White);

    hexa.setPosition(center.x, center.y); window.draw(hexa); //Middle Hex
    hexa.setPosition(center.x, center.y+(2*hexRadius)); window.draw(hexa); //Bottom Hex
    hexa.setPosition(center.x, center.y-(2*hexRadius)); window.draw(hexa); //Top Hex
    hexa.setPosition(center.x+(1.75*hexRadius), center.y+(hexRadius)); window.draw(hexa); //Bottom Right Hex
    hexa.setPosition(center.x+(1.75*hexRadius), center.y-(hexRadius)); window.draw(hexa); //Top Right Hex
    hexa.setPosition(center.x-(1.75*hexRadius), center.y+(hexRadius)); window.draw(hexa); //Bottom Left Hex
    hexa.setPosition(center.x-(1.75*hexRadius), center.y-(hexRadius)); window.draw(hexa); //Top Left Hex

    sf::Text text("Controls", font, hexRadius/2.25);
    //Should be constant, otherwise affected by letters like 'p':
    auto textHeight = text.getLocalBounds().height;
    text.setFillColor(sf::Color::Blue);
    //Calculate what the text size needs to be

    text.setString("Resume");
    text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x, center.y);
    window.draw(text); //Resume - Middle Hex

    text.setString("Load");
    text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x, center.y-(2*hexRadius));
    window.draw(text); //Load - Top Hex

    text.setString("Save");
    text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x, center.y+(2*hexRadius));
    window.draw(text); //Save - Bottom Hex

    text.setString("Controls");
    text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x+(1.75*hexRadius), center.y-(hexRadius));
    window.draw(text); //Controls - Top Right Hex

    text.setString("Options");
    text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x+(1.75*hexRadius), center.y+(hexRadius));
    window.draw(text); //Options - Bottom Right Hex

    text.setString("About");
    text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x-(1.75*hexRadius), center.y-(hexRadius));
    window.draw(text); //About - Top Left Hex

    text.setString("Credits");
    text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x-(1.75*hexRadius), center.y+(hexRadius));
    window.draw(text); //Credits - Bottom Left Hex
    /* </Menu-Graphics> */


    window.display();
}

void Graphics::game()
{
    //check window events
    sf::Event event;
    while (window.pollEvent(event))
    {
      //Get window events
      GraphicsInternals::basicEvents(event);
      //get controls
      GraphicsInternals::controlledEvents(event);

      //Pause control
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Space)
        {
          if(manager->getPauseState()) //paused
            manager->resume();
          else
            manager->pause();

          menu = 0; //switch to the pause menu
          return;
        }
      }
    }
    //Keyboard, mouse, etc
    GraphicsInternals::input();

    //Actually Draw!
    window.clear();
    GraphicsInternals::drawMap();         //Hex grid
    GraphicsInternals::drawEntities();    //Entites
    window.display();
}

void Graphics::textualGraphics() const
{
    manager->sleep(1000000000); //Wait for window to open

    string spin = "|\\-/";
    while (window.isOpen())
    {
        for (int i = 0; i < 4; ++i)
        {
            //Build print statement
            ostringstream output;
            output << "Res: " << manager->getResolution();
            output << "; Speed: " << manager->getSpeed();
            output << "; Tick: " << manager->getTick();
            output << "; Day: " << float(manager->getTick())/(60.0*60.0*24.0);
            output << "; entCount: " << bin->count();
            output << " " << spin[i];
            output << "    ";

            //Print it
            cout << output.str();
            cout.flush();

            //Delay for the spinner
            manager->sleep(75000000);  //Spin lock hovered around 30%

            //Refreash/clear screen
            for (size_t t = 0; t < output.str().size(); ++t)
                cout << "\b"; //clear last character
        }
    }
}
