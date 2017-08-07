using namespace std;

void Graphics::eventLoop()
{
    manager->startDetachedThread(&Graphics::textualGraphics, this);
    visualGraphics();
}

void Graphics::visualGraphics()
{
    GraphicsInternals::openWindow(string("Sim"));

    while (window.isOpen())
    {
      GraphicsInternals::manageEvents(); //check window events
      GraphicsInternals::input(); //Keyboard, mouse, etc

      //Actually Draw!
      window.clear();
      GraphicsInternals::drawMap();         //Hex grid
      GraphicsInternals::drawEntities();    //Entites
      GraphicsInternals::pauseOverlay();    //Graying screen
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
