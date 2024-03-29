#include <gtest/gtest.h>

extern "C" {
#include "ring-buffer.h"
#include "rebar.h"
}

#define SIZE  10

class RingBufferTest : public ::testing::Test {
	protected:

	RingBuffer buffer;
	DataElement data[SIZE] = {0};

	virtual void SetUp() {
		buffer.data = data;

		Error error = RingBuffer_Initialize(&buffer, sizeof(data), 4, SIZE);
		EXPECT_EQ(error, Error_None);
	}	
};


TEST_F(RingBufferTest, Initialze) {

	Error error = RingBuffer_Clear(&buffer);
	EXPECT_EQ(error, Error_None);

	bool isEmpty = false;
	RingBuffer_IsEmpty(&buffer, &isEmpty);
	EXPECT_EQ(isEmpty, true);

	uint32_t size = INT_MAX;
	error = RingBuffer_GetSize(&buffer, &size);
	EXPECT_EQ(error, Error_None);
	EXPECT_EQ(size, 0);

}

TEST_F(RingBufferTest, EnqueueDequeueNoOverwriteInt) {

	Error error = RingBuffer_Clear(&buffer);
	EXPECT_EQ(error, Error_None);

	uint32_t size = INT_MAX;
	error = RingBuffer_GetSize(&buffer, &size);
	EXPECT_EQ(error, Error_None);
	EXPECT_EQ(size, 0);

	//Enqueue
	for (uint16_t i = 0; i < SIZE; i++)
	{
		DataElement element;
		element.valueInt = i;

		Error error = RingBuffer_EnqueueNoOverwrite(&buffer, &element);
		EXPECT_EQ(error, Error_None) << "RingBuffer_EnqueueNoOverwrite failed : " <<  error << ". index = " << i ;

		size = INT_MAX;
		error = RingBuffer_GetSize(&buffer, &size);
		EXPECT_EQ(error, Error_None) << "RingBuffer_GetSize failed : " << error << ". index = " << i ;
		EXPECT_EQ(size, i + 1)  << "RingBuffer_GetSize failed. expected 0, found  " << size << ". index = " << i ;
	}


	//Dequeue
	size = INT_MAX;
	for (uint16_t i = 0; i < SIZE; i++)
	{
		DataElement element = {0};
		
		Error error = RingBuffer_GetSize(&buffer, &size);
		EXPECT_EQ(error, Error_None) << "RingBuffer_GetSize failed : " << error << ". index = " << i ;
		EXPECT_EQ(size, SIZE - i)  << "RingBuffer_GetSize failed. expected 0, found  " << size << ". index = " << i ;

		error = RingBuffer_Dequeue(&buffer, &element);
		EXPECT_EQ(error, Error_None) << "RingBuffer_Dequeue failed : " << error << ". index = " << i ;
		EXPECT_EQ(element.valueInt, i) << "INcorrect value : " << element.valueInt << ". index = " << i ;

		error = RingBuffer_GetSize(&buffer, &size);
		EXPECT_EQ(error, Error_None) << "RingBuffer_GetSize failed : " << error << ". index = " << i ;
		EXPECT_EQ(size, SIZE - i - 1)  << "RingBuffer_GetSize failed. expected 0, found  " << size << ". index = " << i ;
	}

}

TEST_F(RingBufferTest, EnqueueDequeueInt) {

	Error error = RingBuffer_Clear(&buffer);
	EXPECT_EQ(error, Error_None);

	uint32_t size = INT_MAX;
	error = RingBuffer_GetSize(&buffer, &size);
	EXPECT_EQ(error, Error_None);
	EXPECT_EQ(size, 0);

	//Enqueue more than capacity
	for (uint16_t i = 0; i < (SIZE * 2); i++)
	{
		DataElement element;
		element.valueInt = i;

		Error error = RingBuffer_Enqueue(&buffer, &element);
		EXPECT_EQ(error, Error_None) << "RingBuffer_EnqueueNoOverwrite failed : " <<  error << ". index = " << i ;

		size = INT_MAX;
		error = RingBuffer_GetSize(&buffer, &size);
		EXPECT_EQ(error, Error_None) << "RingBuffer_GetSize failed : " << error << ". index = " << i ;
		uint16_t expectedSize = (i < 10) ?  (i + 1) : 10;
		EXPECT_EQ(size, expectedSize)  << "RingBuffer_GetSize failed. expected 0, found  " << size << ". index = " << i ;
	}

	//Dequeue
	size = INT_MAX;
	for (uint16_t i = 0; i < SIZE; i++)
	{
		DataElement element = {0};
		Error error = RingBuffer_GetSize(&buffer, &size);
		EXPECT_EQ(error, Error_None) << "RingBuffer_GetSize failed : " << error << ". index = " << i ;
		EXPECT_EQ(size, SIZE - i)  << "RingBuffer_GetSize failed. expected 0, found  " << size << ". index = " << i ;

		error = RingBuffer_Dequeue(&buffer, &element);
		EXPECT_EQ(error, Error_None) << "RingBuffer_Dequeue failed : " << error << ". index = " << i ;
		EXPECT_EQ(element.valueInt, i + SIZE) << "Incorrect value : " << element.valueInt << ". index = " << i ;

		error = RingBuffer_GetSize(&buffer, &size);
		EXPECT_EQ(error, Error_None) << "RingBuffer_GetSize failed : " << error << ". index = " << i ;
		EXPECT_EQ(size, SIZE - i - 1)  << "RingBuffer_GetSize failed. expected 0, found  " << size << ". index = " << i ;
	}

}
