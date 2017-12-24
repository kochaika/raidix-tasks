#ifndef RAID6_H
#define RAID6_H

int Calculate_S0S1(unsigned char *D, int nDrives, int nSyndromes);

int Recovery1d_S0(unsigned char *D, int nDrives, int nSyndromes, int *Failed);

int Recovery1d_S1(unsigned char *D, int nDrives, int nSyndromes, int *Failed);

int Recovery2d_S0S1(unsigned char *D, int nDrives, int nSyndromes, int *Failed);

int SDC_Detection_S0S1(unsigned char *D, int nDrives, int nSyndromes, int *Failed);

#endif
