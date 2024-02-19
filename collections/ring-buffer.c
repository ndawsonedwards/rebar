#include "ring-buffer.h"

/**
 * @brief Initializes ring buffer for first time use
 * 
 * @param buffer Ring Buffer structure to initialize
 * @param elementSize Size of each element in RingBuffer, in bytes
 * @param capacity total amount of elements ring buffer can contain 
 * @return Error 
 */
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

/**
 * @brief Enqueues an item onto the ring buffer. Returns Insufficient Memory error if Enqueue when full
 * 
 * @param buffer Ring Buffer to add to 
 * @param item item to add to the ring buffer
 * @return Error 
 */
Error RingBuffer_EnqueueNoOverwrite(RingBuffer *buffer, DataElement *item)
{
    if (ILLEGAL_POINTER(buffer) || ILLEGAL_POINTER(item)) {
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
Error RingBuffer_Enqueue(RingBuffer *buffer, DataElement *item) {

    if (ILLEGAL_POINTER(buffer) || ILLEGAL_POINTER(item)) {
        return Error_IllegalPointer;
    }

    if (buffer->isFull) {
        buffer->tail = (buffer->tail + 1) % buffer->capacity;
    }

    buffer->data[buffer->head] = *item;
    buffer->head = (buffer->head + 1) % buffer->capacity;

    buffer->isFull = (buffer->head == buffer->tail);
    return Error_None;

}

/**
 * @brief Dering buffers an item off of the ring buffer
 * 
 * @param buffer Ring Buffer to remove from 
 * @param item item that is removed from the ring buffer
 * @return Error 
 */
Error RingBuffer_Dequeue(RingBuffer *buffer, DataElement *item)
{
    if (ILLEGAL_POINTER(buffer) || ILLEGAL_POINTER(item)) {
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

/**
 * @brief Checks if there is an element to Dering buffer. This does not remove the item from the ring buffer. Returns Error_NotFound if buffer is empty
 * 
 * @param buffer Ring Buffer to peek from 
 * @param item Next itme, if available. or NULL if there is no item to peek
 * @return Error 
 */
Error RingBuffer_Peek(RingBuffer *buffer, DataElement *item)
{
    if (ILLEGAL_POINTER(buffer) || ILLEGAL_POINTER(item)) {
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

/**
 * @brief Returns the total number of items on the ring buffer
 * 
 * @param buffer RingBuffer
 * @param size The amount of items stored in the buffer
 * @return Error 
 */
Error RingBuffer_GetSize(RingBuffer *buffer, uint32_t *size)
{
    if (ILLEGAL_POINTER(buffer) || ILLEGAL_POINTER(size)) {
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

/**
 * @brief Checks if the ring buffer is full
 * 
 * @param buffer Ring Buffer to check 
 * @param isFull return true if ring buffer is full, false otherwise
 * @return Error 
 */
Error RingBuffer_IsFull(RingBuffer *buffer, bool *isFull)
{
    if (ILLEGAL_POINTER(buffer) || ILLEGAL_POINTER(isFull)) {
        return Error_IllegalPointer;
    }

    *isFull = buffer->isFull;
    return Error_None;
}

/**
 * @brief Checks if the ring buffer is emtpy
 * 
 * @param buffer Ring Buffer to check
 * @param isEmpty return true if ring buffer is empty, false otherwise
 * @return Error 
 */
Error RingBuffer_IsEmpty(RingBuffer *buffer, bool *isEmpty)
{
    if (ILLEGAL_POINTER(buffer) || ILLEGAL_POINTER(isEmpty)) {
        return Error_IllegalPointer;
    }

    *isEmpty = ((buffer->head == buffer->tail) && ( ! buffer->isFull));
    return Error_None;

}

/**
 * @brief Clears entries from the buffer. 
 * 
 * @param buffer 
 * @return Error 
 */
Error RingBuffer_Clear(RingBuffer *buffer) {
    if (ILLEGAL_POINTER(buffer)) {
        return Error_IllegalPointer;
    }

    buffer->head = 0;
    buffer->tail = 0;

    return Error_None;
}
