#include <Source/Application.h>
#include <Source/Core/Platform/EApplicationCallback.h>
#include <Source/Core/Platform/Windows.h>

Omory::Application::Application()
{
}

Omory::Application::~Application()
{
  delete platform;
}

Omory::EApplicationCallback Omory::Application::CreateDevice()
{
  platform = new Windows("", 1280, 720, 60);
  EApplicationCallback ac = platform->CreateDevice();
  return ac;
}

Omory::EApplicationCallback Omory::Application::Initialize()
{
  return EApplicationCallback::RUNNING;
}

Omory::EApplicationCallback Omory::Application::Update()
{
  auto ac = platform->LoopDevide();
  return ac;
}

void Omory::Application::Shutdown()
{
}

void Omory::Application::Run()
{
  EApplicationCallback cb;
  cb = CreateDevice();
  if(cb != EApplicationCallback::RUNNING){ return; }
  cb = Initialize();
  if(cb != EApplicationCallback::RUNNING){ return; }
  do
  {
    Update();
  }while(cb == EApplicationCallback::RUNNING);
  Shutdown();
}
