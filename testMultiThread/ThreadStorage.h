#ifndef THREAD_STORAGE_H_
#define THREAD_STORAGE_H_


extern bool g_threadRuningFlag;
extern bool g_threadMasterRunning;

UINT ThreadProcA(LPVOID lpParam);
UINT ThreadProcB(LPVOID lpParam);
UINT ThreadProcC(LPVOID lpParam);

UINT ThreadProcX(LPVOID lpParam);


UINT ThreadProcMaster(LPVOID lpParam);
UINT ThreadProcNewA(LPVOID lpParam);
UINT ThreadProcNewB(LPVOID lpParam);
UINT ThreadProcNewC(LPVOID lpParam);

#endif
