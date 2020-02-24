#pragma once

#include "Poco/Timer.h"
#include "Poco/Stopwatch.h"

class PocoTimer
{

public:

  PocoTimer();
  void PrintElapsedTime(Poco::Timer& timer);

private:

  Poco::Stopwatch stopWatch;

};
