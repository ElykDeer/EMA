#include <string>
#include <iostream>
#include <sstream>

class Graphics : public GraphicsInternals
{
public:
  using GraphicsInternals::GraphicsInternals;

  void eventLoop();

  void visualGraphics();

  void textualGraphics() const;
};
