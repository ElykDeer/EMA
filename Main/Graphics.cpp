#include "Graphics.h"
using namespace std;

GraphicsInternals::GraphicsInternals(const Bin* const bin, const ThreadManager* const manager)
  : bin(bin), manager(manager) {}

GraphicsInternals::~GraphicsInternals() {}

#include "../Plugins/Graphics/Graphics.cpp"
