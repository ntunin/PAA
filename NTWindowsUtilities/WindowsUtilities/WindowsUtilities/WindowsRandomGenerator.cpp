#include "stdafx.h"
#include "WindowsRandomGenerator.h"
#include "TaskManager.h"

using namespace std;

WindowsRandomGenerator::WindowsRandomGenerator() {
	task = new GeneratorTask;
	TaskManager::getSharedManager()->execute(task);
}

void WindowsRandomGenerator::stop() {
	task->stop();
}

int WindowsRandomGenerator::next() {
	return task->next();
}

void WindowsRandomGenerator::GeneratorTask::execute() {
	unique_lock<mutex> lck(randMtx, defer_lock);
	lck.lock();
	running = true;
	squireIndex = rand() % 1000;
	lck.unlock();
	while (running) {
		lck.lock();
		squireIndex = (squireIndex*squireIndex) % 1000;
		value = rand() * (time(NULL) % 100)/squireIndex;
		lck.unlock();
	}
}

void WindowsRandomGenerator::GeneratorTask::stop() {
	unique_lock<mutex> lck(randMtx, defer_lock);
	lck.lock();
	running = false;
	lck.unlock();
}

int WindowsRandomGenerator::GeneratorTask::next() {
	unique_lock<mutex> lck(randMtx, defer_lock);
	lck.lock();
	int v = value;
	value = rand() * (time(NULL) % 100);
	lck.unlock();
	return v;
}


WindowsRandomGenerator::~WindowsRandomGenerator()
{
}
