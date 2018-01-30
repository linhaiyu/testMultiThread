#include "stdafx.h"
#include "Common.h"
#include "ThreadStorage.h"

bool g_threadRuningFlag = true;

UINT ThreadProcA(LPVOID lpParam)
{
    HWND hwnd = (HWND)lpParam;

    while(g_threadRuningFlag) {
        for (int i = 0; i < 2; ++i)
        {
            CString *pStr = new CString(_T(""));
            pStr->Format("MULTI:  ThreadProcA random data is %d", rand());
            ::PostMessage(hwnd, WM_UPDATE_A, (WPARAM)pStr, 0);

            Sleep(200);
        } 

        Sleep(2000);
    }

    return 0;
}

UINT ThreadProcB(LPVOID lpParam)
{
    HWND hwnd = (HWND)lpParam;

    while(g_threadRuningFlag) {
        CString *pStr = new CString(_T(""));
        pStr->Format("MULTI:  ThreadProcB random data is %d", rand());
        ::PostMessage(hwnd, WM_UPDATE_B, (WPARAM)pStr, 0);

        Sleep(800);
    }
    return 0;
}

UINT ThreadProcC(LPVOID lpParam)
{
    HWND hwnd = (HWND)lpParam;

    while(g_threadRuningFlag) {
        CString *pStr = new CString(_T(""));
        pStr->Format("MULTI:  ThreadProcC random data is %d", rand());
        ::PostMessage(hwnd, WM_UPDATE_C, (WPARAM)pStr, 0);

        Sleep(5000);
    }

    return 0;
}

UINT ThreadProcX(LPVOID lpParam)
{
    THREAD_INFO_PARAM* param = (THREAD_INFO_PARAM*)lpParam;
    
    HWND hwnd = (HWND)param->hWnd;
    int nCount = param->data1;
    
    for (int i = 0; i < nCount; ++i)
    {
        CString *pStr = new CString(_T(""));
        pStr->Format("ThreadProcX No.%d random data is %f", (i+1), rand()/100);
        ::PostMessage(hwnd, WM_UPDATE_X, 0, (LPARAM)pStr);

        Sleep(300);
    }   

    return 0;
}
