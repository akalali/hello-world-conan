#include "PocoTimer.h"

#include <iostream>

PocoTimer::PocoTimer()
{
  stopWatch.start();

  Poco::Timer timer(250, 500);

  timer.start(Poco::TimerCallback<PocoTimer>(*this, &PocoTimer::PrintElapsedTime));
  Poco::Thread::sleep(5000);
  timer.stop();
}

void PocoTimer::PrintElapsedTime(Poco::Timer& timer)
{
  std::cout << "Time elapsed: " << stopWatch.elapsed() / 1000 << " milliseconds." << std::endl;
}
