#include "GF_operations.h"
#include <stdio.h>

int Calculate_S0S1(unsigned char *D, int nDrives, int nSyndromes){
    int xorSyndromIndex = nDrives;
    int gfSyndromIndex = xorSyndromIndex+1;
    D[xorSyndromIndex] = 0;
    D[gfSyndromIndex] = 0;

    for(int i=0;i<nDrives;i++){
        D[xorSyndromIndex]^=D[i];

        D[gfSyndromIndex] = GF_mulX(D[gfSyndromIndex]);
        D[gfSyndromIndex]^= D[i];
    }

    return 0;
}


int Recovery1d_S0(unsigned char *D, int nDrives, int nSyndromes, int *Failed){
    int xorSyndromIndex = nDrives;
    unsigned char xor = D[xorSyndromIndex];
    D[*Failed] = 0;
    for(int i=0; i<nDrives;i++)
        xor^=D[i];
    D[*Failed] = xor;

    return 0;
}


int Recovery1d_S1(unsigned char *D, int nDrives, int nSyndromes, int *Failed){
    int xorSyndromIndex = nDrives;
    int gfSyndromIndex = xorSyndromIndex+1;
    unsigned char S1 = D[gfSyndromIndex];
    D[*Failed] = 0;
    unsigned char gf = 0;
    for(int i=0;i<nDrives;i++){
        gf = GF_mulX(gf);
        gf^= D[i];
    }
    unsigned char res = S1 ^ gf;
    res = GF_mul(res, GF_inv(GF_pow(nDrives - *Failed - 1)));
    D[*Failed]  = res;

    return 0;

}


int Recovery2d_S0S1(unsigned char *D, int nDrives, int nSyndromes, int *Failed){
    int xorSyndromIndex = nDrives;
    int gfSyndromIndex = xorSyndromIndex+1;
    unsigned char S0_old = D[xorSyndromIndex];
    unsigned char S1_old = D[gfSyndromIndex];
    int j = *Failed;
    int k = *(Failed+1);
    D[j] = 0;
    D[k] = 0;

    unsigned char S0_new = 0;
    unsigned char S1_new = 0;

    for(int i=0;i<nDrives;i++){
        S0_new^=D[i];
        S1_new = GF_mulX(S1_new);
        S1_new^= D[i];
    }

    D[j] = GF_mul((GF_mul(S1_old ^ S1_new, GF_inv(GF_pow(nDrives - k - 1))) ^ S0_old ^ S0_new), GF_inv(GF_pow(k - j) ^ 1));
	D[k] = S0_old ^ S0_new ^ D[j];

    return 0;
}


int SDC_Detection_S0S1(unsigned char *D, int nDrives, int nSyndromes, int *Failed){
    int xorSyndromIndex = nDrives;
    int gfSyndromIndex = xorSyndromIndex+1;
    unsigned char S0_old = D[xorSyndromIndex];
    unsigned char S1_old = D[gfSyndromIndex];
    unsigned char S0_new = 0;
    unsigned char S1_new = 0;
    for(int i=0;i<nDrives;i++){
        S0_new^=D[i];
        S1_new = GF_mulX(S1_new);
        S1_new^= D[i];
    }
    if(S0_old == S0_new && S1_old == S1_new)
        return 0;

    unsigned char j = nDrives - 1 - GF_log(GF_mul((S1_old ^ S1_new),GF_inv(S0_old ^ S0_new)));
    D[j] = S0_old ^ S0_new ^ D[j];
    if(Failed)
        *Failed = j;
    return 1;
}
