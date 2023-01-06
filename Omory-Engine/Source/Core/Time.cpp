#include "Time.h"

float Time::DeltaTime()
{
    return 0.0f;
}

bool Time::WaitFPS()
{
    return false;
}

void Time::SetTargetFPS(unsigned int targetFPS)
{
  if(targetFPS <=0){ return; }
  this->targetFPS = targetFPS;
}
