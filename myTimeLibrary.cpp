#ifndef MYTIMELIBRARY_H
#define MYTIMELIBRARY_H

constexpr auto MAX_TIME_TO_GET_INFECTED = 300000;

#include <Windows.h>
class MTL
{
public:
    long long get_current_time()
    {

        SYSTEMTIME currentSystemTime;
        GetSystemTime(&currentSystemTime);

        FILETIME v_ftime;
        ULARGE_INTEGER v_ui;
        SystemTimeToFileTime(&currentSystemTime, &v_ftime);
        v_ui.LowPart = v_ftime.dwLowDateTime;
        v_ui.HighPart = v_ftime.dwHighDateTime;
        __int64 v_right;
        v_right = v_ui.QuadPart / 10000;

        return (long long)(v_right);
    }
};
#endif #pragma once
