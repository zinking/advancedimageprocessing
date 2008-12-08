#include "StdAfx.h"
#include "DIPClass.h"

const int Contrast = 5;//����DISTANCE��ʾʱ��ĶԱȶ�Ч��

Kernel kerl =  Kernel::getDefaultKernel();
DIPClass::DIPClass(void){}

DIPClass::~DIPClass(void){}


//PIXEL INLINE OPERATIONS------------------------------------------------------------------------------------------------------
inline uchar* PIXEL( IplImage* img, int x, int y )
{
	uchar* ptr = (uchar*) (
		img->imageData + y * img->widthStep
		);

	return &ptr[3*x];
}
inline uchar getPixel( IplImage* img, int x, int y )
{
	return PIXEL(  img,  x,  y )[0];
}

inline void setGrayPixel(  IplImage* img, int x, int y, uchar v )
{
	uchar* pixel = PIXEL(img,x,y);
	pixel[0] = v;
	pixel[1] = v;
	pixel[2] = v;
}
bool inline AssertValid( int x, int y, IplImage* img)
{
	bool validx = ( x>=0 ) && ( x < img->width );
	bool validy = ( y>=0 ) && ( y < img->height );
	return validx && validy;
}

//--------------------------------------------------------------------------------------------------------------------------------------
//������������ͼƬ�������Ҷ�����
inline void TraceImg( IplImage* img ){
	for( int y=0; y<img->height; y++ ) {
		for( int x=0; x<img->width; x++ ) {//��������ͼ��
			uchar currentPixel = getPixel( img, x,y ) ;
			TRACE("%d ",currentPixel );
		}
		TRACE("\n");
	}
}
//------------------------------------BASIC MORPHOLOGY OPERATIONS--------------------------------------------------------
int DIPClass::Erode(IplImage* src, IplImage* dst , Kernel& kernel )
{

	uchar currentgrayvalue = 0;
	for( int y=0; y<dst->height; y++ ) {
		for( int x=0; x<dst->width; x++ ) {
				uchar mingrayValue = 255;
			//��KERNEL�������
				for ( int kernelI = 0; kernelI < kernel.width; kernelI++ ){
					for ( int kernelJ = 0; kernelJ < kernel.height; kernelJ++ ){
						//��KERNEL��CENTER������ǰPIXEL�У�Ȼ���KERNEL����ʼ�㿪ʼ������
						//KERNEL�����Ӧ��ͼ������������
							int CorrespondKerPixelI = x -kernel.centerX + kernelI ;
							int CorrespondKerPixelJ = y -kernel.centerY + kernelJ ;
						//----------------------------------------------------------------------------------
							if ( !AssertValid(CorrespondKerPixelI,CorrespondKerPixelJ,src) ) continue;
							uchar currentPixelValue = getPixel( src, CorrespondKerPixelI,CorrespondKerPixelJ ) ;
						//��Ϊ��EROSION����Ҫ��KENEL�������ת�ò���
							uchar currentKernelValue =  kernel.getTransKernelValue( kernelI,kernelJ);
						//GRAYSCALE��ERIOSION���������������ô��ǰ����ֵҪ��ȥKERNEL�ϵĻҶ�ֵ
						//�����������Ȼ��Ҫ����Ϊ0
							currentgrayvalue = currentPixelValue > currentKernelValue ? 
								currentPixelValue-currentKernelValue:0;
						//���µ�ǰ�������е���С�Ҷ�ֵ
							currentgrayvalue < mingrayValue ? 
								mingrayValue = currentgrayvalue: NULL;
					}
				}
				setGrayPixel( dst,x,y,mingrayValue);
		}
	}
	return 0;
}

