#include "GF_tables.h"
#include "GF_operations.h"
#include <stdio.h>
unsigned char f = 0x1d;


unsigned char GF_mulX(unsigned char a)
{
	return  (a << 1) ^ (f * (a >> 7));
}

unsigned char GF_mul(unsigned char a, unsigned char b)
{
	unsigned char bites[8];
	for(int i=7; i>=0; i--){
		bites[7-i] = (b&(1<<i))>>i;
	}
	unsigned char res = bites[0]*a;
	for(int i=1; i<8; i++){
		res = GF_mulX(res);
		res ^= bites[i]*a;
	}

	return res;
}

unsigned char GF_xor(unsigned char a, unsigned char b)
{
    return  a ^ b;
}

unsigned char GF_pow(unsigned char a)
{
	return GF_powT[ a ];
}
/*
unsigned char GF_pow(unsigned char a){
	unsigned char res = 1;
	for (int i = 0; i < a; i++)
		res = GF_mulX(res);
	return res;
}
*/

unsigned char GF_log(unsigned char a)
{
	return LogTable[a-1][1];
}
/*
???
*/

unsigned char GF_inv(unsigned char a)
{
	unsigned char res = InvTable[a - 1][1];
	return res;
}

/*
unsigned char GF_inv(unsigned char a){
	unsigned char res = a;
	for (int i = 0; i < 254; i++)
		res = GF_mul(res, a);
	return res;
}
*/
