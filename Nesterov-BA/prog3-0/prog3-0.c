#include <stdlib.h>
#include "prog3-0.h"


int fold(fpointer f,  double *x, int n, int m){
    	int foutput, i;
	foutput = n;
	for(i=0;i<m;++i){
		foutput = (*f)(foutput, x[i]);
	}
	return foutput;
}
