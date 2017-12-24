#ifndef GF_OPERATIONS_H
#define GF_OPERATIONS_H

//#include "RDX_Engine.h"

extern unsigned char GF_mulX(unsigned char a);
extern unsigned char GF_mul(unsigned char a, unsigned char b);
extern unsigned char GF_xor(unsigned char a, unsigned char b);
extern unsigned char GF_pow(unsigned char a);
extern unsigned char GF_log(unsigned char a);

extern unsigned char GF_inv(unsigned char a);

#endif
