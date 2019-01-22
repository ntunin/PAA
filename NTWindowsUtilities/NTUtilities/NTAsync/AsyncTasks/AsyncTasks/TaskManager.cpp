#include "stdafx.h"
#include "TaskManager.h"


TaskManager *TaskManager::manager = NULL;

TaskManager::TaskManager()
{
}


TaskManager::~TaskManager()
{
}


TaskManager *TaskManager::getSharedManager() {
	return manager;
}

void TaskManager::setSharedManager(TaskManager *sharedManager) {
	manager = sharedManager;
}
