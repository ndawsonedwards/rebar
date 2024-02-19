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
    buffer->isFull = false;

    return Error_None;
}

Error RingBuffer_Enqueue(RingBuffer *buffer, DataElement *item)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    bool isFull = false;
    Error error = RingBuffer_IsFull(buffer, &isFull);
    if (error != Error_None) {
        return error;
    }

    if (buffer->isFull) {
        return Error_InsufficientMemory;
    }

    buffer->data[buffer->head] = *item;
    buffer->head = (buffer->head + 1) % buffer->capacity;

    buffer->isFull = (buffer->head == buffer->tail);
    return Error_None;
}

/**
 * @brief Enqueues an item onto the ring buffer. Will overrite next element if full.
 * 
 * @param buffer Ring Buffer to add to 
 * @param item item to add to the ring buffer
 * @return Error 
 */
Error RingBuffer_EnqueueOverwrite(RingBuffer *buffer, DataElement *item) {

    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    buffer->data[buffer->head] = *item;
    buffer->head = (buffer->head + 1) % buffer->capacity;

    buffer->isFull = (buffer->head == buffer->tail);
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
    
    buffer->tail  = (buffer->tail + 1) % buffer->capacity;
    buffer->isFull = false;

    return Error_None;
}

Error RingBuffer_Peek(RingBuffer *buffer, DataElement *item)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    bool isEmpty = false;
    Error error = RingBuffer_IsEmpty(buffer,&isEmpty);
    if (error != Error_None) {
        return error;
    }
    if (isEmpty) {
        return Error_NotFound;
    }

    *item = buffer->data[buffer->tail];

    return Error_None;
}

Error RingBuffer_GetSize(RingBuffer *buffer, uint32_t *size)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    if (buffer->isFull) {
        *size = buffer->capacity;
        return Error_None;
    }

    *size = (buffer->head >= buffer->tail) ? 
                (buffer->head - buffer->tail) :
                (buffer->head + buffer->capacity - buffer->tail);

    return Error_None;
}


Error RingBuffer_IsFull(RingBuffer *buffer, bool *isFull)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    *isFull = buffer->isFull;
    return Error_None;
}

Error RingBuffer_IsEmpty(RingBuffer *buffer, bool *isEmpty)
{
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    *isEmpty = ((buffer->head == buffer->tail) && ( ! buffer->isFull));
    return Error_None;

}

/**
 * @brief Clears entries from the buffer. 
 * 
 * @param buffer 
 * @return Error * 
 */
Error RingBuffer_Clear(RingBuffer *buffer) {
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    buffer->head = 0;
    buffer->tail = 0;

    return Error_None;
}
