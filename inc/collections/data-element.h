#ifndef DATA_ELEMENT_H
#define DATA_ELEMENT_H

#include <stdint.h>

typedef struct {
    void *data;

    uint32_t sizeInBytes;

}DataElement;


#endif // DATA_ELEMENT_H