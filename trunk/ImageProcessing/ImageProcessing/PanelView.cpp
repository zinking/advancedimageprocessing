// PanelView.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "PanelView.h"
#include "MainFrm.h"
#include "PicView.h"
#include "ThAlgorithm.h"


// CPanelView

IMPLEMENT_DYNCREATE(CPanelView, CFormView)

CPanelView::CPanelView()
	: CFormView(CPanelView::IDD)
	, mThreshhold(0),histogram(NULL)
{

}

CPanelView::~CPanelView()
{
}

void CPanelView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLD_THR, mThreshhold);
	DDV_MinMaxInt(pDX, mThreshhold, 0, 255);
	DDX_Control(pDX, IDC_COMBO_ALGO, m_cbAlgorithm);
	DDX_Control(pDX, IDC_SLD_THR, mSliderBar);
	DDX_Control(pDX, IDC_SLD_GDELTA, deltaSlider);
	DDX_Control(pDX, ID_CMB_MTYPE, m_cbEdgeType);
}

BEGIN_MESSAGE_MAP(CPanelView, CFormView)
	ON_CBN_DROPDOWN(IDC_COMBO_ALGO, &CPanelView::OnCbnDropdownComboAlgo)
	ON_CBN_SELCHANGE(IDC_COMBO_ALGO, &CPanelView::OnCbnSelchangeComboAlgo)
//	ON_WM_CREATE()
//ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_THR, &CPanelView::OnNMCustomdrawSldThr)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_THR, &CPanelView::OnNMReleasedcaptureSldThr)
ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
//ON_BN_CLICKED(IDC_BTN_GAUSS, &CPanelView::OnBnClickedBtnGauss)
ON_BN_CLICKED(IDC_BTN_EDGE, &CPanelView::OnBnClickedBtnEdge)
ON_BN_CLICKED(IDC_BTN_ERO, &CPanelView::OnBtnErosionClick)
ON_BN_CLICKED(IDC_BTN_DIA, &CPanelView::OnBtnDialationClick)
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_GDELTA, &CPanelView::OnNMReleasedcaptureSldGdelta)
ON_BN_CLICKED(IDC_BTNOPEN, &CPanelView::OnBnClickedBtnopen)
ON_BN_CLICKED(IDC_BTNCLOSE, &CPanelView::OnBnClickedBtnclose)
ON_BN_CLICKED(IDC_BTNDISTANCE, &CPanelView::OnBnClickedBtndistance)
ON_BN_CLICKED(IDC_BTNSKELETON, &CPanelView::OnBnClickedBtnskeleton)
ON_BN_CLICKED(IDC_BTNRESTORE, &CPanelView::OnBnClickedBtnrestore)
ON_BN_CLICKED(IDC_BTNGRADIENT, &CPanelView::OnBnClickedBtngradient)
ON_BN_CLICKED(IDC_BTNEDGE, &CPanelView::OnBnClickedBtnedge)
ON_BN_CLICKED(IDC_BTNCOND, &CPanelView::OnBnClickedBtncond)
ON_BN_CLICKED(IDC_BTNGRAYRE, &CPanelView::OnBnClickedBtngrayre)
ON_BN_CLICKED(IDC_BTN_LDMASK, &CPanelView::OnBnClickedBtnLdmask)
//ON_BN_CLICKED(IDC_BTN_MODE, &CPanelView::OnBnClickedBtnMode)
ON_BN_CLICKED(IDC_BTN_CBR, &CPanelView::OnBnClickedBtnCbr)
END_MESSAGE_MAP()


// CPanelView 诊断

#ifdef _DEBUG
void CPanelView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPanelView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPanelView 消息处理程序

void CPanelView::OnCbnDropdownComboAlgo()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("hello");
}

void CPanelView::OnCbnSelchangeComboAlgo()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("hello");
	//CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent(); 
	//CPicView* pview=(CPicView*)MainFrame->m_picSplitter.GetPane(1,0);
	//pview->InitializeUpdate();


	//usage of combo-box 
	//see http://hi.baidu.com/lzycsd/blog/item/71f8d9edb67d864978f05546.html

	int sel = m_cbAlgorithm.GetCurSel();
	ThAlgorithm* pAlgorithm = ThAlgorithmFactory::getAlgorithm( (AlgorithmType)sel, histogram);
	int thvalue = pAlgorithm->CalcThreshHold();
	mSliderBar.SetPos( thvalue );

	CMainFrame* pMain=(CMainFrame*)this->GetParent()->GetParent(); 
	pMain->IUpdateBinaryImage();




}

void CPanelView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//m_cbAlgorithm.AddString("OStu");
	//m_cbAlgorithm.AddString("Entropy");
	mSliderBar.SetRange(0,255);
	mSliderBar.SetPos( 100 );

	deltaSlider.SetRange( 1 ,100 );
	deltaSlider.SetPos( 25 );


	//  创建Tooltips
	m_tooltip.Create(GetDlgItem(IDC_SLD_THR));
	m_tooltip.Activate(TRUE);
	
	
	// TODO: 在此添加专用代码和/或调用基类
}



void CPanelView::OnNMReleasedcaptureSldThr(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent(); 
	MainFrame->IUpdateBinaryImage( );

	*pResult = 0;
}

BOOL CPanelView::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT nID =pNMHDR->idFrom;
    if (pTTT->uFlags & TTF_IDISHWND)
    {
          // idFrom is actually the HWND of the tool
          nID = ::GetDlgCtrlID((HWND)nID);
          if(nID)
          {
               //  这里就是你要显示的Tooltips，可以根据需要来定制
               CString strToolTips;
               strToolTips.Format("当前域值：%d", mSliderBar.GetPos());
   
               strcpy(pTTT->lpszText, strToolTips);
               pTTT->hinst = NULL;
               return(TRUE);
           }
    }

    return(FALSE);
}

void CPanelView::OnBnClickedBtnGauss()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent(); 
	double gDelta = deltaSlider.GetPos() / 10.0 ;
	MainFrame->gaussianDelta = gDelta;
	MainFrame->OnConvolutionGaussian();
}

void CPanelView::OnBnClickedBtnEdge()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnConvolutionSobel();
}

void CPanelView::OnNMReleasedcaptureSldGdelta(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent(); 
	double gDelta = deltaSlider.GetPos() / 10.0 ;
	MainFrame->gaussianDelta = gDelta;
	MainFrame->OnConvolutionGaussian();
	*pResult = 0;
}

VOID CPanelView::OnBtnErosionClick()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyErosion();
}

VOID CPanelView::OnBtnDialationClick()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyDialation();
}
void CPanelView::OnBnClickedBtnopen()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyOpen();
}

void CPanelView::OnBnClickedBtnclose()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyClose();
}

void CPanelView::OnBnClickedBtndistance()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyDistance();
}

void CPanelView::OnBnClickedBtnskeleton()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologySkeleton();
}

void CPanelView::OnBnClickedBtnrestore()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologySkeletonRestore();
}

void CPanelView::OnBnClickedBtngradient()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyGradient();
}

void CPanelView::OnBnClickedBtnedge()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyEdgeDetection();
}

void CPanelView::OnBnClickedBtncond()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyConditionDialation();
}

void CPanelView::OnBnClickedBtngrayre()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyGrayScaleReconstruction();
}

void CPanelView::OnBnClickedBtnLdmask()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyLoadMaskFile();
}

//void CPanelView::OnBnClickedBtnMode()
//{
//	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
//	MainFrame->OnMorphologyLoadMaskFile();
//}

void CPanelView::OnBnClickedBtnCbr()
{
	CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent();
	MainFrame->OnMorphologyCBR();
}
