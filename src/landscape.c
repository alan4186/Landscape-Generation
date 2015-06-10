/*
 * landscape.h

 *
 *  Created on: May 18, 2015
 *      Author: alan
 */
#include <math.h>
#include <stdio.h>

int targetLength(int n) {
	long double rnf = 1.0;
	long double product = 1.0;
	long double diff = 1; // the difference between the current target and sqrt(n!)
	int t1 = 0; // lower target length

	// compute rnf
	for(int i=1;i<=n;i++){
		rnf*=sqrt(i);
	}

	while (diff > 0) {
		t1 += 1;
		product *= t1;
		diff = rnf - product;
	}
	printf("t1 = %d\n",t1);
	//which is closer to rnf? t1 | t2
	long double d1 = product - rnf;
	long double d2 = rnf- (product / t1);
	printf("d1=%Lf\nd2=%Lf\n",d1,d2);

	// might always be --t1
	if (product - rnf > rnf - (product / t1))
		return --t1;
	else
		return t1;
}

