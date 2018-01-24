#include "typedef.h"
#include "Command.h"
#include "uart.h"
#include "string.h"
#include "Delay.h"

//================================================

static BOOLEAN CheckSum(U8 *p,U8 count)
{
    U8  cksum = 0;                                          /* checksum */
    
	if(p==NULL)
		return FALSE;
	
	while( count-- ) cksum += *p++;                   /* calculate checksum */
	
    if(cksum)
		return FALSE;
	return TRUE;
}

static void CheckSumGen(U8 *p,U8 offset)
{
    U8  cksum = 0;                                          /* checksum */
    U16  count;
	
	if(p==NULL)
        return ;
	
	count = p[offset]-1;
    while( count-- ) cksum += *p++;                   /* calculate checksum */
	
	*p = (~cksum)+1;                                            /* write checksum */
}

#define MAIN_CMD1 0x41
#define MAIN_CMD2 0x44

#define CMD_SHAKE_HANDS_OLD     0x4105
#define CMD_SET_CURRENT			0x4102//设置LED电流 set Led current
#define CMD_GET_CURRENT			0x4101//获取LED电流 get Led current
#define CMD_LED_ON_OFF			0x4118//控制LED开关 switch Led

#define CMD_SHAKE_HANDS			0x4400//用于确认串口是否连接好，投影仪是否正常工作 confirm serial port OK
#define CMD_FLIP				0x4413//图像翻转 triggle image
#define CMD_INPUT_SOURCE		0x4408//选择输入源  select source input
#define CMD_FIRMWARE_UPGRATE	0x440E//固件升级  firm update
#define CMD_LIGHT_SELECT        0x4418//光源选择  Led source select
#define CMD_VERSION             0x4417
#define CMD_TEMPERATURE         0x4405//温度  thermo

int PackageReceive(unsigned char *Buffer,unsigned char Size)
{
	unsigned char buffer[255],i;
	unsigned char Total=Size+2;
	if(GetChars((S8*)buffer,Total)==FALSE)
		return 0;

	if(CheckSum(buffer,Total))
	{
		for(i=0;i<Size;i++)
			Buffer[i]=buffer[i+1];
		return Size;
	}
	else
		return -1;
}


static int Package(U16 cmd,U8 *TransmitBuffer,U8 TransmitSize,U8 *ReceiveBuffer,U8 ReceiveSize,U16 ReceiveTryCnt)
{
	U8 buffer[1024],MainCmd,TotalSize,SubCmd;
	U16 i;

	if(TransmitBuffer==NULL && TransmitSize>0)
		return -1;

	if(ReceiveBuffer==NULL && ReceiveSize>0)
		return -1;

	MainCmd=(cmd>>8)&0xff;
	SubCmd=cmd&0xff;

	if(MainCmd==MAIN_CMD2)
		TotalSize=TransmitSize+5;
	else
		TotalSize=TransmitSize+4;

	buffer[0]=0xE0;
	buffer[1]=TotalSize;
	buffer[2]=MainCmd;
	buffer[3]=SubCmd;

    for(i=0;i<TransmitSize;i++)
		buffer[4+i]=TransmitBuffer[i];

    if(MainCmd==MAIN_CMD2)
		CheckSumGen(buffer,1);
	
	ReceiveBufferClear();
	SendChars(buffer,buffer[1]);

	if(ReceiveSize==0)
		  return 0;

	if(MainCmd==MAIN_CMD2)
		TotalSize=ReceiveSize+2;
	else
		TotalSize=ReceiveSize;

	for(i=0;i<ReceiveTryCnt;i++)
	{
		if(GetChars(buffer,TotalSize)==FALSE)
			continue;

		if(MainCmd==MAIN_CMD1)
		{
			for(i=0;i<ReceiveSize;i++)
				ReceiveBuffer[i]=buffer[i];
			return ReceiveSize;
		}
	
		if(CheckSum(buffer,TotalSize))
		{
			for(i=0;i<ReceiveSize;i++)
				ReceiveBuffer[i]=buffer[i+1];
			return ReceiveSize;
		}
		else
			return -1;
	}
	return 0;
}


Bool GetTemperature(short int *r,short int *g,short int *b,short int *board)
{
	U8 buffer[10];
	//---------------------------------------------
	buffer[0]=0x00;
	if(Package(CMD_TEMPERATURE,buffer,1,buffer,8,50))
	{
		*r=buffer[0]+(buffer[1]<<8);
		*g=buffer[2]+(buffer[3]<<8);
		*b=buffer[4]+(buffer[5]<<8);
		*board=buffer[6]+(buffer[7]<<8);
		return TRUE;
	}

	if(Package(CMD_TEMPERATURE,NULL,0,buffer,6,50))
	{
		*r=buffer[0]+(buffer[1]<<8);
		*g=buffer[2]+(buffer[3]<<8);
		*b=buffer[4]+(buffer[5]<<8);
		*board=-100;
		return TRUE;
	}
	*r=-100;
	*g=-100;
	*b=-100;
	*board=-100;
	return FALSE;
}