int DIPClass::Dialate(IplImage* src, IplImage* dst , Kernel& kernel)
{
	uchar currentgrayvalue = 0;
	for( int y=0; y<dst->height; y++ ) {
		for( int x=0; x<dst->width; x++ ) {
			uchar maxgrayValue = 0;
			//��KERNEL�������
			for ( int kernelI = 0; kernelI < kernel.width; kernelI++ ){
				for ( int kernelJ = 0; kernelJ < kernel.height; kernelJ++ ){
					//��KERNEL��CENTER������ǰPIXEL�У�Ȼ���KERNEL����ʼ�㿪ʼ������
					//KERNEL�����Ӧ��ͼ������������
					int CorrespondKerPixelI = x -kernel.centerX + kernelI ;
					int CorrespondKerPixelJ = y -kernel.centerY + kernelJ ;
					//----------------------------------------------------------------------------------
					if ( !AssertValid(CorrespondKerPixelI,CorrespondKerPixelJ,src) ) continue;
					uchar currentPixelValue = getPixel( src, CorrespondKerPixelI,CorrespondKerPixelJ ) ;
					//DIALATIONֱ�ӻ�ȡ��Ӧ��KERNEL�����ϵ�ֵ����
					uchar currentKernelValue = kernel.getKernelValue( kernelI,kernelJ);
					//��֤������ļӷ�
					currentgrayvalue = currentPixelValue + currentKernelValue < 255 ? 
						currentPixelValue+currentKernelValue: 255 ;
					//���µ�ǰ�����ε��������ֵ
					currentgrayvalue > maxgrayValue ? 
						maxgrayValue = currentgrayvalue: NULL;
				}
			}
			setGrayPixel( dst,x,y,maxgrayValue);
		}
	}
	return 0;
}



int DIPClass::Open(IplImage* src, IplImage* dst , Kernel& kernel)
{
	IplImage* tmp = cvCloneImage(src);
	Erode( src,tmp,kernel);
	Dialate( tmp,dst,kernel);
	cvReleaseImage( &tmp );
	return 0;
}

int DIPClass::Close(IplImage* src, IplImage* dst , Kernel& kernel)
{
	IplImage* tmp =  cvCloneImage(src);
	Dialate( src,tmp,kernel);
	Erode( tmp,dst,kernel);
	cvReleaseImage( &tmp );
	return 0;
}


//---------------------------------------------------------------------------------------------------------------------------------------
inline int ErodeOnce(IplImage* src, IplImage*rst,IplImage* dst, int distance,int& nonZeroPixels , Kernel& kernel)
{
	//SRC: the original image to work on ��ʴһ�ε�Դͼ��
	//RST: the eroded once image ��ʴ���ͼ��
	//DST: the final Distance image record distance info ��¼ͼ����Ϣ��ͼ��
	nonZeroPixels = 0;

	uchar currentgrayvalue = 0;
	for( int y=0; y<dst->height; y++ ) {
		for( int x=0; x<dst->width; x++ ) {//��������ͼ��
			uchar mingrayValue = 255;
			uchar originalValue = getPixel( src, x,y ) ;
			//��KERNEL�������
			if ( originalValue != 0 ){//�����ǰ�ĻҶ�Ϊ0�����ͱ�ERODEΪ0

				for ( int kernelI = 0; kernelI < kernel.width; kernelI++ ){
					for ( int kernelJ = 0; kernelJ < kernel.height; kernelJ++ ){//��������KERNEL

						//��KERNEL��CENTER������ǰPIXEL�У�Ȼ���KERNEL����ʼ�㿪ʼ������
						//KERNEL�����Ӧ��ͼ������������
						int CorrespondKerPixelI = x -kernel.centerX + kernelI ;
						int CorrespondKerPixelJ = y -kernel.centerY + kernelJ ;
						//----------------------------------------------------------------------------------
						if ( !AssertValid(CorrespondKerPixelI,CorrespondKerPixelJ,src) ) continue;
						uchar currentPixelValue = getPixel( src, CorrespondKerPixelI,CorrespondKerPixelJ ) ;
						uchar currentKernelValue =  kernel.getTransKernelValue( kernelI,kernelJ);
						//GRAYSCALE��ERIOSION���������������ô��ǰ����ֵҪ��ȥKERNEL�ϵĻҶ�ֵ
						//�����������Ȼ��Ҫ����Ϊ0
						currentgrayvalue = currentPixelValue > currentKernelValue ? 
							currentPixelValue-currentKernelValue:0;
						//���µ�ǰ�������е���С�Ҷ�ֵ
						currentgrayvalue < mingrayValue ? 
							mingrayValue = currentgrayvalue: NULL;
					}
				}//FOR LOOP
			}//if LOOP
			else{
				mingrayValue = 0;
			}
			

			setGrayPixel( rst ,x,y,mingrayValue);
			mingrayValue != 0 ?  nonZeroPixels++:NULL;
			if ( originalValue != 0 && mingrayValue == 0 ){//���ԭ������0���Ǳ�ERODE������ô�ͽ���ֵ��ΪI
				setGrayPixel( dst ,x,y,distance*Contrast);
			}
		}
	}
	return 0;
}
int DIPClass::Distance(IplImage* src, IplImage* dst , Kernel& kernel)
{
	IplImage* ErodeSRC = cvCloneImage(src);
	IplImage* ErodeRST = cvCloneImage(src);

	IplImage* tmp;//����ָ�룬����ÿ�εĸ�ʴ��������´εĸ�ʴ

	int UnErodedPixelCount = 0;
	for  ( int i=1; ;i++){
		ErodeOnce(ErodeSRC,ErodeRST,dst,i,UnErodedPixelCount,kernel );
		if ( UnErodedPixelCount == 0 ) break;
		tmp = ErodeSRC;
		ErodeSRC = ErodeRST;
		ErodeRST = tmp;
	}

	cvReleaseImage(&ErodeSRC);
	cvReleaseImage(&ErodeRST);

	return 0;
}

