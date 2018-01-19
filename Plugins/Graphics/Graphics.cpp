using namespace std;

void Graphics::eventLoop()
{
    //manager->startDetachedThread(&Graphics::textualGraphics, this);

    GraphicsInternals::openWindow(string("Sim"));

    //Menu numbers"
      // 0 - Pause
      // 1 - Game
      // 2 - Load
      // 3 - Save
      // 4 - Quit
      // 5 - Options
      // 6 - About
      // 7 - Credits

    while (window->isOpen())
    {
        if (menu == 0) //paused
        {
            pauseMenu();
        }
        else if (menu == 1) //running the game
        {
            game();
        }
        else if (menu == 2)
        {
            bin->load("Saves/Turtle.dat");
            menu = 0;
        }
        else if (menu == 3)
        {
            bin->save();
            menu = 0;
        }
        else if (menu == 4)
        {
            quit();
        }
        else if (menu == 5)
        {
            options();
        }
        else if (menu == 6)
        {
            about();
        }
        else if (menu == 7)
        {
            credits();
        }
    }
}

void  Graphics::pauseMenu()
{

  Bin pauseBin(100, 100, 5);
  Graphics badIdea(&pauseBin, nullptr);
  badIdea.window = window;
  const unsigned int numFloaters = 25;
  for(unsigned int numOfNodes = 0; numOfNodes < numFloaters; ++numOfNodes)
  {
      pauseBin.insert(new Floater((pauseBin.chanceGen(pauseBin.gen))*(pauseBin.getWidth()), (pauseBin.chanceGen(pauseBin.gen))*(pauseBin.getHeight()), &pauseBin));
  }

  auto gameView = window->getView();
  auto pauseView = window->getView();
  pauseView.setSize(window->getSize().x, window->getSize().y);

  while (window->isOpen())
  {
    //check window events
    bool mouseWasClicked = false;
    sf::Event event;
    while (window->pollEvent(event))
    {
        //Basic events for keeping the window responcive and reacting as desired

        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
            manager->kill();
            window->close();
        }
        // catch the resize events
        if (event.type == sf::Event::Resized)
        {
            //scale view to new window size
            sf::View view = sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height));
            //set center to old center
            view.setCenter(window->getView().getCenter());
            //propogate
            gameView = view;
            pauseView = view;
            window->setView(view);
        }

        //Pause control
        if (event.type == sf::Event::KeyPressed)
        {
          if (event.key.code == sf::Keyboard::Escape)
          {
            manager->resume();

            window->setView(gameView);
            menu = 1; //switch to the game menu
            return;
          }
        }
        if (event.type == sf::Event::MouseButtonPressed)
            if (event.mouseButton.button == sf::Mouse::Left)
                mouseWasClicked = true;
    }

    window->setView(gameView);

    //still draw the hexes, but don't have the interactivity of the map
    window->clear();
    GraphicsInternals::drawMap();         //Hex grid
    GraphicsInternals::pauseOverlay();    //Graying screen

    window->setView(pauseView);
    /* <Menu-Graphics>  */
    //Center/proportion finding
    auto center = window->getView().getCenter();
    double hexRadius;
    if (window->getView().getSize().x < window->getView().getSize().y)
        hexRadius = window->getView().getSize().x/8;
    else
        hexRadius = window->getView().getSize().y/8;

    //Draw Mini Sim
    //set a new view
    sf::View miniView = window->getView();
    miniView.setSize(miniView.getSize().x*(pauseBin.getWidth()/2/hexRadius), miniView.getSize().y*(pauseBin.getHeight()/2/hexRadius));
    miniView.setCenter(sf::Vector2f(pauseBin.getWidth()/2, pauseBin.getHeight()/2));
    window->setView(miniView);
    pauseBin.updateEntities(1);
    badIdea.drawMap();  //Hex grid
    badIdea.drawEntities();    //Entites
    //reset back to old view
    window->setView(pauseView);

    //Background hexes
    sf::CircleShape hexa(hexRadius, 6); //Each hex will be a circle with 6 sides
    hexa.rotate(30);
    hexa.setOrigin(hexRadius, hexRadius);
    hexa.setFillColor(sf::Color::Green);
    hexa.setPosition(center.x, center.y+(sqrt(3)*hexRadius)); window->draw(hexa); //Bottom Hex
    hexa.setPosition(center.x, center.y-(sqrt(3)*hexRadius)); window->draw(hexa); //Top Hex
    hexa.setPosition(center.x+(1.5*hexRadius), center.y+(hexRadius*sqrt(3)/2)); window->draw(hexa); //Bottom Right Hex
    hexa.setPosition(center.x+(1.5*hexRadius), center.y-(hexRadius*sqrt(3)/2)); window->draw(hexa); //Top Right Hex
    hexa.setPosition(center.x-(1.5*hexRadius), center.y+(hexRadius*sqrt(3)/2)); window->draw(hexa); //Bottom Left Hex
    hexa.setPosition(center.x-(1.5*hexRadius), center.y-(hexRadius*sqrt(3)/2)); window->draw(hexa); //Top Left Hex

    //Reset hex to normal attributes for next bit
    hexa.setOutlineColor(sf::Color::Blue);
    hexa.setOutlineThickness(3);
    hexa.setFillColor(sf::Color::White);

    //Forground Hexes - the options
    hexa.setPosition(center.x, center.y+(2*hexRadius)); window->draw(hexa); //Bottom Hex
    hexa.setPosition(center.x, center.y-(2*hexRadius)); window->draw(hexa); //Top Hex
    hexa.setPosition(center.x+(1.75*hexRadius), center.y+(hexRadius)); window->draw(hexa); //Bottom Right Hex
    hexa.setPosition(center.x+(1.75*hexRadius), center.y-(hexRadius)); window->draw(hexa); //Top Right Hex
    hexa.setPosition(center.x-(1.75*hexRadius), center.y+(hexRadius)); window->draw(hexa); //Bottom Left Hex
    hexa.setPosition(center.x-(1.75*hexRadius), center.y-(hexRadius)); window->draw(hexa); //Top Left Hex
    hexa.setFillColor(sf::Color::Transparent);
    hexa.setPosition(center.x, center.y); window->draw(hexa); //Middle Hex
    hexa.setFillColor(sf::Color(0, 255, 0, 100));

    //Text overlays
    sf::Text menuItemsText("Controls", font); //"Controls" doesn't exist
    menuItemsText.setCharacterSize(hexRadius/2.25);
    auto textHeight = menuItemsText.getLocalBounds().height;
    //Should be constant, otherwise affected by letters like 'p':

    menuItemsText.setFillColor(sf::Color::Blue);

    menuItemsText.setString("Save"); menuItemsText.setOrigin(menuItemsText.getLocalBounds().width/2, textHeight);
    menuItemsText.setPosition(center.x, center.y-(2*hexRadius)); window->draw(menuItemsText);//Top
    menuItemsText.setString("Load"); menuItemsText.setOrigin(menuItemsText.getLocalBounds().width/2, textHeight);
    menuItemsText.setPosition(center.x, center.y+(2*hexRadius)); window->draw(menuItemsText); //Bottom
    menuItemsText.setString("About"); menuItemsText.setOrigin(menuItemsText.getLocalBounds().width/2, textHeight);
    menuItemsText.setPosition(center.x+(1.75*hexRadius), center.y-(hexRadius)); window->draw(menuItemsText); //Top Right
    menuItemsText.setString("Quit"); menuItemsText.setOrigin(menuItemsText.getLocalBounds().width/2, textHeight);
    menuItemsText.setPosition(center.x+(1.75*hexRadius), center.y+(hexRadius)); window->draw(menuItemsText); //Bottom Right
    menuItemsText.setString("Options"); menuItemsText.setOrigin(menuItemsText.getLocalBounds().width/2, textHeight);
    menuItemsText.setPosition(center.x-(1.75*hexRadius), center.y-(hexRadius)); window->draw(menuItemsText); //Top Left
    menuItemsText.setString("Credits"); menuItemsText.setOrigin(menuItemsText.getLocalBounds().width/2, textHeight);
    menuItemsText.setPosition(center.x-(1.75*hexRadius), center.y+(hexRadius)); window->draw(menuItemsText); //Bottom Left
    /* </Menu-Graphics> */

    //Input
    auto mouseX = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x;
    auto mouseY = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y;

    if (sqrt(pow((mouseX - center.x), 2) + pow((mouseY - (center.y+(2*hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x, center.y+(2*hexRadius)); window->draw(hexa); //Bottom Hex
        if (mouseWasClicked)
        {
            menu = 2; //switch to the load "menu"
            return;
        }
    }
    else if (sqrt(pow((mouseX - center.x), 2) + pow((mouseY - (center.y-(2*hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x, center.y-(2*hexRadius)); window->draw(hexa); //Top Hex
        if (mouseWasClicked)
        {
            menu = 3; //switch to the Save "menu"
            return;
        }
    }
    else if (sqrt(pow((mouseX - (center.x+(1.75*hexRadius))), 2) + pow((mouseY - (center.y+(hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x+(1.75*hexRadius), center.y+(hexRadius)); window->draw(hexa); //Bottom Right Hex
        if (mouseWasClicked)
        {
            menu = 4; //switch to the Quit "menu"
            return;
        }
    }
    else if (sqrt(pow((mouseX - (center.x-(1.75*hexRadius))), 2) + pow((mouseY - (center.y-(hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x-(1.75*hexRadius), center.y-(hexRadius)); window->draw(hexa); //Top Left Hex
        if (mouseWasClicked)
        {
            menu = 5; //switch to the Option "menu"
            return;
        }
    }
    else if (sqrt(pow((mouseX - (center.x+(1.75*hexRadius))), 2) + pow((mouseY - (center.y-(hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x+(1.75*hexRadius), center.y-(hexRadius)); window->draw(hexa); //Top Right Hex
        if (mouseWasClicked)
        {
            menu = 6; //switch to the About "menu"
            return;
        }
    }
    else if (sqrt(pow((mouseX - (center.x-(1.75*hexRadius))), 2) + pow((mouseY - (center.y+(hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x-(1.75*hexRadius), center.y+(hexRadius)); window->draw(hexa); //Bottom Left Hex
        if (mouseWasClicked)
        {
            menu = 7; //switch to the Credits "menu"
            return;
        }
    }

    //Play Button
    hexa.setRadius(hexRadius/2); hexa.setOrigin(hexRadius/2, hexRadius/2);
    hexa.setPointCount(3); hexa.rotate(60);
    hexa.setPosition(center.x, center.y);

    if (sqrt(pow((mouseX - center.x), 2) + pow((mouseY - center.y), 2)) < hexRadius)
    {
        window->draw(hexa);

        if (mouseWasClicked)
        {
            manager->resume();

            window->setView(gameView);
            menu = 1; //switch to the game menu
            return;
        }
    }
    else
    {
        hexa.setFillColor(sf::Color(0, 0, 255, 100)); window->draw(hexa); //Middle Hex
    }

    window->display();
  }
}

void Graphics::game()
{
    //check window events
    sf::Event event;
    while (window->pollEvent(event))
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
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
          manager->pause();

          menu = 0; //switch to the pause menu
          return;
        }
      }
    }
    //Keyboard, mouse, etc
    GraphicsInternals::input();

    //Actually Draw!
    window->clear();
    GraphicsInternals::drawMap();         //Hex grid
    GraphicsInternals::drawEntities();    //Entites
    GraphicsInternals::pauseOverlay();    //Graying screen
    window->display();
}

void Graphics::load()
{
    window->clear();
    auto gameView = window->getView();

    subMenuDefaultActions();

    window->display();
    window->setView(gameView);
}

void Graphics::save()
{
    window->clear();
    auto gameView = window->getView();

    subMenuDefaultActions();

    window->display();
    window->setView(gameView);
}

void Graphics::quit()
{
    window->clear();
    auto gameView = window->getView();
    auto newView = window->getView();
    newView.setSize(window->getSize().x, window->getSize().y);
    newView.setCenter(window->getSize().x/2, window->getSize().y/2);
    window->setView(newView);

    //check window events
    sf::Event event;
    while (window->pollEvent(event))
    {
      //Get window events
      GraphicsInternals::basicEvents(event);

      //Pause control
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          menu = 0; //switch to the pause menu
        }
        if (event.key.code == sf::Keyboard::Return)
        {
            manager->kill();
            window->close();
        }
      }
    }

    window->draw(warningText);

    window->display();
    window->setView(gameView);
}

void Graphics::options()
{
    window->clear();
    auto gameView = window->getView();

    subMenuDefaultActions();

    window->display();
    window->setView(gameView);
}

void Graphics::about()
{
    window->clear();
    auto gameView = window->getView();

    subMenuDefaultActions();

    window->display();
    window->setView(gameView);
}

void Graphics::credits()
{
    window->clear();
    auto gameView = window->getView();

    subMenuDefaultActions();

    window->display();
    window->setView(gameView);
}

void Graphics::subMenuDefaultActions()
{
    auto newView = window->getView();
    newView.setSize(window->getSize().x, window->getSize().y);
    newView.setCenter(window->getSize().x/2, window->getSize().y/2);
    window->setView(newView);

    //check window events
    sf::Event event;
    while (window->pollEvent(event))
    {
      //Get window events
      GraphicsInternals::basicEvents(event);

      //Pause control
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          menu = 0; //switch to the pause menu
        }
      }

      if (event.type == sf::Event::MouseButtonPressed)
      {
          if (event.mouseButton.button == sf::Mouse::Left)
          {
              auto mouseX = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x;
              auto mouseY = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y;

              if (sqrt(pow(mouseX - 85, 2) + pow(mouseY - 85, 2)) < 70)
              {
                menu = 0; //switch to the pause menu
              }
          }
      }

    }

    backButton();
}

void Graphics::backButton()
{
    //Back Button
    sf::CircleShape backCirc(70);
    backCirc.setPosition(15, 15);
    backCirc.setFillColor(sf::Color(255, 0, 0, 100));
    backCirc.setOutlineColor(sf::Color::Red);
    backCirc.setOutlineThickness(3);
    window->draw(backCirc);
    sf::CircleShape backSqr(30, 4);
    backSqr.rotate(45);
    backSqr.setOrigin(30, 30);
    backSqr.setPosition(102, 85);
    backSqr.setFillColor(sf::Color::Blue);
    backSqr.setOutlineColor(sf::Color::Green);
    backSqr.setOutlineThickness(3);
    window->draw(backSqr);
    sf::CircleShape backArrow(30, 3);
    backArrow.rotate(30);
    backArrow.setOrigin(30, 30);
    backArrow.setPosition(68, 85);
    backArrow.setFillColor(sf::Color::Blue);
    backArrow.setOutlineColor(sf::Color::Green);
    backArrow.setOutlineThickness(3);
    window->draw(backArrow);
}

/*
void Graphics::textualGraphics() const
{
    manager->sleep(1000000000); //Wait for window to open

    string spin = "|\\-/";
    while (window->isOpen())
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
*/
