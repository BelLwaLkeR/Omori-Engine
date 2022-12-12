#include <Source/Application.h>
#include <Source/Core/Platform/Windows.h>

Omory::Application::Application()
{
}

Omory::Application::~Application()
{
  delete platform;
}

Omory::Response Omory::Application::CreateDevice()
{
  platform = new Windows("", 1280, 720, 60);
  Response ac = platform->CreateDevice();
  return ac;
}

Omory::Response Omory::Application::Initialize()
{
  return { EResponseCode::S00_Success };
}

Omory::Response Omory::Application::Update()
{
  auto ac = platform->LoopDevide();
  return ac;
}

void Omory::Application::Shutdown()
{
}

void Omory::Application::Run()
{
  Response cb;
  cb = CreateDevice();
  if(cb.GetCodeHead() != EResponseCodeHead::Success){ return; }
  cb = Initialize();
  if(cb.GetCodeHead() != EResponseCodeHead::Success){ return; }
  do
  {
    Update();
  }while(cb.responseCode == EResponseCode::S01_Continue);
  Shutdown();
}
