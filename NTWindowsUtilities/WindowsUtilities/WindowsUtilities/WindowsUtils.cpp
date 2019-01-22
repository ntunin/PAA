#include "stdafx.h"
#include "WindowsUtils.h"
#include <stdio.h>
#include <strsafe.h>
#include <chrono>

WindowsUtils::WindowsUtils()
{
}

LPWSTR WindowsUtils::wideString(const std::string &instr) {
	int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);
	if (bufferlen == 0) {
		return 0;
	}
	LPWSTR widestr = new WCHAR[bufferlen + 1];
	::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);
	widestr[bufferlen] = 0;
	return widestr;
}

std::string WindowsUtils::string(LPWSTR instr) {
	int bufferlen = ::WideCharToMultiByte(CP_ACP, 0, instr, wcslen(instr), NULL, 0, NULL, false);
	if (bufferlen == 0) {
		return 0;
	}
	LPSTR str = new CHAR[bufferlen + 1];
	::WideCharToMultiByte(CP_ACP, 0, instr, wcslen(instr), str, bufferlen, NULL, false);
	str[bufferlen] = 0;
	return std::string(str);
}

void WindowsUtils::createDirectory(const std::string& path) {
	LPWSTR lpPath = wideString(path);
	CreateDirectory(lpPath, NULL);
}


bool WindowsUtils::existsDirectory(const std::string& path) {
	LPWSTR lpPath = wideString(path);
	DWORD attrs = GetFileAttributes(lpPath);
	if (attrs == INVALID_FILE_ATTRIBUTES)
		return false;

	if (attrs & FILE_ATTRIBUTE_DIRECTORY)
		return true;  

	return false;
}


std::vector<std::string> WindowsUtils::contentsOfDirectory(const std::string& path) {
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;
	LPWSTR lpPath = wideString(path);
	std::vector<std::string> result;

	StringCchCopy(szDir, MAX_PATH, lpPath);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind) {
		//Shared::bundle().log()->print("INVALID FILE HANDLE <WindowsUtils::contentsOfDirectory>");
		return result;
	}

	do	{
		std::string fileName = string(ffd.cFileName);
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (fileName != "." && fileName != "..") {
				//Shared::bundle().log()->print(fileName.append("\n"));
			}
		} else {
			result.push_back(fileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) {
		//Shared::bundle().log()->print("FILE ERROR <WindowsUtils::contentsOfDirectory>");
	}

	FindClose(hFind);
	return result;
}

std::uint64_t WindowsUtils::time() {
	return std::chrono::duration_cast< std::chrono::milliseconds >(
		std::chrono::system_clock::now().time_since_epoch()
		).count();
}


void WindowsUtils::copy(std::string& from, std::string& to) {
	LPWSTR lpFrom = wideString(from);
	LPWSTR lpTo = wideString(to);
	CopyFile(lpFrom, lpTo, false);
}

WindowsUtils::~WindowsUtils()
{
}
