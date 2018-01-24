#ifndef __COMMAND_H__
#define __COMMAND_H__

#ifdef __cplusplus
extern "C" {
#endif


Bool GetCurrent(U16 *Red,U16 *Green,U16 *Blue);
Bool ShakeHands(void);

Bool SetCurrent(U16 red,U16 green,U16 blue);
Bool LedOnOff(unsigned char flag);

int FirmWareUpGrate(U8 *FileName,U8 Namelength);
Bool GetTemperature(short int *r,short int *g,short int *b,short int *board);
Bool CheckVersion(U32 Version);
Bool Flip(unsigned char FlipX,unsigned char FlipY);
Bool InputSource(unsigned char Value);
Bool LightControl(U8 Index);
int PackageReceive(unsigned char *Buffer,unsigned char Size);

#ifdef __cplusplus
};
#endif


#endif