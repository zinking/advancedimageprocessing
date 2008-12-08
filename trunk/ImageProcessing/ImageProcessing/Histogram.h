#pragma once
#include "cv.h"
#include "cvaux.h"
#include "highgui.h"

class Histogram
{
public:
	Histogram( /*IplImage* pimage =NULL*/){}
	~Histogram(){}
	void IUpdate(IplImage* pimage = NULL);
	float getHistValue( int index );

	int operator[]( int index );


public:
	CvHistogram* hist;
	IplImage* image;
	float min_Value;
	float max_Value;
	int min_index;
	int max_index;

};
