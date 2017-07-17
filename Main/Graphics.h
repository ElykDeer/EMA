#ifndef SIM_GRAPHICAL_API
#define SIM_GRAPHICAL_API 1

#include "dataStructure.h"
#include "ThreadManager.h"

class GraphicsInternals
{
public:
  GraphicsInternals(const Bin* const bin, const ThreadManager* const manager);
  virtual ~GraphicsInternals();

  virtual void spin() = 0;

protected:
  const Bin* const bin;
  const ThreadManager* const manager;
};

#include "../Plugins/Graphics/Graphics.h"

#endif
