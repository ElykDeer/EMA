#include "Graphics.h"
using namespace std;

GraphicsInternals::GraphicsInternals(const Bin* const bin, const ThreadManager* const manager)
  : bin(bin), manager(manager) {}

GraphicsInternals::~GraphicsInternals() {}

void GraphicsInternals::openWindow(const string& name)
{
  window.create(sf::VideoMode(bin->getWidth(), bin->getHeight()), name, sf::Style::Default);
}

void GraphicsInternals::drawMap() const
{

}

void GraphicsInternals::drawEntities() const
{

}

#include "../Plugins/Graphics/Graphics.cpp"
