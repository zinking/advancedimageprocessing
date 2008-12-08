#pragma once

class Histogram;

class ThAlgorithm
{
public:
	ThAlgorithm(){}
	virtual ~ThAlgorithm(){}

	virtual int CalcThreshHold(){ return 100; }
	virtual CString getInfo(){ return "";}

private:
	CString m_info;
};


class otsu :public ThAlgorithm
{
public:
	otsu( Histogram& h ):hist(h){  }
	virtual ~otsu(){}

	virtual int CalcThreshHold();
	virtual CString getInfo(){ return m_strInfo;}

private:
	Histogram& hist;
	CString m_strInfo;
};

class entrophy: public ThAlgorithm
{
public:
	entrophy(Histogram& h):hist(h){}
	virtual ~entrophy(){}

	virtual int CalcThreshHold();
	virtual CString getInfo(){ return m_strInfo;}

	//void setHist( Histogram& h) { hist = h; }

private:
	Histogram& hist;
	CString m_strInfo;
};

enum AlgorithmType{ OTSU,ENTROPHY };
class ThAlgorithmFactory
{
public:
	static ThAlgorithm* getAlgorithm( AlgorithmType al ,Histogram* h)
	{
		switch ( al )
		{
		case OTSU:
			return new otsu( *h );
			break;
		case ENTROPHY:
			return new entrophy( *h );
			break;
		}
	}
};
