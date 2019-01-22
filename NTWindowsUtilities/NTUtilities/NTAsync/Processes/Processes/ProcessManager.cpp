#include "stdafx.h"
#include "ProcessManager.h"
#include <mutex> 

using namespace std;

mutex processManagerMtx;


ProcessManager *ProcessManager::sharedManager = NULL;

ProcessManager::ProcessManager() {
	this->countOfDispatched = 0;
}


ProcessManager::~ProcessManager()
{
}


void ProcessManager::run(ProcessRunner *runner) {
	this->lock();
	this->queuedRunners.push(runner);
	this->unlock();
	this->ping();
}

ProcessManager *ProcessManager::getSharedManager() {
	return sharedManager;
}

void ProcessManager::setSharedManager(ProcessManager *manager) {
	sharedManager = manager;
}

