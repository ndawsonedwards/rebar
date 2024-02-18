#ifndef DATA_ELEMENT_H
#define DATA_ELEMENT_H

#include <stdint.h>

/**
 * @brief Union of data types to support generic type ring buffer
 * 
 */
typedef union {

    void *pointer;

    uint32_t valueInt;

    float valueFloat;
}DataElement;




#endif // DATA_ELEMENT_H