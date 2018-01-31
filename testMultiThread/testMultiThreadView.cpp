// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// testMultiThreadView.cpp : CtestMultiThreadView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "testMultiThread.h"
#endif

#include "testMultiThreadDoc.h"
#include "testMultiThreadView.h"

#include "Common.h"
#include "ThreadStorage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CtestMultiThreadView

IMPLEMENT_DYNCREATE(CtestMultiThreadView, CFormView)

BEGIN_MESSAGE_MAP(CtestMultiThreadView, CFormView)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_BN_CLICKED(IDC_UPDATE_BUTTON, &CtestMultiThreadView::OnBnClickedUpdateButton)
    ON_BN_CLICKED(IDC_START_BUTTON, &CtestMultiThreadView::OnBnClickedStartButton)
    ON_BN_CLICKED(IDC_STOP_BUTTON, &CtestMultiThreadView::OnBnClickedStopButton)
    ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CtestMultiThreadView::OnBnClickedClearButton)

    ON_MESSAGE(WM_UPDATE_A, &CtestMultiThreadView::OnMessageA)
    ON_MESSAGE(WM_UPDATE_B, &CtestMultiThreadView::OnMessageB)
    ON_MESSAGE(WM_UPDATE_C, &CtestMultiThreadView::OnMessageC)
    ON_MESSAGE(WM_UPDATE_X, &CtestMultiThreadView::OnMessageX)

    ON_BN_CLICKED(IDC_START_SYN_BUTTON, &CtestMultiThreadView::OnBnClickedStartSynButton)
    ON_BN_CLICKED(IDC_STOP_SYN_BUTTON, &CtestMultiThreadView::OnBnClickedStopSynButton)
END_MESSAGE_MAP()

// CtestMultiThreadView ����/����

CtestMultiThreadView::CtestMultiThreadView()
	: CFormView(CtestMultiThreadView::IDD)
{
	m_pThreadA = NULL;
    m_pThreadB = NULL;
    m_pThreadC = NULL;
    m_pThreadMaster = NULL;
    m_pThreadNewA = NULL;
    m_pThreadNewB = NULL;
    m_pThreadNewC = NULL;
}

CtestMultiThreadView::~CtestMultiThreadView()
{
}

void CtestMultiThreadView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_INFO_EDIT, m_ctlInfoEdit);
    DDX_Control(pDX, IDC_INFO_LIST, m_ctlInfoList);
    DDX_Control(pDX, IDC_CLEAR_BUTTON, m_ctlClearButton);
    DDX_Control(pDX, IDC_UPDATE_BUTTON, m_ctlAdd20Button);
    DDX_Control(pDX, IDC_START_BUTTON, m_ctlStartMultiThreadButton);
    DDX_Control(pDX, IDC_STOP_BUTTON, m_ctlStopMultiThreadButton);
}

BOOL CtestMultiThreadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CtestMultiThreadView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
    m_ctlInfoList.InsertColumn (0, _T("#"), LVCFMT_LEFT, 50);
    m_ctlInfoList.InsertColumn (1, _T("Information"), LVCFMT_LEFT, 300);

    m_ctlStopMultiThreadButton.EnableWindow(FALSE);
}

void CtestMultiThreadView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CtestMultiThreadView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CtestMultiThreadView ���

#ifdef _DEBUG
void CtestMultiThreadView::AssertValid() const
{
	CFormView::AssertValid();
}

void CtestMultiThreadView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CtestMultiThreadDoc* CtestMultiThreadView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestMultiThreadDoc)));
	return (CtestMultiThreadDoc*)m_pDocument;
}
#endif //_DEBUG



void CtestMultiThreadView::UpdateList(CString str)
{
    int index = m_ctlInfoList.GetItemCount();
    CString strIndex;
    strIndex.Format(_T("%d"), index);
    m_ctlInfoList.InsertItem(index, strIndex);
    m_ctlInfoList.SetItemText(index, 1, str);

    m_ctlInfoList.EnsureVisible(m_ctlInfoList.GetItemCount() - 1, TRUE);
}