inline bool isMaxPixel( IplImage* img,int x, int y, uchar currentPixel,Kernel& kernel ){
	for ( int kernelI = 0; kernelI < kernel.width ; kernelI++ ){
		for ( int kernelJ = 0; kernelJ < kernel.height ; kernelJ++ ){//��������KERNEL

			if ( kernelI == kernel.centerX && kernelJ == kernel.centerY ) continue;
			//��KERNEL��CENTER������ǰPIXEL�У�Ȼ���KERNEL����ʼ�㿪ʼ������
			//KERNEL�����Ӧ��ͼ������������
			int CorrespondKerPixelI = x -kernel.centerX + kernelI ;
			int CorrespondKerPixelJ = y -kernel.centerY + kernelJ ;
			//----------------------------------------------------------------------------------
			if ( !AssertValid(CorrespondKerPixelI,CorrespondKerPixelJ,img) ) continue;
			uchar currentKernelPixelValue = getPixel( img, CorrespondKerPixelI,CorrespondKerPixelJ ) ;
			if ( currentKernelPixelValue > currentPixel ) return false;
		}
	}

	return true;
}

inline int SkeletonSubset( ){//TODO������ʹ�ù�ʽ����
	return 0;
}

int DIPClass::Skeleton(IplImage* src, IplImage* dst ,Kernel& kernel)
{

	IplImage* distanceResult = distanceResult = cvCloneImage(src);
	
	this->Distance( src,distanceResult,kernel);
	//--------------------------------------------------------------------------------------
	for( int y=0; y<dst->height; y++ ) {
		for( int x=0; x<dst->width; x++ ) {//��������ͼ��
			uchar currentPixel = getPixel( distanceResult, x,y ) ;
			if ( currentPixel == 0  ) continue;
			if ( !isMaxPixel(distanceResult,x,y,currentPixel,kernel) ) setGrayPixel( dst,x,y,0);
			else setGrayPixel( dst,x,y, currentPixel );
		}
	}

		cvReleaseImage(&distanceResult);
	return 0;
}

//�Ե�ǰ����Ϊ���������Χ�뾶�����ڵ�����Ϊ��ɫ
inline int fillNeighborArea( IplImage* img, int x, int y ,int radius  ){
	int startX = x - radius ;
	int startY = y - radius ;
	for ( int i = startX; i < startX + 2*radius+1; i++ ){
		for ( int j = startY; j < startY + 2*radius+1; j++ ){
				if ( !AssertValid( i,j,img) ) continue;
				setGrayPixel(img,i,j,255);
		}
	}

	return 0;
}


