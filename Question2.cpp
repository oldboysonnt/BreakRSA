// HelloGMPApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <mpir.h>
#include <gmp.h>
#include <mpfr.h>
#include<math.h>

#define MODULUS "648455842808071669662824265346772278726343720706976263060439070378797308618081116462714015276061417569195587321840254520655424906719892428844841839353281972988531310511738648965962582821502504990264452100885281673303711142296421027840289307657458645233683357077834689715838646088239640236866252211790085787877"

bool isInteger(mpfr_t n) {
	bool b = false;
	mpfr_t flr,s;
	mpfr_init(flr);
	mpfr_init(s);
	mpfr_floor(flr, n);
	mpfr_sub(s, n, flr, MPFR_RNDD);
	if (mpfr_cmp_ui(s, 0) == 0)
		b = true;
	mpfr_clear(flr);
	mpfr_clear(s);
	return b;
}

int main(void)
{
	unsigned long int i = 0;
	mpfr_t N, p, q, A, x, temp,temp1, n;
	mpfr_set_default_prec(1080);
	mpfr_init(N);
	mpfr_init(p);
	mpfr_init(q);
	mpfr_init(A);
	mpfr_init(x);
	mpfr_init(n);
	mpfr_init(temp);
	mpfr_init(temp1);
	mpfr_set_str(N, MODULUS, 10, MPFR_RNDD);
	printf("   N  = ");
	mpfr_out_str(stdout, 10, 0, N, MPFR_RNDD);
	putchar('\n');
	putchar('\n');
	putchar('\n');
	mpfr_sqrt(n, N, MPFR_RNDD);
	mpfr_out_str(stdout, 10, 0, n, MPFR_RNDD);
	putchar('\n');
	mpfr_ceil(A, n);
	mpfr_out_str(stdout, 10, 0, A, MPFR_RNDD);
	putchar('\n');
	putchar('\n');
	unsigned long int j = pow(2, 20);
	printf("%d", j);
	for (i = 0; i < pow(2, 20); i++)
	{
		printf("%d  :\n", i);
		mpfr_add_ui(temp, A, i, MPFR_RNDD);
		//mpfr_out_str(stdout, 10, 0, temp, MPFR_RNDD);
		mpfr_sqr(temp, temp, MPFR_RNDD);
		putchar('\n');
		mpfr_sub(x, temp, N, MPFR_RNDD);
		mpfr_sqrt(x, x, MPFR_RNDD);
		if (isInteger(x))
			break;
	}
	    mpfr_add_ui(A, A, i, MPFR_RNDD);
		mpfr_add(p, A, x, MPFR_RNDD);
		mpfr_sub(q, A, x, MPFR_RNDD);
		mpfr_mul(temp1, p, q, MPFR_RNDD);

		printf("  ----------- ||   RESULT   || -----------\n");
		printf("   x  = ");
		mpfr_out_str(stdout, 10, 0, x, MPFR_RNDD);
		putchar('\n');
		printf("   p  = ");
		mpfr_out_str(stdout, 10, 0, p, MPFR_RNDD);
		putchar('\n');
		printf("   q  = ");
		mpfr_out_str(stdout, 10, 0, q, MPFR_RNDD);
		putchar('\n');
		printf("   p*q  = ");
		mpfr_out_str(stdout, 10, 0, temp1, MPFR_RNDD);
		putchar('\n');
		if (mpfr_cmp(temp1, N) == 0) {
			printf("    TRUE  ");
		}
		else printf("   FALSE ");
		printf("\n\n\n");
	// Free memories
	mpfr_clear(N);
	mpfr_clear(p);
	mpfr_clear(q);
	mpfr_free_cache();
	return 0;
}