// CtestMultiThreadView ��Ϣ�������
int CtestMultiThreadView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CFormView::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    CRect rectDummy;
    rectDummy.SetRectEmpty ();

//     const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | LVS_REPORT | LVS_SINGLESEL;
// 
//     if (!m_ctlInfoList.Create (dwViewStyle, rectDummy, this, 0))
//     {
//         TRACE0("Failed to create output view\n");
//         return -1;      // fail to create
//     }
//     m_ctlInfoList.SetExtendedStyle(LVS_EX_FULLROWSELECT /*| LVS_EX_GRIDLINES*/);

    return 0;
}

void CtestMultiThreadView::OnBnClickedUpdateButton()
{
    // �����߳� X������ �� �����ݺ��Զ��˳�

    CString str;
    m_ctlInfoEdit.GetWindowTextA(str);
    int infoCount = atoi(str);
    THREAD_INFO_PARAM infoParam;
    infoParam.data1 = infoCount;
    infoParam.hWnd = this->m_hWnd;

    AfxBeginThread(ThreadProcX, &infoParam);
}


void CtestMultiThreadView::OnBnClickedStartButton()
{
    // �����߳�A��B��C����ʱ��������
    g_threadRuningFlag = true;
    m_pThreadA = AfxBeginThread(ThreadProcA, this->m_hWnd);
    m_pThreadB = AfxBeginThread(ThreadProcB, this->m_hWnd);
    m_pThreadC = AfxBeginThread(ThreadProcC, this->m_hWnd);

    m_ctlStartMultiThreadButton.EnableWindow(FALSE);
    m_ctlStopMultiThreadButton.EnableWindow(TRUE);

}

void CtestMultiThreadView::OnBnClickedStopButton()
{
    MSG msg;
    int nExitThreadCount = 0;
    int nWaitThreadCount = 3;
    HANDLE handles[] = {(m_pThreadA->m_hThread), (m_pThreadB->m_hThread), (m_pThreadC->m_hThread)};

    // �߳��˳���־��ֹͣ�߳�A��B��C
    g_threadRuningFlag = false;

    // �ȴ��߳��˳�
    while(true) {
        DWORD dwRet = MsgWaitForMultipleObjects(nWaitThreadCount, handles, FALSE, INFINITE, QS_ALLINPUT);

        if (dwRet == (WAIT_OBJECT_0 + nWaitThreadCount))
        {
            // ����Ϣ����
            CString str = _T("Received message..");
            UpdateList(str);

            if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } 
        else if(dwRet >= WAIT_OBJECT_0 && dwRet <= (WAIT_OBJECT_0 + nWaitThreadCount))
        {
            // ���߳��˳�
            ++nExitThreadCount;
            CString name[] = {_T("A"), _T("B"), _T("C")};
            CString str;
            str.Format("Thread %s �˳���~~~ ���˳� %d ���߳�", name[dwRet], nExitThreadCount);
            UpdateList(str);

            // �����ȴ��˳����߳�����
            int nIndex = dwRet - WAIT_OBJECT_0;
            handles[nIndex] = handles[nWaitThreadCount - 1];
            handles[nWaitThreadCount - 1] = NULL;
            --nWaitThreadCount;

            if (nExitThreadCount >= 3)
            {
                break;
            }
        }
        else {
            break;
        }
    }

    m_pThreadA = NULL;
    m_pThreadB = NULL;
    m_pThreadC = NULL;

    m_ctlStartMultiThreadButton.EnableWindow(TRUE);
    m_ctlStopMultiThreadButton.EnableWindow(FALSE);

    CString str = _T("�����̶߳��˳���~~");
    UpdateList(str);
}

void CtestMultiThreadView::OnBnClickedClearButton()
{
    m_ctlInfoList.DeleteAllItems();
}


LRESULT CtestMultiThreadView::OnMessageX(WPARAM wParam, LPARAM lParam)
{
    CString *pStr = (CString*) lParam;
    UpdateList(*pStr);
    delete pStr;

    return 0;
}

LRESULT CtestMultiThreadView::OnMessageA(WPARAM wParam, LPARAM lParam)
{
    CString *pStr = (CString*) wParam;
    UpdateList(*pStr);
    delete pStr;

    return 0;
}