int DIPClass::SkeletonRestore( IplImage* skeleton, IplImage* dst ){
	if ( skeleton == NULL ) return 0;//SKELETON ͼ�񲻵�Ϊ��
	//TraceImg( skeleton );

	for( int y=0; y<dst->height; y++ ) {
		for( int x=0; x<dst->width; x++ ) {//��������ͼ��
			uchar currentPixel = getPixel( skeleton, x,y ) ;
			if ( currentPixel == 0  ) {
				uchar dstPixel = getPixel( dst, x,y ) ;
				if ( dstPixel == 0 ) setGrayPixel(dst,x , y,0);
				continue;
			}
			int radius = currentPixel/Contrast -1;
			fillNeighborArea( dst,x ,y ,radius);
		}
	}

	return 0;
}



//A,B, Result ������ͬ����ͼ�������CLONE��
int DIPClass::Subtract( IplImage* A, IplImage* B, IplImage* result ){
	for( int y=0; y<A->height; y++ ) {
		for( int x=0; x<A->width; x++ ) {//��������ͼ��
			uchar PixelA = getPixel( A, x,y ) ;
			uchar PixelB = getPixel( B, x,y ) ;
			if ( PixelA >= PixelB ) setGrayPixel( result,x,y, PixelA-PixelB );
			else setGrayPixel( result,x,y, 0 );
		}
	}
	return 0;
}

//A,B������ͬ��ͼ�񣬲����Ƕ�ֵͼ�񣬴˲�����������
int DIPClass::Reverse(IplImage*src, IplImage* dst){
	for( int y=0; y<src->height; y++ ) {
		for( int x=0; x<src->width; x++ ) {
			uchar Pixel = getPixel( src, x,y ) ;
			setGrayPixel( dst,x,y, 255-Pixel );
		}
	}
	return 0;
}

int DIPClass::And( IplImage*marker, IplImage* mask, IplImage* result){
	int ShileldedPixelCount = 0;
	static int lastShieldCount = 0;
	for( int y=0; y<marker->height; y++ ) {
		for( int x=0; x<marker->width; x++ ) {
			uchar markerPixel = getPixel( marker, x,y ) ;
			uchar maskPixel = getPixel( mask,x,y );
			if (  maskPixel == 0 ){
				setGrayPixel( result,x,y, 0 );
				setGrayPixel( marker,x,y, 0 );
			} 
			else if ( maskPixel == 255 ){
				setGrayPixel( result,x,y, 255 );
				setGrayPixel( marker,x,y, 255 );
				ShileldedPixelCount++;
			}
			
		}
	}
	if ( lastShieldCount == ShileldedPixelCount ) 
		return 0;//��ʾAND������ٱ仯
	lastShieldCount = ShileldedPixelCount;
	return 1;
}

int DIPClass::GrayScaleAnd( IplImage*marker, IplImage* mask, IplImage* result){
	int ShileldedPixelCount = 0;
	static int lastShieldCount = 0;
	for( int y=0; y<marker->height; y++ ) {
		for( int x=0; x<marker->width; x++ ) {
			uchar markerPixel = getPixel( marker, x,y ) ;
			uchar maskPixel = getPixel( mask,x,y );

			if ( markerPixel > maskPixel ){
				setGrayPixel( result,x,y, maskPixel );
				setGrayPixel( marker,x,y, maskPixel );
				//���Ŀ��ĻҶ�ֵ������MASK�ϵ����أ�
				ShileldedPixelCount++;
			}
			else{
				setGrayPixel( result,x,y,markerPixel);
				setGrayPixel( marker,x,y, markerPixel );
			}

		}
	}
	if ( lastShieldCount == ShileldedPixelCount ) 
		return 0;//��ʾAND������ٱ仯
	lastShieldCount = ShileldedPixelCount;
	return 1;
}

int DIPClass::MulConstant( IplImage*src, IplImage* dst, float k  ){
	for( int y=0; y<src->height; y++ ) {
		for( int x=0; x<src->width; x++ ) {
			uchar Pixel = getPixel( src, x,y ) ;
			uchar rPixel = (uchar)( (float)Pixel*k );
			setGrayPixel( dst,x,y, rPixel );
		}
	}

	return 0;
}

