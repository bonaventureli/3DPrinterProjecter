
#ifndef  __QUEUE_H__
#define  __QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ------------------- simple ring buffer implementation ------------------- */
/* ------------------------------------------------------------------------- */

#define RING_BUFFER_SIZE  512

typedef struct tagRingBuffer{
    U32   readIndex;
    U32   writeIndex;
    U8   buffer[RING_BUFFER_SIZE];
}RingBuffer_t;

extern RingBuffer_t KeyRingBuffer;
//extern RingBuffer_t UartRingBuffer;

void  RingBufferWrite(RingBuffer_t *rb, U8 c);
U8 RingBufferHasData(RingBuffer_t *rb);
U32 RingBufferCount(RingBuffer_t *rb);
U8 RingBufferRead(RingBuffer_t *rb);
void RingBufferClear(RingBuffer_t *rb);

#ifdef __cplusplus
};
#endif

#endif