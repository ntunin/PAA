#include "stdafx.h"
#include "WindowsProcessRunner.h"
#include "WindowsUtils.h"
#include "ProcessManager.h"
#include <strsafe.h>
#include <tchar.h>

#define BUFSIZE 4096

using namespace std;

void startProcessRunner(ProcessRunner *ProcessRunner);

WindowsProcessRunner::WindowsProcessRunner() {
}

void WindowsProcessRunner::startInNewThread() {
	this->thread = std::thread(startProcessRunner, this);
}

void startProcessRunner(ProcessRunner *processRunner) {
	processRunner->run();
}


void WindowsProcessRunner::exe(string command) {
	string input;
	this->exe(command, input);
}

void WindowsProcessRunner::run() {
	ProcessManager::getSharedManager()->run(this);
}


void WindowsProcessRunner::exe(string command, string input) {

	SECURITY_ATTRIBUTES saAttr;

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// Create a pipe for the child process's STDIN. 
	if (input.length() > 0) {
		if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
			ErrorExit(WindowsUtils::wideString("Stdin CreatePipe"));

		// Ensure the write handle to the pipe for STDIN is not inherited. 

		if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
			ErrorExit(WindowsUtils::wideString("Stdin SetHandleInformation"));
	}


	// Create the child process. 
	LPWSTR lpCommand = WindowsUtils::wideString(command);
	CreateChildProcess(lpCommand, input);


	return;
}




void WindowsProcessRunner::wait() {
	this->thread.join();
}

void WindowsProcessRunner::CreateChildProcess(LPWSTR cmd, string &input) {
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	BOOL bSuccess = FALSE;

	// Set up members of the PROCESS_INFORMATION structure. 

	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	// Set up members of the STARTUPINFO structure. 
	// This structure specifies the STDIN and STDOUT handles for redirection.

	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdInput = g_hChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	// Create the child process. 
	bool likeConsole = input.length() == 0;
	bSuccess = CreateProcess((likeConsole) ? NULL : cmd,
		(likeConsole) ? cmd : NULL,     // command line 
		NULL,          // process security attributes 
		NULL,          // primary thread security attributes 
		TRUE,          // handles are inherited 
		CREATE_NEW_CONSOLE,             // creation flags 
		NULL,          // use parent's environment 
		NULL,          // use parent's current directory 
		&siStartInfo,  // STARTUPINFO pointer 
		&piProcInfo);  // receives PROCESS_INFORMATION 

					   // If an error occurs, exit the application. 
	if (!bSuccess)
		ErrorExit(WindowsUtils::wideString("CreateProcess"));
	else {
		if (input.length() > 0) {
			WriteToPipe(input);
		}
		WaitForSingleObject(piProcInfo.hProcess, INFINITE);
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
	}
}

void WindowsProcessRunner::WriteToPipe(string &input) {
	DWORD dwWritten;
	BOOL bSuccess = FALSE;


	bSuccess = WriteFile(g_hChildStd_IN_Wr, input.c_str(), (DWORD)input.size(), &dwWritten, NULL);

	// Close the pipe handle so the child process stops reading. 

	if (!CloseHandle(g_hChildStd_IN_Wr))
		ErrorExit(WindowsUtils::wideString("StdInWr CloseHandle"));
}

void WindowsProcessRunner::ReadFromPipe(void) {
	DWORD dwRead, dwWritten;
	CHAR chBuf[BUFSIZE];
	BOOL bSuccess = FALSE;
	HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (;;)
	{
		bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) break;

		bSuccess = WriteFile(hParentStdOut, chBuf,
			dwRead, &dwWritten, NULL);
		if (!bSuccess) break;
	}
}

void WindowsProcessRunner::ErrorExit(PTSTR lpszFunction) {
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		WindowsUtils::wideString("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(1);
}


WindowsProcessRunner::~WindowsProcessRunner()
{
}