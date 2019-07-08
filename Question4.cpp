// HelloGMPApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <mpir.h>
#include <gmp.h>
#include <mpfr.h>
#include<iostream>

#define MODULUS    "179769313486231590772930519078902473361797697894230657273430081157732675805505620686985379449212982959585501387537164015710139858647833778606925583497541085196591615128057575940752635007475935288710823649949940771895617054361149474865046711015101563940680527540071584560878577663743040086340742855278549092581"
#define CIPHERTEXT  "22096451867410381776306561134883418017410069787892831071731839143676135600120538004282329650473509424343946219751512256465839967942889460764542040581564748988013734864120452325229320176487916666402997509188729971690526083222067771600019329260870009579993724077458967773697817571267229951148662959627934791540"

void computeDecryptExponent(mpfr_t& d, mpfr_t e, mpfr_t pN) {
	mpfr_t xa,xm,xr,q,r,a,m;
	mpfr_init(xa);
	mpfr_init(xm);
	mpfr_init(xr);
	mpfr_init(q);
	mpfr_init(r);
	mpfr_init(a);
	mpfr_init(m);
	mpfr_set(a, e, MPFR_RNDD);
	mpfr_set(m, pN, MPFR_RNDD);
	mpfr_set_ui(xa, 1, MPFR_RNDD);
	mpfr_set_ui(xm, 0, MPFR_RNDD);
	while (mpfr_cmp_ui(m, 0) != 0) 
	{
		mpfr_div(q, a, m, MPFR_RNDD);
		mpfr_floor(q, q);
		mpfr_mul(q, q, xm, MPFR_RNDD);
		mpfr_sub(xr, xa, q, MPFR_RNDD);
		mpfr_set(xa, xm, MPFR_RNDD);
		mpfr_set(xm, xr, MPFR_RNDD);
		mpfr_fmod(r, a, m, MPFR_RNDD);
		mpfr_set(a, m, MPFR_RNDD);
		mpfr_set(m, r, MPFR_RNDD);
	}
	mpfr_set(d, xa, MPFR_RNDD);
}

unsigned char convert(char x) {
	if (x >= '0' && x <= '9')
		return x - 48;
	if (x >= 'a' && x <= 'f')
		return x - 87;
}
unsigned char convert10(char a, char b) {
	return convert(a) * 16 + convert(b);
}

void pow(mpfr_t x, mpfr_t n, mpfr_t m, mpfr_t& res) {
	mpfr_t power,t,t1,t2,t4;
	mpfr_init(t); mpfr_set_ui(t, 1, MPFR_RNDD);
	mpfr_init(power); mpfr_set(power, x, MPFR_RNDD);
	mpfr_init(t1); mpfr_set_ui(t1, 2, MPFR_RNDD);
	mpfr_init(t2); mpfr_init(t4);
	while (1) {
		mpfr_set(t4, power, MPFR_RNDD);
		mpfr_sqr(power, power, MPFR_RNDD);
		mpfr_fmod(power, power, m, MPFR_RNDD);
		mpfr_fmod(t2, n, t1, MPFR_RNDD);
		if (mpfr_cmp_ui(t2, 1) == 0) {
			mpfr_mul(t, t, t4, MPFR_RNDD);
			mpfr_fmod(t, t, m, MPFR_RNDD);
		}
		mpfr_div_ui(n, n, 2, MPFR_RNDD);
		mpfr_floor(n, n);
		if (mpfr_cmp_ui(n, 1) == 0) 
			break;
	}
	mpfr_mul(res, power, t, MPFR_RNDD);
	mpfr_fmod(res, res, m, MPFR_RNDD);
}

int main(void)
{
	char* plaintext;
	plaintext = new char[3000];
	memset(plaintext, 0, 3000);
	mpfr_exp_t exp;
	mpfr_t N, p, q, A, x, temp,temp2,e,d,CP,PT,d1;
	mpfr_set_default_prec(2500);
	mpfr_init(N);
	mpfr_init(p);
	mpfr_init(q);
	mpfr_init(A);
	mpfr_init(x);
	mpfr_init(e);
	mpfr_init(d);
	mpfr_init(CP);
	mpfr_init(PT);
	mpfr_init(d1);
	mpfr_set_str(N, MODULUS, 10, MPFR_RNDD);
	mpfr_set_str(CP, CIPHERTEXT, 10, MPFR_RNDD);
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
	mpfr_init(temp2);
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
		printf("    TRUE \n ");
	else printf("   FALSE\n ");

	// find d to decryption 

	// compute (p-1)*(q-1)
	mpfr_set_ui(e, 65537, MPFR_RNDD);
	mpfr_sub_ui(temp, p, 1, MPFR_RNDD);
	mpfr_sub_ui(temp2, q, 1, MPFR_RNDD);
	mpfr_mul(temp, temp, temp2, MPFR_RNDD);
	// compute Decryption Exponent
	computeDecryptExponent(d, e, temp);
	printf("The decrypting exponent   d = ");
	mpfr_out_str(stdout, 10, 0, d, MPFR_RNDD);
	putchar('\n');
	putchar('\n');
	pow(CP, d, N, PT);
	mpfr_out_str(stdout, 16, 0, PT, MPFR_RNDD);
	putchar('\n');
	mpfr_get_str(plaintext,&exp , 16, 0, PT, MPFR_RNDD);
	plaintext[exp] = 0;
	std::cout<<  plaintext << std::endl;
	
	int i,j=0;
	char* pt,*pt2;
	pt = new char[3000];
	pt2 = new char[3000];
	memset(pt2, 0, 3000);
	memset(pt, 0, 3000);
	for (i = 0; i < exp; i++)
		if (plaintext[i] == '0' && plaintext[i + 1] == '0')
		{
			strcpy(pt, &plaintext[i + 2]);
			break;
		}
	for (i = 0; i < strlen(pt); i += 2)
		pt2[j++] = convert10(pt[i], pt[i + 1]);
	printf("--------------------The plaintext : %s--------------------------------------",pt2);

	putchar('\n');
	mpfr_clear(N);
	mpfr_clear(p);
	mpfr_clear(q);
	mpfr_free_cache();
	return 0;
}


