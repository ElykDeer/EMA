using namespace std;

void Graphics::spin() const
{
  string spin = "|\\-/";
  while (1)
      for (int i = 0; i < 4; ++i)
      {
          //Build print statement
          ostringstream output;
          output << "Resolution: " << manager->getResolution();
          output << "; Speed: " << manager->getSpeed();
          output << "; Tick Count: " << manager->getTick();
          output << "; entityCount: " << bin->count();
          output << "; lasTime: " << manager->lasTimeeee.count();
          output << "; time: " << manager->timeeee.count() << " " << spin[i];

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
