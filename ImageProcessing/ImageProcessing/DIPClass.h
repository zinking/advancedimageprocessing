#pragma once
#include "highgui.h"
#include "Kernel.h"



enum GradientType{ STANDARD,ETERNAL,INTERNAL};
extern Kernel kerl; 
class DIPClass
{
public:
	DIPClass(void);
	~DIPClass(void);

	int Erode(IplImage* src, IplImage* dst, Kernel& kernel = kerl);
	int Dialate(IplImage* src, IplImage* dst , Kernel& kernel = kerl);
	int Open(IplImage* src, IplImage* dst , Kernel& kernel = kerl);
	int Close(IplImage* src, IplImage* dst , Kernel& kernel = kerl);

	int Distance(IplImage* src, IplImage* dst , Kernel& kernel = kerl);
	int Skeleton(IplImage* src, IplImage* dst, Kernel& kernel = kerl );
	int SkeletonRestore( IplImage* skeleton, IplImage* dst );

	//Mathematical Operations
	int Subtract( IplImage* A, IplImage* B, IplImage* result );
	int Reverse(IplImage*src, IplImage* dst);
	int MulConstant( IplImage*src, IplImage* dst, float k = 1 );
	int And( IplImage*marker, IplImage* mask, IplImage* result);
	int GrayScaleAnd( IplImage*marker, IplImage* mask, IplImage* result);


	int Gradient(IplImage*src, IplImage* dst, GradientType type = STANDARD );
	int EdgeDetection( IplImage*src, IplImage* dst, GradientType type = STANDARD );

	int ConditionalDialation(  IplImage*marker, IplImage* mask, Kernel& kernel = kerl );
	int GrayScaleRestoration( IplImage*marker, IplImage* mask, Kernel& kernel = kerl  );
};

inline void TraceImg( IplImage* img );
