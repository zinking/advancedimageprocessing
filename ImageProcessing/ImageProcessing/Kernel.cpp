#include "StdAfx.h"
#include "Kernel.h"

Kernel::Kernel( int w, int h )
{
	this->width = w;
	this->height = h;
	this->data = new float[ w*h];
	memset( data,0,w*h*4 );

	centerX = w/2 ;
	centerY = h/2 ;
}

float Kernel::getKernelValue(int x,int y )const{
	//return data[ x*width + y ];
	return data[ y*width + x ];
}
float Kernel::getTransKernelValue( int x, int y ) const{

	int II = 2* centerX - x;
	int JJ = 2* centerY - y;
	if ( !AssertValid( II,JJ ) ) return 0;//如果在转置的时候出错，那么返回一个默认值
	//return data[ II*width + JJ ];
	return data[ JJ*width + II ];
}

void Kernel::setKernelValue( const float* ptr ){
	//必须保证传过来的数组不能越界
	memcpy( data,ptr, width*height*4 );
}

Kernel::~Kernel(void){
	if ( this->data != NULL ) delete data;
}

 Kernel Kernel::getDefaultKernel(){
	Kernel* ker = new Kernel(3,3);
	return *ker;
}
 Kernel Kernel::getDiskKernel(){
	Kernel* ker = new Kernel( 5 , 5 );
	float kData[] = 
	{ 
		0,1,1,1,0,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		0,1,1,1,0
	};
	ker->setKernelValue( kData );
	return *ker;

}

 Kernel Kernel::getR10DiskKernel(){
	 Kernel* ker = new Kernel( 10 , 10 );
	 float kData[] = 
	 { 
		 0,0,0,0,1,1,0,0,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,1,1,1,1,1,1,0,0,
		 0,0,0,1,1,1,1,0,0,0,
		 0,0,0,0,1,1,0,0,0,0
	 };
	 ker->setKernelValue( kData );
	 return *ker;

 }
 Kernel Kernel::getDiamondKernel(){
	Kernel* ker = new Kernel( 5 , 5 );
	float kData[] = 
	{ 
		0,0,1,0,0,
		0,0,1,0,0,
		1,1,1,1,1,
		0,0,1,0,0,
		0,0,1,0,0
	};
	ker->setKernelValue( kData );
	return *ker;

}
