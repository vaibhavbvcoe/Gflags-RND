// testHeapCorruption.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<Windows.h>
#include<iostream>
using namespace std;

void WriteMemoryDump()
{
    wchar_t command[1024] = L"";
    wsprintf(command, L"procdump.exe -accepteula -ma %d d:\full.dmp",
    GetCurrentProcessId());

    STARTUPINFOW inInfo;
    ZeroMemory(&inInfo, sizeof(inInfo));
    inInfo.cb = sizeof(inInfo);
    PROCESS_INFORMATION outInfo;
    ZeroMemory(&outInfo, sizeof(outInfo));
    const BOOL status = CreateProcessW(NULL, command, NULL, NULL, FALSE, 0,
    NULL, NULL, &inInfo, &outInfo);

    if (status)
    {
        wcout << outInfo.dwProcessId << endl;
        WaitForSingleObject(outInfo.hProcess, INFINITE);
        CloseHandle(outInfo.hProcess);
        CloseHandle(outInfo.hThread);
    }
}
LONG WINAPI UnhandledExceptionHandler(EXCEPTION_POINTERS* pExceptionInfo){
    __try
    {
        WriteMemoryDump();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char* argv[])
{
    SetUnhandledExceptionFilter(UnhandledExceptionHandler);
    int* ptr = new int();
    delete ptr;
    delete ptr;
    return 0;
}