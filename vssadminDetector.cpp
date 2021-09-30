#ifndef VSSADMINDETECTOR_H
#define VSSADMINDETECTOR_H
#include <cstdio>
#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <tlhelp32.h>
#include "threadData.h"
#include "myTimeLibrary.h"

class VD
{

public:
    bool IsProcessRunning(char *processName)
    {
        bool exists = false;
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

        while (Process32Next(snapshot, &entry))
            if (!_stricmp(entry.szExeFile, processName))
                exists = true;

        CloseHandle(snapshot);
        return exists;
    }

    DWORD WINAPI vssadmin_detector(LPVOID lpParam)
    {

        PMYDATA pData = (PMYDATA)lpParam;

        while (*pData->detected == false)
        {

            while (!IsProcessRunning((char *)pData->path) && (*pData->detected == false))
                ;

            if (*pData->detected)
                return 0;

            printf("VSSAdmin.exe was run\n");

            pData->last_sucessful = get_current_time();

            Sleep(MAX_TIME_TO_GET_INFECTED);
        }

        return 0;
    }
};
#endif
#pragma once
DWORD WINAPI vssadmin_detector(LPVOID lpParam);
