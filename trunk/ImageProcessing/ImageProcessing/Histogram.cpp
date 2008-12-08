#include "StdAfx.h"
#include "Histogram.h"

void Histogram::IUpdate( IplImage* pimage )
{
	if ( pimage == NULL ) return;
	this->image = pimage;

	int bins = 256;
	int hsize[] = {bins};
	float xranges[] = { 0, 256 };
	float* ranges[] = { xranges };
	IplImage* planes[] = { image };

	//get the histogram and some info about it
	hist = cvCreateHist( 1, hsize, CV_HIST_ARRAY, ranges,1);
	cvCalcHist( planes, hist, 0, NULL);
	cvGetMinMaxHistValue( hist, &min_Value, &max_Value,&min_index,&max_index);

}

float Histogram::getHistValue( int index )
{
	if ( image == NULL ) return -1.0f;
	return cvQueryHistValue_1D( hist, index);
}

int Histogram::operator [](int index)
{
	return getHistValue( index );
}
