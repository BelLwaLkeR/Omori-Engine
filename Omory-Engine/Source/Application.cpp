#include <Application.h>
#include <Core/Platform/Windows/WindowsPlatform.h>
#include <Core/Platform/APlatform.h>

Omory::Application::Application()
{
}

Omory::Application::~Application()
{
}

Omory::Response Omory::Application::CreateDevice()
{
  platform = MakeUnique<WindowsPlatform>("", 1280, 720, 60);
  if(platform->CreateDevice().IsFailed()){ return { EResponseCode::E10_DeviceAnythingError, "" }; }
  //TODO : d3d12CommonCreateDeviceを何とかして呼ぶ。

  return { EResponseCode::S00_Success };
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
  if(cb.IsFailed()){ return; }
  cb = Initialize();
  if(cb.GetCodeHead() != EResponseCodeHead::Success){ return; }
  do
  {
    cb = Update();
  }while(cb.responseCode == EResponseCode::S01_Continue);
  Shutdown();
}
