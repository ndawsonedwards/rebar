#include <gtest/gtest.h>

extern "C" {
#include "linked-list.h"
#include "string.h"
#include "rebar.h"
}

class LinkedListTest : public ::testing::Test {
	protected:

	LinkedList list;
    #define LIST_CAPACITY  10

	virtual void SetUp() {
		list.capacity = LIST_CAPACITY;

		Error error = LinkedList_Initialize(&list, LIST_CAPACITY);
		EXPECT_EQ(error, Error_None);
	}	
};


typedef struct SampleDataNode{
    LinkedListNode node;
    uint32_t value;

}SampleDataNode;

TEST_F(LinkedListTest, AddNode) {

    SampleDataNode dataNode;
    dataNode.value = 10;

    EXPECT_EQ(LinkedList_GetLength(&list), 0);

    Error error = LinkedList_Append(&list, (LinkedListNode*) &dataNode);
    EXPECT_EQ(error, Error_None);
    EXPECT_EQ(LinkedList_GetLength(&list), 1);

    
}
TEST_F(LinkedListTest, ForEachIterator) {


    Error error = LinkedList_Reset(&list);
    EXPECT_EQ(error, Error_None);
    EXPECT_EQ(LinkedList_GetLength(&list), 0);

    SampleDataNode data[LIST_CAPACITY] = {0};
    for(uint8_t i = 0; i < LIST_CAPACITY; i++) {
        data->value = i;
        error = LinkedList_Append(&list, (LinkedListNode*) &data[i]);
        EXPECT_EQ(error, Error_None);
        EXPECT_EQ(LinkedList_GetLength(&list), i+1);
    }

    uint16_t sum = 0;
    LinkedListNode *node;
    LINKED_LIST_FOR_EACH(node, list) {
        SampleDataNode *node = node;
        sum = sum + node->value; 
    }

    EXPECT_EQ(sum, 45);

}
