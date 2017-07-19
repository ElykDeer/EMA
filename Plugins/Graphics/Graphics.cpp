using namespace std;

void Graphics::spin()
{
    manager->startDetachedThread(&Graphics::textualGraphics, this);
    visualGraphics();
}

void Graphics::visualGraphics()
{
    GraphicsInternals::openWindow(string("Sim"));

    while (window.isOpen())
    {
      GraphicsInternals::manageEvents();

      //Actually Draw!
      window.clear();

      GraphicsInternals::drawMap();
      GraphicsInternals::drawEntities();

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
            output << "; entCount: " << bin->count();
            output << "; " << manager->lasTimeeee.count();
            output << "; " << manager->timeeee.count() << " " << spin[i] << "    ";

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
