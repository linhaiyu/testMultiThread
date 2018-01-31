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

// testMultiThreadView.h : CtestMultiThreadView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>

using namespace std;

class CtestMultiThreadView : public CFormView
{
protected: // �������л�����
	CtestMultiThreadView();
	DECLARE_DYNCREATE(CtestMultiThreadView)

public:
	enum{ IDD = IDD_TESTMULTITHREAD_FORM };

// ����
public:
	CtestMultiThreadDoc* GetDocument() const;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CtestMultiThreadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnBnClickedUpdateButton();
    afx_msg void OnBnClickedStartButton();
    afx_msg void OnBnClickedStopButton();
    afx_msg void OnBnClickedClearButton();
    afx_msg LRESULT OnMessageX(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMessageA(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMessageB(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMessageC(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()

protected:
    
    void UpdateList(CString str);


    CEdit m_ctlInfoEdit;
    CListCtrl m_ctlInfoList;

    CButton m_ctlClearButton;
    CButton m_ctlAdd20Button;
    CButton m_ctlStartMultiThreadButton;
    CButton m_ctlStopMultiThreadButton;

    CWinThread *m_pThreadA;
    CWinThread *m_pThreadB;
    CWinThread *m_pThreadC;

    HANDLE m_ThreadNewAEvent;
    HANDLE m_ThreadNewBEvent;
    HANDLE m_ThreadNewCEvent;
    CWinThread *m_pThreadMaster;
    CWinThread *m_pThreadNewA;
    CWinThread *m_pThreadNewB;
    CWinThread *m_pThreadNewC;

    vector<DWORD> m_vThreadIds;


public:
    afx_msg void OnBnClickedStartSynButton();
    afx_msg void OnBnClickedStopSynButton();
};

#ifndef _DEBUG  // testMultiThreadView.cpp �еĵ��԰汾
inline CtestMultiThreadDoc* CtestMultiThreadView::GetDocument() const
   { return reinterpret_cast<CtestMultiThreadDoc*>(m_pDocument); }
#endif

