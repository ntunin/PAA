#include "stdafx.h"
#include "WindowsProcessManager.h"

using namespace std;

WindowsProcessManager::WindowsProcessManager()
{
	lck = unique_lock<mutex>(processManagerMtx, defer_lock);
}


int WindowsProcessManager::getCoresCount() {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int numCPU = sysinfo.dwNumberOfProcessors;
	return numCPU;
}

WindowsProcessManager::~WindowsProcessManager()
{
}

void WindowsProcessManager::ping() {
	if (this->queuedRunners.size() == 0) {
		return;
	}
	ProcessRunner *runner = NULL;
	unique_lock<mutex> lck(processManagerMtx, defer_lock);
	lck.lock();
	int coresCount = this->getCoresCount();
	if (countOfDispatched < coresCount) {
		runner = this->queuedRunners.front();
		this->queuedRunners.pop();
	}
	lck.unlock();
	if (runner != NULL) {
		lck.lock();
		this->countOfDispatched++;
		lck.unlock();
		runner->dispatch();
		lck.lock();
		this->countOfDispatched--;
		lck.unlock();
		this->ping();
	}
}


void WindowsProcessManager::lock() {
	lck.lock();
}

void WindowsProcessManager::unlock() {
	lck.unlock();
}
