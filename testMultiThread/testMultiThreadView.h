// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// testMultiThreadView.h : CtestMultiThreadView 类的接口
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>

using namespace std;

class CtestMultiThreadView : public CFormView
{
protected: // 仅从序列化创建
	CtestMultiThreadView();
	DECLARE_DYNCREATE(CtestMultiThreadView)

public:
	enum{ IDD = IDD_TESTMULTITHREAD_FORM };

// 特性
public:
	CtestMultiThreadDoc* GetDocument() const;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CtestMultiThreadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
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

#ifndef _DEBUG  // testMultiThreadView.cpp 中的调试版本
inline CtestMultiThreadDoc* CtestMultiThreadView::GetDocument() const
   { return reinterpret_cast<CtestMultiThreadDoc*>(m_pDocument); }
#endif

