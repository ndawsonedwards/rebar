#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include "rebar.h"

typedef struct 
{
    uint8_t * const data;
    uint32_t lengthInBytes;
}Buffer;

/**
 * @brief Initializes buffer to point to a specific memory
 * 
 * @param data Pointer do the data
 * @param lengthInBytes length of the memory region, in bytes
 * @param buffer returned initialized buffer
 * @return Error 
 */
Error Buffer_Initialize(void *data, uint32_t lengthInBytes, Buffer * buffer);

/**
 * @brief Writes a data element to the buffer
 * 
 * @param buffer buffer object
 * @param data data to write to the buffers
 * @param lengthInBytes length of data in bytes
 * @param offsetInBytes offset to write data to 
 * @return Error 
 */
Error Buffer_Write(Buffer *buffer, void *data, uint32_t lengthInBytes, uint32_t offsetInBytes);

/**
 * @brief Reads from the buffer at a specified index
 * 
 * @param buffer buffer object
 * @param data data read from buffer
 * @param lengthInBytes length of data in bytes
 * @param offsetInBytes offset to write data to 
 * @return Error 
 */
Error Buffer_Read(Buffer *buffer,   void *data, uint32_t lengthInBytes, uint32_t offsetInBytes);


/**
 * @brief Sanity checks the pointer values and length of teh buffer
 * 
 * @param buffer Buffer to sanity check
 * @return Error Returns no error if sanity check passes without issue
 */
Error Buffer_SanityCheck(Buffer *buffer);

#endif // BUFFER_H