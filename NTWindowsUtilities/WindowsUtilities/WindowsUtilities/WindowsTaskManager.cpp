#include "stdafx.h"
#include "WindowsTaskManager.h"
#include <sstream>

WindowsTaskManager::WindowsTaskManager()
{
}

void taskMethod(Task *task) {
	task->execute();
}

std::string threadId(std::thread *thread) {
	std::stringstream s;
	thread->get_id()._To_text(s);
	return s.str();
}

void WindowsTaskManager::execute(Task *task) {
	std::thread *thread = new std::thread(taskMethod, task);
	std::string id = threadId(thread);
	task->assign(id);
	this->threads.push_back(thread);
}


void WindowsTaskManager::wait(Task *task) {
	int index = indexOf(task);
	std::thread *thread = threads[index];
	this->threads.erase(this->threads.begin()+=index);
	thread->join();
}

int WindowsTaskManager::indexOf(Task *task) {
	int count = this->threads.size();
	std::string taskId = task->getId();
	for (int i = 0; i < count; i++) {
		std::thread *thread = threads[i];
		std::string id = threadId(thread);
		if (id == taskId) {
			return i;
		}
	}
}


WindowsTaskManager::~WindowsTaskManager()
{
	int size = this->threads.size();
	for (int i = 0; i < size; i++) {
		delete threads[i];
	}
}
