#include "ring-buffer.h"



Error RingBuffer_Initialize(RingBuffer *buffer, 
                            uint16_t bufferSize, 
                            uint16_t elementSize, 
                            uint32_t capacity)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }


    if ( bufferSize < (elementSize * capacity)) {
        return Error_InsufficientMemory;
    }


    buffer->head = 0;
    buffer->tail = 0;
    buffer->capacity = capacity;

    return Error_None;
}

Error RingBuffer_Enqueue(RingBuffer *buffer, DataElement *item)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    if (RingBuffer_IsFull(buffer)) {
        return Error_InsufficientMemory;
    }

    buffer->data[buffer->head] = *item;
    buffer->head = (buffer->head + 1) % buffer->capacity;

    return Error_None;
}

Error RingBuffer_Dequeue(RingBuffer *buffer, DataElement *item)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    Error error = RingBuffer_Peek(buffer, item);
    if (error != Error_None) {
        return error;
    }

    if (item->pointer == NULL) {
        return Error_None;
    }

    buffer->tail  = (buffer->tail + 1) % buffer->capacity;

    return Error_None;
}

Error RingBuffer_Peek(RingBuffer *buffer, DataElement *item)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    if (RingBuffer_IsEmpty(buffer)) {
        item->pointer = NULL;
        return Error_None;
    }

    *item = buffer->data[buffer->tail];

    return Error_None;
}

Error RingBuffer_GetSize(RingBuffer *buffer, uint32_t *size)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    *size = (buffer->head > buffer->tail) ? 
                (buffer->head - buffer->tail) :
                (buffer->head + buffer->capacity - buffer->tail);

    return Error_None;
}


bool RingBuffer_IsFull(RingBuffer *buffer)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    return (buffer->head + 1) % buffer->capacity == buffer->tail;
}

bool RingBuffer_IsEmpty(RingBuffer *buffer)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    return buffer->head == buffer->tail;
}
