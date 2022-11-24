#pragma once
#include <Source/Singleton.h>
#include <Source/Process.h>
#include <forward_list>

class ProcessManager:public Singleton<ProcessManager>
{
public:
	ProcessManager();
	~ProcessManager();

  void AddProcess(Process* processableObject);
	void RemoveProcess(Process* processableObject);
	void Update();
	void Draw();

private:
	std::forward_list<Process*> processList;


};
