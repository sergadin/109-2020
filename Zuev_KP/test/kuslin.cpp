#include <cstring>
#include <stdio.h>
#include "kuslin.h"

bool ZZ::doTrace = true;

void ZZ::convertIn(int val)
{
	char temp[12];
	sprintf(temp, "%d", val); 
	int len = strlen(temp); 
	if(ndigits_ == 0)
       	{
		ndigits_ = len;
	}

	data_ = new char[ndigits_]; 
	if(len > ndigits_)
       	{
	       	throw "ZZ::convertIn: len > ndigits_";
       	}

	for(int i=0; i<ndigits_; i++)
       	{
		data_[i] = (i < len ? temp[len - i - 1] : '0');
	}
}

ZZ::ZZ(int val) : data_(NULL), ndigits_(0), isPositive_(false)
{

	if(ZZ::doTrace) 
	{
		std::cout << "Constructor" << std::endl;
	}

	convertIn(val);
}


ZZ::ZZ(int val, unsigned int arrsize) : data_(NULL), isPositive_(false) 
{
	ndigits_ = arrsize;
	convertIn(val);
}


ZZ::ZZ(const ZZ& z) 
{
	delete data_;
	data_ = new char[z.ndigits_];
	memcpy(data_, z.data_, z.ndigits_);
	ndigits_ = z.ndigits_;
	isPositive_ = z.isPositive_;
}


ZZ::~ZZ()
{
	if(ZZ::doTrace) 
	{
		std::cout << "Destructor" << std::endl;
	}
	delete[] data_;
}


ZZ operator* (const ZZ& z1, const ZZ& z2) 
{
	int z1rs = z1.realSize(),
	    z2rs = z2.realSize();
	ZZ res(0, z1rs+z2rs+1);
	for(int i=0; i < z1rs; i++) 
	{
		for(int j=0; j < z2rs; j++) 
		{
			unsigned int prod = (unsigned int)(z1.data_[i]-'0')*(unsigned int)(z2.data_[j]-'0');

			for(int k=i+j; k < i+z2rs+1 && prod > 0; k++) {
				unsigned int sum = (prod % 10) + (unsigned)(res.data_[k]-'0');
				res.data_[k] = '0' + (sum % 10);
				prod = (sum/10 + prod/10);
			}
		}
	}

	res.isPositive_ = !(z1.isPositive_ ^ z2.isPositive_);
	return res;
}


ZZ& ZZ::operator= (const ZZ& z) 
{
	delete data_;
	data_ = new char[ndigits_ = z.ndigits_];
	memcpy(data_, z.data_, z.ndigits_);
	isPositive_ = z.isPositive_;
	return *this;
}

std::ostream& operator <<(std::ostream& os, const ZZ& z) 
{
	for(int i = z.realSize()-1; i>=0; i--) 
	{
		os << z.data_[i];
		//if(i>0) os << " ";
	}
	return os;
}


int ZZ::realSize() const 
{
	for(int i=ndigits_-1; i>0; --i)
		if(data_[i] != 0 && data_[i] != '0') return i+1;
	return 1;
}
