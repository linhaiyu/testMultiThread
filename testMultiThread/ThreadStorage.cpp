#include "stdafx.h"
#include <Windows.h> 
#include <vector>

#include "Common.h"
#include "ThreadStorage.h"

using namespace std;

bool g_threadRuningFlag = true;
bool g_threadMasterRunning = true;

UINT ThreadProcA(LPVOID lpParam)
{
    HWND hwnd = (HWND)lpParam;

    while(g_threadRuningFlag) {
        CString *pStr = new CString(_T(""));
        pStr->Format("MULTI:  ThreadProc A random data is %d", rand());
        ::PostMessage(hwnd, WM_UPDATE_A, (WPARAM)pStr, 0);

        Sleep(800);
    }

    return 0;
}

UINT ThreadProcB(LPVOID lpParam)
{
    HWND hwnd = (HWND)lpParam;

    while(g_threadRuningFlag) {
        CString *pStr = new CString(_T(""));
        pStr->Format("MULTI:  ThreadProc B random data is %d", rand());
        ::PostMessage(hwnd, WM_UPDATE_B, (WPARAM)pStr, 0);

        Sleep(200);
    }
    return 0;
}

UINT ThreadProcC(LPVOID lpParam)
{
    HWND hwnd = (HWND)lpParam;

    while(g_threadRuningFlag) {
        CString *pStr = new CString(_T(""));
        pStr->Format("MULTI:  ThreadProc C random data is %d", rand());
        ::PostMessage(hwnd, WM_UPDATE_C, (WPARAM)pStr, 0);

        Sleep(1100);
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

UINT ThreadProcMaster(LPVOID lpParam)
{
    vector<DWORD>* pV = (vector<DWORD>*)lpParam;

    // TODO: 等待三个事件，然后发送Action消息
    HANDLE eventA = OpenEvent(EVENT_ALL_ACCESS, TRUE, "NewAEvent");
    HANDLE eventB = OpenEvent(EVENT_ALL_ACCESS, TRUE, "NewBEvent");
    HANDLE eventC = OpenEvent(EVENT_ALL_ACCESS, TRUE, "NewCEvent");

    HANDLE handles[] = {eventA, eventB, eventC};

    while (g_threadMasterRunning)
    {
        DWORD dw = WaitForMultipleObjects(3, handles, TRUE, 6000);

        if (dw == WAIT_TIMEOUT)
        {
            continue;
        } 
        else if (dw == WAIT_OBJECT_0)
        {
            ResetEvent(eventA);
            ResetEvent(eventB);
            ResetEvent(eventC);

            vector<DWORD>::iterator it = pV->begin();
            for (; it != pV->end(); ++it)
            {
                DWORD id = *it;
                PostThreadMessage(id, WM_ACTION, 0, 0);
            }
        }
        else
        {
            continue;
        }
    }

    vector<DWORD>::iterator it = pV->begin();
    for (; it != pV->end(); ++it)
    {
        DWORD id = *it;
        PostThreadMessage(id, WM_THREAD_QUIT, 0, 0);
    }

    return 0;
}

UINT ThreadProcNewA(LPVOID lpParam)
{
    HWND hwnd = (HWND)lpParam;
    MSG msg;
    while(true) {
        GetMessage(&msg, NULL, 0, 0);

        if (msg.message == WM_ACTION)
        {
            CString *pStr = new CString(_T(""));
            pStr->Format("MULTI:  ThreadProc New A random data is %d", rand());
            ::PostMessage(hwnd, WM_UPDATE_A, (WPARAM)pStr, 0);
            
            Sleep(800);
            HANDLE event = OpenEvent(EVENT_ALL_ACCESS, TRUE, "NewAEvent");
            SetEvent(event);
        } 
        else if(msg.message == WM_THREAD_QUIT)
        {
            break;
        }
        else 
        {
            continue;
        }
    }   

    return 0;
}

UINT ThreadProcNewB(LPVOID lpParam)
{
    HWND hwnd = (HWND)lpParam;
    MSG msg;
    while(true) {
        GetMessage(&msg, NULL, 0, 0);

        if (msg.message == WM_ACTION)
        {
            CString *pStr = new CString(_T(""));
            pStr->Format("MULTI:  ThreadProc New B random data is %d", rand());
            ::PostMessage(hwnd, WM_UPDATE_B, (WPARAM)pStr, 0);

            Sleep(200);
            HANDLE event = OpenEvent(EVENT_ALL_ACCESS, TRUE, "NewBEvent");
            SetEvent(event);
        } 
        else if(msg.message == WM_THREAD_QUIT)
        {
            break;
        }
        else 
        {
            continue;
        }
    }   

    return 0;
}

UINT ThreadProcNewC(LPVOID lpParam)
{
    HWND hwnd = (HWND)lpParam;
    MSG msg;
    while(true) {
        GetMessage(&msg, NULL, 0, 0);

        if (msg.message == WM_ACTION)
        {
            CString *pStr = new CString(_T(""));
            pStr->Format("MULTI:  ThreadProc New C random data is %d", rand());
            ::PostMessage(hwnd, WM_UPDATE_C, (WPARAM)pStr, 0);

            Sleep(1100);
            HANDLE event = OpenEvent(EVENT_ALL_ACCESS, TRUE, "NewCEvent");
            SetEvent(event);
        } 
        else if(msg.message == WM_THREAD_QUIT)
        {
            break;
        }
        else 
        {
            continue;
        }
    }   

    return 0;
}
