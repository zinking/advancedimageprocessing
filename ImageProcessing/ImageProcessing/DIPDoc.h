// DIPDoc.h : CDIPDoc ��Ľӿ�
//


#pragma once
#include "Histogram.h"



class CDIPDoc : public CDocument
{
protected: // �������л�����
	CDIPDoc();
	DECLARE_DYNCREATE(CDIPDoc)

// ����
public:
	//CvvImage cvImage;
	//CvvImage thImage;
	//Histogram hist;
	//IplImage* pImg;

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CDIPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	// װ�ز���ԭRGBͼ��ת��Ϊ�Ҷ�ͼ
	//bool LoadGrayImage(CString strPicPath);
public:
	// ������ֵ�����ͼ��
	//int CreateBinaryImage(int threshHold);
};


