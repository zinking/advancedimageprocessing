// DIPView.h : CDIPView ��Ľӿ�
//


#pragma once
class CDIPDoc;


class CDIPView : public CView
{
protected: // �������л�����
	CDIPView();
	DECLARE_DYNCREATE(CDIPView)

// ����
public:
	CDIPDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CDIPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	// //�ָ���
	//CSplitterWnd mSplitter;
public:
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // DIPView.cpp �еĵ��԰汾
inline CDIPDoc* CDIPView::GetDocument() const
   { return reinterpret_cast<CDIPDoc*>(m_pDocument); }
#endif

