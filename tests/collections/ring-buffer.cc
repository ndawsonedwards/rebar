#include <gtest/gtest.h>

extern "C" {
#include "ring-buffer.h"
#include "rebar.h"
}


TEST(BufferInitTest, IsNull) {

    RingBuffer buffer;

    const uint8_t SIZE = 10;
    DataElement data[SIZE] = {0};
    buffer.data = data;

    Error error = RingBuffer_Initialize(&buffer, sizeof(data), 4, SIZE);
    EXPECT_EQ(error, Error_None);

    EXPECT_EQ(RingBuffer_IsEmpty(&buffer), true);

    uint32_t size = 123;
    error = RingBuffer_GetSize(&buffer, &size);
    EXPECT_EQ(error, Error_None);
    EXPECT_EQ(size, 0);

}

