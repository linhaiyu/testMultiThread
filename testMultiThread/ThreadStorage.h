#ifndef THREAD_STORAGE_H_
#define THREAD_STORAGE_H_


extern bool g_threadRuningFlag;

UINT ThreadProcA(LPVOID lpParam);
UINT ThreadProcB(LPVOID lpParam);
UINT ThreadProcC(LPVOID lpParam);

UINT ThreadProcX(LPVOID lpParam);

#endif
