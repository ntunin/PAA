#include "stdafx.h"
#include "Task.h"


Task::Task()
{
}

void Task::assign(std::string id) {
	this->id = id;
}

std::string Task::getId() {
	return this->id;
}

Task::~Task()
{
}
