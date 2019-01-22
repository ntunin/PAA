#include "stdafx.h"
#include "WindowsCacheManager.h"
#include "WindowsUtils.h"
#include <sstream>
#include "NecOutParser.h"

WindowsCacheManager::WindowsCacheManager(std::string path) {
	this->path = path;
	WindowsUtils::createDirectory(path);
}

std::string WindowsCacheManager::cachedFileName(std::string name) {
	std::stringstream str;
	str << path << "/" << name;
	return str.str();
}

bool WindowsCacheManager::cached(std::string filename) {
	std::string path = cachedFileName(filename);
	return WindowsUtils::existsDirectory(path);
}

void WindowsCacheManager::fill(std::string filename, NecOut **outs) {
	std::string path = cachedFileName(filename);
	std::vector<std::string> files = WindowsUtils::contentsOfDirectory(path);
	int count = files.size();
	for (int i = 0; i < count; i++) {
		std::string path = cachedFileName(filename).append("/").append(files[i]);
		int start = path.find_last_of('-') + 1;
		int end = path.find_last_of('.');
		int n = atoi(path.substr(start, end - start).c_str());
		NecOutParser(path, outs[n]);
	}
}


void WindowsCacheManager::cache(std::string filename, NecOut **out) {
	std::string path = cachedFileName(filename);
	WindowsUtils::createDirectory(path);
	WindowsUtils::copy(filename, path.append("/").append(filename));
}


WindowsCacheManager::~WindowsCacheManager()
{
}
