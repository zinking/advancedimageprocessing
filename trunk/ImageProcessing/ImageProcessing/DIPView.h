// DIPView.h : CDIPView 类的接口
//


#pragma once
class CDIPDoc;


class CDIPView : public CView
{
protected: // 仅从序列化创建
	CDIPView();
	DECLARE_DYNCREATE(CDIPView)

// 属性
public:
	CDIPDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CDIPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	// //分割器
	//CSplitterWnd mSplitter;
public:
	
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // DIPView.cpp 中的调试版本
inline CDIPDoc* CDIPView::GetDocument() const
   { return reinterpret_cast<CDIPDoc*>(m_pDocument); }
#endif

