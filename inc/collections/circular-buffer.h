#ifndef CIRCULAR_BUFFER_Hstack
#define CIRCULAR_BUFFER_H


#include "include.h"
#include "data-element.h"

typedef struct {
    DataElement *data;
    void *front; 
    void *rear; 
    uint32_t size;
    uint32_t capacity
} RingBuffer;

/**
 * @brief Initializes ring buffer for first time use
 * 
 * @param buffer Ring Buffer structure to initialize
 * @param elementSize Size of each element in RingBuffer, in bytes
 * @param capacity total amount of elements ring buffer can contain 
 * @return Error 
 */
Error RingBuffer_Initialize(RingBuffer *buffer, uint16_t elementSize, uint32_t capacity);

/**
 * @brief Enring buffers an item onto the ring buffer
 * 
 * @param buffer Ring Buffer to add to 
 * @param item item to add to the ring buffer
 * @return Error 
 */
Error RingBuffer_Enqueue(RingBuffer *buffer, void *item);

/**
 * @brief Dering buffers an item off of the ring buffer
 * 
 * @param buffer Ring Buffer to remove from 
 * @param item item that is removed from the ring buffer
 * @return Error 
 */
Error RingBuffer_Dequeue(RingBuffer *buffer,void *item);

/**
 * @brief Checks if there is an element to Dering buffer. This does not remove the item from the ring buffer
 * 
 * @param buffer Ring Buffer to peek from 
 * @param item Next itme, if available. or NULL if there is no item to peek
 * @return Error 
 */
Error RingBuffer_Peek(RingBuffer *buffer, void *item);

/**
 * @brief Returns the total number of items on the ring buffer
 * 
 * @param buffer RingBuffer
 * @return Error 
 */
Error RingBuffer_GetCount(RingBuffer *buffer);

/**
 * @brief Checks if the ring buffer is full
 * 
 * @param buffer Ring Buffer to check 
 * @return true If ring buffer is full
 * @return false If ring buffer is not full
 */
bool RingBuffer_IsFull(RingBuffer *buffer);

/**
 * @brief Checks if the ring buffer is emtpy
 * 
 * @param buffer Ring Buffer to check
 * @return true If ring buffer is empty
 * @return false If ring buffer is not empty
 */
bool RingBuffer_IsEmpty(RingBuffer *buffer);


#endif // CIRCULAR_BUFFER_H