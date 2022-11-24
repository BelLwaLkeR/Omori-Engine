#pragma once
#include <chrono>
#include <Source/Core/Singleton.h>

class Time: public Singleton<Time>
{
public:
  float DeltaTime();
  bool WaitFPS();
  void SetTargetFPS(int targetFPS);


private:
  float actualFPS;
  float targetFPS;


};