int DIPClass::Gradient(IplImage*src, IplImage* dst, GradientType type  ){
	IplImage* subtractResult =  cvCloneImage(src);
	IplImage* dialationResult;
	IplImage* erosionResult;
	switch (type)
	{
	case STANDARD:
		dialationResult =  cvCloneImage(src);
		erosionResult =  cvCloneImage(src);
		this->Dialate( src,dialationResult );
		this->Erode( src,erosionResult );
		this->Subtract( dialationResult,erosionResult,subtractResult );
		this->MulConstant( subtractResult,dst,0.5 );
		
		cvReleaseImage(  &dialationResult );
		cvReleaseImage(  &erosionResult );
		return 0;
		break;

	case ETERNAL:
		dialationResult =  cvCloneImage(src);
		this->Dialate( src,dialationResult );
		this->Subtract( dialationResult,src,subtractResult );
		this->MulConstant( subtractResult,dst,0.5 );

		cvReleaseImage(  &dialationResult );
		return 0;
		break;

	case INTERNAL:
		erosionResult =  cvCloneImage(src);
		this->Erode( src,erosionResult );
		this->Subtract( src,erosionResult,subtractResult );
		this->MulConstant( subtractResult,dst,0.5 );

		cvReleaseImage(  &erosionResult );
		return 0;
		break;

	}

	cvReleaseImage(&subtractResult);

	return 0;
}

int DIPClass::EdgeDetection(IplImage*src, IplImage* dst, GradientType type  ){

	IplImage* dialationResult;
	IplImage* erosionResult;

	switch (type)
	{
	case STANDARD:
		dialationResult =  cvCloneImage(src);
		erosionResult =  cvCloneImage(src);
		this->Dialate( src,dialationResult );
		this->Erode( src,erosionResult );
		this->Subtract( dialationResult,erosionResult,dst );

		cvReleaseImage(  &dialationResult );
		cvReleaseImage(  &erosionResult );
		return 0;
		break;

	case ETERNAL:
		dialationResult =  cvCloneImage(src);
		this->Dialate( src,dialationResult );
		this->Subtract( dialationResult,src,dst );

		cvReleaseImage(  &dialationResult );
		return 0;
		break;

	case INTERNAL:
		erosionResult =  cvCloneImage(src);
		this->Erode( src,erosionResult );
		this->Subtract( src,erosionResult,dst );

		cvReleaseImage(  &erosionResult );
		return 0;
		break;
	}



	return 0;
}


int DIPClass::ConditionalDialation(  IplImage*marker, IplImage* mask,Kernel& kernel ){
	//MARKER�����ͼ��
	//MASK����ͼ��
	IplImage* dialateResult = cvCloneImage( marker );
	IplImage* iPointer;
	Kernel k(7,7);
	this->Erode( marker,dialateResult  );

	while (  And(dialateResult,mask,marker) !=0 ){
		iPointer = marker;
		marker = dialateResult;
		dialateResult = iPointer;
		this->Erode( marker,dialateResult );
	}

	//cvReleaseImage( &dialateResult );
	return 0;
}

int DIPClass::GrayScaleRestoration( IplImage*marker, IplImage* mask, Kernel& kernel  ){
	IplImage* dialateResult = cvCloneImage( marker );
	IplImage* iPointer;
	//Kernel k(7,7);
	this->Dialate( marker,dialateResult ,kernel );
//#define  DEBUGIMG 1

#ifdef DEBUGIMG
	TraceImg( dialateResult );
	TRACE("begin TRACING ----------\n");
#endif

	while (  GrayScaleAnd(dialateResult,mask,marker) !=0 ){
		iPointer = marker;
		marker = dialateResult;
		dialateResult = iPointer;

#ifdef DEBUGIMG
		TRACE("TRACING DIALETED RESULT IMG \n");
		TraceImg( dialateResult );
		TRACE("TRACING MASK IMG \n");
		TraceImg( mask );
		TRACE("TRACING MARKER IMG \n");
		TraceImg( marker );
#endif

		this->Dialate( marker,dialateResult,kernel );
	}

#ifdef DEBUGIMG
	TRACE("---------------------------------------------------------\n");
	TRACE("TRACING MARKER IMG \n");
	TraceImg( marker );
	TRACE("TRACING DIA-RESULT IMG \n");
	TraceImg( dialateResult );
	TRACE("TRACING MASK IMG \n");
	TraceImg( mask );
#endif
	//cvReleaseImage( &dialateResult );

	return 0;
}
