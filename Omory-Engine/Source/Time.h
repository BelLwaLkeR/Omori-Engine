#pragma once
#include <chrono>
#include <Source/Singleton.h>

class Time: public Singleton<Time>
{
public:
  float DeltaTime();
  void SetFPS();
  bool WaitFPS();


private:
  float targetFPS;
  float actualFPS;

};