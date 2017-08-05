using namespace std;

void Graphics::evnetLoop()
{
    manager->startDetachedThread(&Graphics::textualGraphics, this);
    visualGraphics();
}

void Graphics::visualGraphics()
{
    GraphicsInternals::openWindow(string("Sim"));

    //Drag/drop
    sf::Vector2f oldPos;
    bool moving = false;
    sf::View view = window.getView();

    while (window.isOpen())
    {

      //manage events (in more detail than GraphicsInternals::manageEvents)
      //check window events
      sf::Event event;
      while (window.pollEvent(event))
      {
        //Use default controls
        #include "../../Main/Graphics/Events.cpp"

        //Add drag/drop
        if (event.type == sf::Event::MouseButtonPressed) // Mouse button is pressed, get the position and set moving as active
            if (event.mouseButton.button == 0)
            {
                moving = true;
                oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            }
        if (event.type == sf::Event::MouseButtonReleased)
            if (event.mouseButton.button == 0) // Mouse button is released, no longer move
                moving = false;
        if (event.type == sf::Event::MouseMoved)
        {
            if (!moving)
                continue;
            // Determine the new position in world coordinates
            const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            // Determine how the cursor has moved
            // Swap these to invert the movement direction
            const sf::Vector2f deltaPos = oldPos - newPos;

            // Move our view accordingly and update the window
            view.move(deltaPos);
            view.setSize(window.getView().getSize());
            window.setView(view);

            // Save the new position as the old one
            // We're recalculating this, since we've changed the view
            oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        }
      }

      GraphicsInternals::input(); //Keyboard, mouse, etc

      //Actually Draw!
      window.clear();

      GraphicsInternals::drawMap();
      GraphicsInternals::drawEntities();
      GraphicsInternals::pauseOverlay();

      window.display();
    }
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
