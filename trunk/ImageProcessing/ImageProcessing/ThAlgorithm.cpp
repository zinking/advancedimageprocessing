#include "StdAfx.h"
#include "ThAlgorithm.h"
#include "Histogram.h"


int otsu::CalcThreshHold()
{
	int thValue,k;

	int n, n1, n2, gmin, gmax;
	double m1, m2, sum, csum, fmax, sb;

	// set up everything
	sum = csum = 0.0;
	n = 0;

	for ( k = 0; k <= 255; k++) 
	{
		/*hist.getHistValue( k ); */
		sum += k * hist[k]; /* x*f(x) 质量矩*/
		n += hist[k]; /* f(x) 质量 */
	}

	// do the otsu global thresholding method
	fmax = -1.0;
	n1 = 0;
	for (k = 0; k < 255; k++) 
	{
		n1 += hist[k];
		if ( !n1 ) continue;

		n2 = n - n1;
		if (n2 == 0) break;

		csum += k *hist[k];
		m1 = csum / n1;
		m2 = (sum - csum) / n2;

		sb = n1 * n2 *(m1 - m2) * (m1 - m2);
		/* bbg: note: can be optimized. */
		if (sb > fmax)
		{
			fmax = sb;
			thValue = k;
		}
	}

	m_strInfo.Format("ThreshValue: %d",thValue);

	return thValue;
}


int entrophy::CalcThreshHold()
{
	int thValue = 0;
	float H[256] , Hb = 0.0, Hw = 0.0, pj=0.0;
	int Nb = 0, Nw = 0, N = 0;

	for (int  k = 0; k <= 255; k++) 
	{
		/*hist.getHistValue( k ); */
		N += hist[k]; /* f(x) 质量 */
	}

	//
	int t,j;
	for (  t=0;t<256;t++)
	{
		Nb = 0;
		for (  j = 0; j <= t ; j++)	Nb += hist[j];
		Nw = N - Nb;

		for (  j=0; j <= t; j++ ) 
		{
			if ( 0 == Nb ) continue;
			pj = (float)hist[j]/((float)Nb /*+ 0.000000000001*/);
			//pj += 0.0000000001;
			if ( pj <= 0 ) continue;
			Hb += -pj*log(pj);
		}
		for ( ;j<256;j++) 
		{
			if ( 0 == Nw ) continue;
			pj = (float)hist[j]/((float)Nw /*+ 0.000000000001*/);
			//pj += 0.0000000001;
			if ( pj <= 0 ) continue;
			Hw += -pj*log(pj);
		}
		H[t] = Hw + Hb;
		Hw =0.0;
		Hb  =0.0;
	}
	
	float maxH = H[0];

	for ( t=0;t<256;t++)
	{
		if ( maxH < H[t] )
		{
			maxH = H[t];
			thValue = t;
		}
	}
	m_strInfo.Format("ThreshValue: %d",thValue);

	return thValue;
}


