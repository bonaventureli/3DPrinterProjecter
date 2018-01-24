#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C" {
#endif

Bool OpenUart(unsigned char dwPort,unsigned long dwBaudRate);
Bool GetChars(S8 * buffer,U8 len);
void SendChars(U8 * buffer,U8 len);
void CloseUart(unsigned char dwPort);
void ReceiveBufferClear(void);

Bool OpenUartEx(unsigned char dwPort);
Bool GetCharsEx(S8 * buffer,U8 len);
void SendCharsEx(U8 * buffer,U8 len);
void CloseUartEx(unsigned char dwPort);
void ReceiveBufferClearEx(void);

#ifdef __cplusplus
};
#endif
#endif