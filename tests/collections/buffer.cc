#include <gtest/gtest.h>

extern "C" {
#include "buffer.h"
#include "rebar.h"
#include <string.h>
}

#define SIZE  10

class BufferTest : public ::testing::Test {
	protected:

};


TEST_F(BufferTest, Initialze) {

    Buffer buffer = {0};
	uint8_t data[SIZE];
    memset(data, 0xff, sizeof(data));
    
    Error error = Buffer_Initialize(data, sizeof(data), &buffer);
    EXPECT_EQ(Error_None, error);
    EXPECT_EQ(sizeof(data[0]) * SIZE, buffer.lengthInBytes);

}

TEST_F(BufferTest, ReadWrite_Uint8) {

    Buffer buffer = {0};
	uint8_t data[SIZE];
    memset(data, 0xff, sizeof(data));
    

    Error error = Buffer_Initialize(data, sizeof(data) ,&buffer);
    EXPECT_EQ(Error_None, error);
    EXPECT_EQ(sizeof(data), buffer.lengthInBytes);

    for (uint8_t i = 0; i < ARRAY_SIZE(data); i++)
    {
        uint8_t entry = i;
        error = Buffer_Write(&buffer, &entry, sizeof(entry), sizeof(entry) * i);
        EXPECT_EQ(Error_None, error);
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(data); i++)
    {
        uint8_t entry = 0;
        error = Buffer_Read(&buffer, &entry, sizeof(entry), sizeof(entry) * i);
        EXPECT_EQ(Error_None, error);
        EXPECT_EQ(i, entry);
    }
}

TEST_F(BufferTest, ReadWrite_Uint32) {

    Buffer buffer = {0};
	uint32_t data[SIZE];
    memset(data, 0xffffffff, sizeof(data));
    

    Error error = Buffer_Initialize(data, sizeof(data) ,&buffer);
    EXPECT_EQ(Error_None, error);
    EXPECT_EQ(sizeof(data), buffer.lengthInBytes);

    for (uint8_t i = 0; i < ARRAY_SIZE(data); i++)
    {
        uint32_t entry = i;
        error = Buffer_Write(&buffer, &entry, sizeof(entry), sizeof(entry) * i);
        EXPECT_EQ(Error_None, error);
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(data); i++)
    {
        uint32_t entry = 0;
        error = Buffer_Read(&buffer, &entry, sizeof(entry), sizeof(entry) * i);
        EXPECT_EQ(Error_None, error);
        EXPECT_EQ(i, entry);
    }
}
