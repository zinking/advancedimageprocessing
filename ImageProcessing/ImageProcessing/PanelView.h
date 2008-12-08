#pragma once
#include "afxwin.h"
#include "afxcmn.h"



// CPanelView ������ͼ
class Histogram;

class CPanelView : public CFormView
{
	DECLARE_DYNCREATE(CPanelView)

protected:
	CPanelView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPanelView();

public:
	enum { IDD = IDD_TOOL_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ͼ��ָ����ֵ
	int mThreshhold;
public:
	afx_msg void OnCbnDropdownComboAlgo();
	afx_msg void OnCbnSelchangeComboAlgo();
	afx_msg void OnBtnErosionClick();
	afx_msg void OnBtnDialationClick();
public:
	// �ָ��㷨ѡ��
	CComboBox m_cbAlgorithm;
public:
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	virtual void OnInitialUpdate();
public:
	// ��ֵ����
	CSliderCtrl mSliderBar;
public:
//	afx_msg void OnNMCustomdrawSldThr(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnNMReleasedcaptureSldThr(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	// ��pan������hist
	Histogram* histogram;
	// tooltip for slidercontrol
	CToolTipCtrl m_tooltip;
	afx_msg void OnBnClickedBtnGauss();
	afx_msg void OnBnClickedBtnEdge();
	// gaussian delta parameter slider
	CSliderCtrl deltaSlider;
	afx_msg void OnNMReleasedcaptureSldGdelta(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnopen();
	afx_msg void OnBnClickedBtnclose();
	afx_msg void OnBnClickedBtndistance();
	afx_msg void OnBnClickedBtnskeleton();
	afx_msg void OnBnClickedBtnrestore();
	afx_msg void OnBnClickedBtngradient();
	afx_msg void OnBnClickedBtnedge();
	CComboBox m_cbEdgeType;
	afx_msg void OnBnClickedBtncond();
	afx_msg void OnBnClickedBtngrayre();
	afx_msg void OnBnClickedBtnLdmask();
};


