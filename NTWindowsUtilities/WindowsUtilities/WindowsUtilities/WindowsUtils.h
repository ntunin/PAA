#pragma once
#include <Windows.h>
#include <string>
#include <vector>

#ifdef WINDOWSUTILITIES_EXPORTS  
#define WINDOWSUTILITIES_API __declspec(dllexport)   
#else  
#define WINDOWSUTILITIES_API __declspec(dllimport)   
#endif 


class WindowsUtils
{
public:
	WINDOWSUTILITIES_API static LPWSTR wideString(const std::string& instr);
	WINDOWSUTILITIES_API static std::string string(LPWSTR instr);
	WINDOWSUTILITIES_API static void createDirectory(const std::string& path);
	WINDOWSUTILITIES_API static bool existsDirectory(const std::string& path);
	WINDOWSUTILITIES_API static void copy(std::string& from, std::string& to);
	WINDOWSUTILITIES_API static std::vector<std::string> contentsOfDirectory(const std::string& path);
	WINDOWSUTILITIES_API static std::uint64_t time();
	WINDOWSUTILITIES_API WindowsUtils();
	WINDOWSUTILITIES_API ~WindowsUtils();
};

