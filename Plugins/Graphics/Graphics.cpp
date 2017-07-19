using namespace std;

void Graphics::spin()
{
    string spin = "|\\-/";
    GraphicsInternals::openWindow(string("Sim"));
    while (window.isOpen())
    {
        //Create window, check window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
              manager->kill();
              window.close();
            }
        }

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
