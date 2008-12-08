// DIPDoc.h : CDIPDoc 类的接口
//


#pragma once
#include "Histogram.h"



class CDIPDoc : public CDocument
{
protected: // 仅从序列化创建
	CDIPDoc();
	DECLARE_DYNCREATE(CDIPDoc)

// 属性
public:
	//CvvImage cvImage;
	//CvvImage thImage;
	//Histogram hist;
	//IplImage* pImg;

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CDIPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 装载并将原RGB图像转化为灰度图
	//bool LoadGrayImage(CString strPicPath);
public:
	// 创建二值化后的图形
	//int CreateBinaryImage(int threshHold);
};


