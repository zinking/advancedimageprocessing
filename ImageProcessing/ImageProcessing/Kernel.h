#pragma once



class Kernel
{
public:
	Kernel( int w, int h );
	~Kernel(void);
	float getKernelValue(int x,int y )const;
	float getTransKernelValue( int x, int y ) const;//用来获得中心转置后的KERNEL值，在EROSION时用到
	void setKernelValue( const float* ptr );


public:
	inline bool AssertValid( int x, int y ) const{
		if ( x >=0 && x < width &&  y>=0 &&  y< height ) return true;
		return false;
	}

	void setCenter( int x, int y ){
		if( !AssertValid( x,y ) ) return;
		centerX = x;
		centerY = y;
	}
public:
	static Kernel getDefaultKernel();
	static Kernel getDiskKernel();
	static Kernel getDiamondKernel();
	static Kernel getR10DiskKernel();

	//int KernelSize;
private:
	float* data;
public:
	int width;
	int height;
	int centerX;
	int centerY;
};