Bool LedOnOff(unsigned char flag)
{
    U8 buffer[6];
	
	buffer[0]=flag;

	if(Package(CMD_LED_ON_OFF,buffer,1,buffer,3,50)<=0)
		return FALSE;
	if(buffer[0]=='A' && buffer[1]=='c' && buffer[2]=='k')
				return TRUE;
	return FALSE;
}



Bool GetCurrent(U16 *Red,U16 *Green,U16 *Blue)
{
	U8 buffer[50];
	if(Package(CMD_GET_CURRENT,NULL,0,buffer,6,50)<=0)
	{
		*Red=0;
		*Green=0;
		*Blue=0;
		return FALSE;
	}
	*Red=buffer[0]+(buffer[1]<<8);
	*Green=buffer[2]+(buffer[3]<<8);
	*Blue=buffer[4]+(buffer[5]<<8);
	return TRUE;
}


Bool SetCurrent(U16 red,U16 green,U16 blue)
{
    U8 buffer[6];

	buffer[0]=red&0xff;
	buffer[1]=(red>>8)&0xff;
	buffer[2]=green&0xff;
	buffer[3]=(green>>8)&0xff;
	buffer[4]=blue&0xff;
	buffer[5]=(blue>>8)&0xff;

	if(Package(CMD_SET_CURRENT,buffer,6,buffer,3,50)<=0)
		return FALSE;
	if(buffer[0]=='A' && buffer[1]=='c' && buffer[2]=='k')
		return TRUE;
	return FALSE;
}

//==============================================================

Bool ShakeHands(void)
{
	U8 SpacCharOld[]="Mstar Connect OK";
	U8 SpacChar[]="ShakeHands";
	U8 buffer[20];
	
	if(Package(CMD_SHAKE_HANDS,SpacChar,10,buffer,10,3))
	{
		buffer[10]=0;
		if(strcmp((char*)buffer,(char*)SpacChar))
			return FALSE;
		else
			return TRUE;
	}

	if(Package(CMD_SHAKE_HANDS_OLD,SpacCharOld,16,buffer,16,3))
	{
		buffer[16]=0;
		if(strcmp((char*)buffer,(char*)SpacCharOld))
			return FALSE;
		else
			return TRUE;
	}
	return FALSE;
}

Bool Flip(unsigned char FlipX,unsigned char FlipY)
{
	U8 buffer[3];
	buffer[0]=FlipX;
	buffer[1]=FlipY;
	if(Package(CMD_FLIP,buffer,2,buffer,3,50)<=0)
		return FALSE;
	if(buffer[0]=='A' && buffer[1]=='c' && buffer[2]=='k')
		return TRUE;
	return FALSE;
}

Bool InputSource(unsigned char Value)
{
	U8 buffer[3];
	buffer[0]=Value;
	if(Package(CMD_INPUT_SOURCE,buffer,1,buffer,3,50)<=0)
		return FALSE;
	if(buffer[0]=='A' && buffer[1]=='c' && buffer[2]=='k')
		return TRUE;
	return FALSE;
}

int FirmWareUpGrate(U8 *FileName,U8 Namelength)
{
	U8 DefaultName[]="PDC01.bin";
	U8 buffer[5];

	if(Package(CMD_FIRMWARE_UPGRATE,FileName,Namelength,buffer,3,5))
	{
		if(buffer[0]=='A' && buffer[1]=='c' && buffer[2]=='k')
		return TRUE;
	}
	//-----------------------------

	if(strcmp((char*)FileName,(char*)DefaultName))
		return -1;

	//E0 03 38
	buffer[0]=0xE0;
	buffer[1]=0x03;
	buffer[2]=0x38;
	
	ReceiveBufferClear();
	SendChars(buffer,3);
	return FALSE;
}

Bool LightControl(U8 Index)
{
	U8 buffer[3];
	buffer[0]=Index;
	if(Package(CMD_LIGHT_SELECT,buffer,1,buffer,3,5)<=0)
		return FALSE;
	if(buffer[0]=='A' && buffer[1]=='c' && buffer[2]=='k')
		return TRUE;
	return FALSE;
}

Bool CheckVersion(U32 Version)// 4 byte
{
	U32 VerVal;
	U8 buffer[4];

	if(Package(CMD_VERSION,NULL,0,buffer,4,5)<=0)
		return FALSE;

	VerVal= buffer[3];
	VerVal= VerVal<<8 | buffer[2];
	VerVal= VerVal<<8 | buffer[1];
	VerVal= VerVal<<8 | buffer[0];
	
	if(VerVal<Version)
		return FALSE;
	return TRUE;
}

