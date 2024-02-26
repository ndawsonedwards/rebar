#include "buffer.h"
#include <string.h>

/**
 * @brief Initializes buffer to point to a specific memory 
 * 
 * @param data Pointer do the data
 * @param lengthInBytes length of the memory region, in bytes
 * @param buffer returned initialized buffer
 * @return Error 
 */
Error Buffer_Initialize(void *data, uint32_t lengthInBytes, Buffer *buffer)
{
    if (ILLEGAL_POINTER(data) || ILLEGAL_POINTER(buffer))
    {
        return Error_IllegalPointer;
    }

    uintptr_t address = (uintptr_t) data;
    memcpy((void*) &buffer->data, &address, sizeof(address));
    buffer->lengthInBytes = lengthInBytes;

    return Error_None;
}

/**
 * @brief Writes a data element to the buffer
 * 
 * @param buffer buffer object
 * @param data data to write to the buffers
 * @param lengthInBytes length of data in bytes
 * @param offsetInBytes offset to write data to 
 * @return Error 
 */
Error Buffer_Write(Buffer *buffer, void *data, uint32_t lengthInBytes, uint32_t offsetInBytes)
{
    Error error = Buffer_SanityCheck(buffer);
    if (error != Error_None)
    {
        return error;
    }
    if (ILLEGAL_POINTER(data))
    {
        return Error_IllegalPointer;
    }

    if ((offsetInBytes + lengthInBytes) > buffer->lengthInBytes)
    {
        return Error_InsufficientMemory;
    }


    memcpy(&buffer->data[offsetInBytes], data, lengthInBytes);

    return Error_None;
}

/**
 * @brief Reads from the buffer at a specified index
 * 
 * @param buffer buffer object
 * @param data data read from buffer
 * @param lengthInBytes length of data in bytes
 * @param offsetInBytes offset to write data to 
 * @return Error 
 */
Error Buffer_Read(Buffer *buffer, void *data, uint32_t lengthInBytes, uint32_t offsetInBytes)
{
    Error error = Buffer_SanityCheck(buffer);
    if (error != Error_None)
    {
        return error;
    }
    if (ILLEGAL_POINTER(data))
    {
        return Error_IllegalPointer;
    }

    memcpy(data, &buffer->data[offsetInBytes], lengthInBytes);

    return Error_None;
}

/**
 * @brief Sanity checks the pointer values and length of teh buffer
 * 
 * @param buffer Buffer to sanity check
 * @return Error Returns no error if sanity check passes without issue
 */
Error Buffer_SanityCheck(Buffer *buffer)
{
    if (ILLEGAL_POINTER(buffer))
    {
        return Error_IllegalPointer;
    }
    if (ILLEGAL_POINTER(buffer->data))
    {
        return Error_IllegalPointer;
    }
    if (buffer->lengthInBytes == 0)
    {
        return Error_InvalidLength;
    }

    return Error_None;
}

