#include <stdio.h>
#include "raid6.h"

void printD(unsigned char *D, int nDrives, int nSyndromes);

int main(){
    unsigned char D1[16]={0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0 ,0};
    // {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x88}
    unsigned char D2[16]={0x11, 0x22, 0x00, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff ,0x00};
    unsigned char D3[16]={0x11, 0x22, 0x00, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee ,0x00, 0x88};
    unsigned char D4[16]={0x11, 0x22, 0x00, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x00, 0xbb, 0xcc, 0xdd, 0xee ,0xff, 0x88};
    unsigned char D5[16]={0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x77, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee ,0xff, 0x88};
    int failedDriveD2[] = {2};
    int failedDriveD3[] = {2};
    int failedDriveD4[] = {2, 9};
    int failedDriveD5[1] = {0};
    int nDrives = 14;
    int nSyndromes = 2;
    printf("Data before S0S1 calculation:\n");
    printD(D1,nDrives, nSyndromes);
    Calculate_S0S1(D1, nDrives, nSyndromes);
    printf("Data after S0S1 calculation:\n");
    printD(D1,nDrives, nSyndromes);

    printf("\nData before Recovery1d_S0:\n");
    printD(D2,nDrives, nSyndromes);
    Recovery1d_S0(D2,nDrives,nSyndromes,failedDriveD2);
    printf("Data after Recovery1d_S0:\n");
    printD(D2,nDrives, nSyndromes);

    printf("\nData before Recovery1d_S1:\n");
    printD(D3,nDrives, nSyndromes);
    Recovery1d_S1(D3,nDrives,nSyndromes,failedDriveD3);
    printf("Data after Recovery1d_S1:\n");
    printD(D3,nDrives, nSyndromes);


    printf("\nData before Recovery2d_S0S1:\n");
    printD(D4,nDrives, nSyndromes);
    Recovery2d_S0S1(D4,nDrives,nSyndromes,failedDriveD4);
    printf("Data after Recovery2d_S0S1:\n");
    printD(D4,nDrives, nSyndromes);

    printf("\nData before SDC_Detection_S0S1:\n");
    printD(D4,nDrives, nSyndromes);
    if(SDC_Detection_S0S1(D4,nDrives,nSyndromes,failedDriveD5)){
        printf("Data corrupted int[%d] block\n", *failedDriveD5);
        printf("Data after SDC_Detection_S0S1:\n");
        printD(D4,nDrives, nSyndromes);
    }
    else{
        printf("No SDC found!\n");
    }

    printf("\nData before SDC_Detection_S0S1:\n");
    printD(D5,nDrives, nSyndromes);
    if(SDC_Detection_S0S1(D5,nDrives,nSyndromes,failedDriveD5)){
        printf("Data corrupted in [%d] block\n", *failedDriveD5);
        printf("Data after SDC_Detection_S0S1:\n");
        printD(D5,nDrives, nSyndromes);
    }
    else{
        printf("No SDC found:\n");
    }

    return 0;
}

void printD(unsigned char *D, int nDrives, int nSyndromes){
    printf("{");
    for(int i=0;i<nDrives+nSyndromes;i++){
        printf("0x%x", D[i]);
        if(i+1<nDrives+nSyndromes)
            printf(", ");
    }
    printf("}\n");
}
