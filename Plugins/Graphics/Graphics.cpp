using namespace std;

void Graphics::eventLoop()
{
    //manager->startDetachedThread(&Graphics::textualGraphics, this);

    GraphicsInternals::openWindow(string("Sim"));

    //Menu numbers"
      // 0 - Pause
      // 1 - Game
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
 // window->setView(window->getView());

  while (window->isOpen())
  {
    //check window events
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
            badIdea.window = nullptr;
            menu = 1; //switch to the game menu
            return;
          }
        }

        //add click for menu options
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

    //Text overlay
    sf::Text text("Controls", font, hexRadius/2.25);
    //Should be constant, otherwise affected by letters like 'p':
    auto textHeight = text.getLocalBounds().height;
    text.setFillColor(sf::Color::Blue);

    text.setString("Load"); text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x, center.y-(2*hexRadius)); window->draw(text);//Top
    text.setString("Save"); text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x, center.y+(2*hexRadius)); window->draw(text); //Bottom
    text.setString("Controls"); text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x+(1.75*hexRadius), center.y-(hexRadius)); window->draw(text); //Top Right
    text.setString("Options"); text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x+(1.75*hexRadius), center.y+(hexRadius)); window->draw(text); //Bottom Right
    text.setString("About"); text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x-(1.75*hexRadius), center.y-(hexRadius)); window->draw(text); //Top Left
    text.setString("Credits"); text.setOrigin(text.getLocalBounds().width/2, textHeight);
    text.setPosition(center.x-(1.75*hexRadius), center.y+(hexRadius)); window->draw(text); //Bottom Left
    /* </Menu-Graphics> */

    //Input
    auto mouseX = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x;
    auto mouseY = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y;

    if (sqrt(pow((mouseX - (center.x-(1.75*hexRadius))), 2) + pow((mouseY - (center.y-(hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x-(1.75*hexRadius), center.y-(hexRadius)); window->draw(hexa); //Top Left Hex
    }
    else if (sqrt(pow((mouseX - (center.x-(1.75*hexRadius))), 2) + pow((mouseY - (center.y+(hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x-(1.75*hexRadius), center.y+(hexRadius)); window->draw(hexa); //Bottom Left Hex
    }
    else if (sqrt(pow((mouseX - (center.x+(1.75*hexRadius))), 2) + pow((mouseY - (center.y-(hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x+(1.75*hexRadius), center.y-(hexRadius)); window->draw(hexa); //Top Right Hex
    }
    else if (sqrt(pow((mouseX - (center.x+(1.75*hexRadius))), 2) + pow((mouseY - (center.y+(hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x+(1.75*hexRadius), center.y+(hexRadius)); window->draw(hexa); //Bottom Right Hex
    }
    else if (sqrt(pow((mouseX - center.x), 2) + pow((mouseY - (center.y-(2*hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x, center.y-(2*hexRadius)); window->draw(hexa); //Top Hex
    }
    else if (sqrt(pow((mouseX - center.x), 2) + pow((mouseY - (center.y+(2*hexRadius))), 2)) < hexRadius)
    {
        hexa.setPosition(center.x, center.y+(2*hexRadius)); window->draw(hexa); //Bottom Hex
    }

    //Play Button
    hexa.setRadius(hexRadius/2); hexa.setOrigin(hexRadius/2, hexRadius/2);
    hexa.setPointCount(3); hexa.rotate(60);
    hexa.setPosition(center.x, center.y);

    if (sqrt(pow((mouseX - center.x), 2) + pow((mouseY - center.y), 2)) < hexRadius)
    {
        window->draw(hexa);
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
