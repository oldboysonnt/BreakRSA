// HelloGMPApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <mpir.h>
#include <gmp.h>
#include <mpfr.h>

#define MODULUS "179769313486231590772930519078902473361797697894230657273430081157732675805505620686985379449212982959585501387537164015710139858647833778606925583497541085196591615128057575940752635007475935288710823649949940771895617054361149474865046711015101563940680527540071584560878577663743040086340742855278549092581"

int main(void)
{
	mpfr_t N, p, q, A, x, temp;
	mpfr_set_default_prec(1030);
	mpfr_init(N);
	mpfr_init(p);
	mpfr_init(q);
	mpfr_init(A);
	mpfr_init(x);
	mpfr_set_str(N, MODULUS, 10, MPFR_RNDD);
	printf("   N  = ");
	mpfr_out_str(stdout, 10, 0, N, MPFR_RNDD);
	putchar('\n');
	putchar('\n');
	putchar('\n');
	mpfr_sqrt(A, N, MPFR_RNDU);
	//putchar('\n');
	mpfr_ceil(A, A);
	//mpfr_out_str(stdout, 10, 0, A, MPFR_RNDD);
	putchar('\n');
	mpfr_init(temp);
	
	mpfr_sqr(temp, A, MPFR_RNDD);
	//mpfr_out_str(stdout, 10, 0, temp, MPFR_RNDD);
	putchar('\n');
	mpfr_sub(x, temp, N, MPFR_RNDD); 
	mpfr_sqrt(x, x, MPFR_RNDD);
	mpfr_add(p, A, x, MPFR_RNDD);
	mpfr_sub(q, A, x, MPFR_RNDD);
	mpfr_mul(temp, p, q, MPFR_RNDD);

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
	mpfr_out_str(stdout, 10, 0, temp, MPFR_RNDD);
	putchar('\n');
	if (mpfr_cmp(temp, N) == 0)
		printf("    TRUE  ");
	else printf("   FALSE ");
	// Free memories
	mpfr_clear(N);
	mpfr_clear(p);
	mpfr_clear(q);
	mpfr_free_cache();
	return 0;
}



