#pragma once
#include <chrono>
#include <Type/Singleton.h>

class Time: public Singleton<Time>
{
public:
  float DeltaTime();
  bool WaitFPS();
  void SetTargetFPS(unsigned int targetFPS);


private:
  float actualFPS;
  unsigned int targetFPS;


};