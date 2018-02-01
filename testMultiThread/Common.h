#ifndef THREAD_COMMAND_H_
#define THREAD_COMMAND_H_

#define WM_UPDATE_A (WM_USER + 100)
#define WM_UPDATE_B (WM_USER + 101)
#define WM_UPDATE_C (WM_USER + 102)

#define WM_UPDATE_X (WM_USER + 200)


struct THREAD_INFO_PARAM {
    int data1;
    int data2;
    int data3;

    HWND hWnd; 
};

// ÊÂ¼þ Event Ãû³Æ
// const CString WORKER_EVENT_X = _T("workerEventXXX");
// const CString WORKER_EVENT_Y = _T("workerEventYYY");
// const CString WORKER_EVENT_Z = _T("workerEventZZZ");

#define WORKER_EVENT_X  ("workerEventXXX")
#define WORKER_EVENT_Y  ("workerEventYYY")
#define WORKER_EVENT_Z  ("workerEventZZZ")


#define WM_ACTION (WM_USER + 300)

#define WM_THREAD_QUIT (WM_USER + 301)

#endif
