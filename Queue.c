#include "typedef.h"
#include "Queue.h"
/* ------------------------------------------------------------------------- */
/*
void InitRingBuffer(RingBuffer_t *rb)
{
	rb->readIndex=0;
	rb->writeIndex=0;
}
*/

void  RingBufferWrite(RingBuffer_t *rb, U8 c)
{
	U32   newWriteIndex = rb->writeIndex + 1;
	
    if(newWriteIndex >= RING_BUFFER_SIZE)
        newWriteIndex = 0;
    if(newWriteIndex != rb->readIndex){ /* not yet full */
        rb->buffer[rb->writeIndex] = c;
        rb->writeIndex = newWriteIndex;
    }
}

U8 RingBufferHasData(RingBuffer_t *rb)
{
    return rb->readIndex != rb->writeIndex;
}

U32 RingBufferCount(RingBuffer_t *rb)
{
	S32   x = rb->writeIndex - rb->readIndex;
	
    if(rb->writeIndex >= rb->readIndex)
        return x;
    return (x + RING_BUFFER_SIZE);
}

U8 RingBufferRead(RingBuffer_t *rb)
{
    U8 c = rb->buffer[rb->readIndex];
    rb->readIndex++;
    if(rb->readIndex >= RING_BUFFER_SIZE)
        rb->readIndex = 0;
    return c;
}

void RingBufferClear(RingBuffer_t *rb)
{
	rb->readIndex=0;
	rb->writeIndex=0;
}