LRESULT CtestMultiThreadView::OnMessageB(WPARAM wParam, LPARAM lParam)
{
    CString *pStr = (CString*) wParam;
    UpdateList(*pStr);
    delete pStr;

    return 0;
}

LRESULT CtestMultiThreadView::OnMessageC(WPARAM wParam, LPARAM lParam)
{
    CString *pStr = (CString*) wParam;
    UpdateList(*pStr);
    delete pStr;

    return 0;
}

void CtestMultiThreadView::OnBnClickedStartSynButton()
{
    m_ThreadNewAEvent = CreateEvent(NULL, TRUE, FALSE, "NewAEvent");
    m_ThreadNewBEvent = CreateEvent(NULL, TRUE, FALSE, "NewBEvent");
    m_ThreadNewCEvent = CreateEvent(NULL, TRUE, FALSE, "NewCEvent");

    // ���������̺߳͹����߳�
    m_pThreadNewA = AfxBeginThread(ThreadProcNewA, this->m_hWnd);
    m_pThreadNewB = AfxBeginThread(ThreadProcNewB, this->m_hWnd);
    m_pThreadNewC = AfxBeginThread(ThreadProcNewC, this->m_hWnd);

    m_vThreadIds.clear();
    m_vThreadIds.push_back(m_pThreadNewA->m_nThreadID);
    m_vThreadIds.push_back(m_pThreadNewB->m_nThreadID);
    m_vThreadIds.push_back(m_pThreadNewC->m_nThreadID);

    g_threadMasterRunning = true;

    m_pThreadMaster = AfxBeginThread(ThreadProcMaster, &m_vThreadIds);

    SetEvent(m_ThreadNewAEvent);
    SetEvent(m_ThreadNewBEvent);
    SetEvent(m_ThreadNewCEvent);
}


void CtestMultiThreadView::OnBnClickedStopSynButton()
{
    MSG msg;
    int nExitThreadCount = 0;
    int nWaitThreadCount = 4;
    HANDLE handles[] = {(m_pThreadNewA->m_hThread), (m_pThreadNewB->m_hThread), (m_pThreadNewC->m_hThread), m_pThreadMaster->m_hThread};

    // �߳��˳���־��ֹͣ�߳�Master and NewA��NewB��NewC
    g_threadMasterRunning = false;

    // �ȴ��߳��˳�
    while(true) {
        DWORD dwRet = MsgWaitForMultipleObjects(nWaitThreadCount, handles, FALSE, INFINITE, QS_ALLINPUT);

        if (dwRet == (WAIT_OBJECT_0 + nWaitThreadCount))
        {
            // ����Ϣ����
            CString str = _T("Received message..");
            UpdateList(str);

            if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } 
        else if(dwRet >= WAIT_OBJECT_0 && dwRet <= (WAIT_OBJECT_0 + nWaitThreadCount))
        {
            // ���߳��˳�
            ++nExitThreadCount;
            CString name[] = {_T("NewA"), _T("NewB"), _T("NewC")};
            CString str;
            str.Format("Thread %s �˳���~~~ ���˳� %d ���߳�", name[dwRet], nExitThreadCount);
            UpdateList(str);

            // �����ȴ��˳����߳�����
            int nIndex = dwRet - WAIT_OBJECT_0;
            handles[nIndex] = handles[nWaitThreadCount - 1];
            handles[nWaitThreadCount - 1] = NULL;
            --nWaitThreadCount;

            if (nExitThreadCount >= 4)
            {
                break;
            }
        }
        else {
            break;
        }
    }

    m_pThreadNewA = NULL;
    m_pThreadNewB = NULL;
    m_pThreadNewC = NULL;
    m_pThreadMaster = NULL;

    CloseHandle(m_ThreadNewAEvent);
    CloseHandle(m_ThreadNewBEvent);
    CloseHandle(m_ThreadNewCEvent);

    CString str = _T("ȴʱӦ���������̶߳��˳���~~");
    UpdateList(str);
}
