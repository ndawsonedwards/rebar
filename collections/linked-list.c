#include "linked-list.h"
#include <stdio.h>

/**
 * @brief Initialized linked list for first time use
 * 
 * @param list pointer to Linked List structure
 * @return Error 
 */
Error LinkedList_Initialize(LinkedList *const list, uint32_t capacity)
{

    if (ILLEGAL_POINTER(list)) {
        return Error_IllegalPointer;
    }

    if (capacity == 0) {
        return Error_InvalidLength;
    }

    list->head = NULL;
    list->length = 0;
    list->capacity = capacity;

    return Error_None;

}

/**
 * @brief Appends a node to end of Linked List
 * 
 * @param list Linked list to append to the end
 * @param addNode Node to append to the end
 * @return Error 
 */
Error LinkedList_Append(LinkedList *const list, LinkedListNode *const addNode)
{
    if (ILLEGAL_POINTER(list) || ILLEGAL_POINTER(addNode)) {
        return Error_IllegalPointer;
    }    
    
    if (list->length == list->capacity) {
        return Error_InsufficientMemory;
    }

    addNode->next = NULL;
    list->length++;

    if (list->head == NULL) {
        list->head = addNode;
        return Error_None;
    }

    LinkedListNode *node = list->head;
    uint32_t index = 0;
    while ( (node->next != NULL ) && (index < list->capacity)) {
        index++;
        node = node->next;
    }

    node->next = addNode;

    return Error_None;
}

/**
 * @brief Removes the node from the linked list
 * 
 * @param list Linked lIst
 * @param node node to remove
 * @return Error 
 */
Error LinkedList_Remove(LinkedList *const list, LinkedListNode *const removeNode)
{
    if (ILLEGAL_POINTER(list) || ILLEGAL_POINTER(removeNode)) {
        return Error_IllegalPointer;
    }    

    LinkedListNode * previousNode = list->head;
    LinkedListNode * node = list->head;

    uint32_t index = 0;
    while ((node != NULL) && (index < list->capacity)) {
        if (node == removeNode) {
            previousNode->next = node->next;
            list->length--;
            return Error_None;

        }else {
            previousNode = node;
            node = node->next;
        }
    }

    return Error_NotFound;
}


/**
 * @brief Checks if the node exists withing the linked list. Search function will be run against each node. 
 * 
 * @param list Linked List
 * @param searchFunction Search function to perform the per node check
 * @param foundlist Returns list of items which match search criteria
 * @return Error 
 */
Error LinkedList_Contains(LinkedList *const list, LinkedList_Search searchFunction, LinkedList * foundList) {
    return Error_NotImplemented;
}


/**
 * @brief returns the count of nodes in the list
 * 
 * @param list Linked List to return count for
 * @return uint16_t 
 */
uint16_t LinkedList_GetLength(LinkedList *const list)
{
    if (ILLEGAL_POINTER(list)) {
        return Error_IllegalPointer;
    }    
    return list->length;
}

Error LinkedList_Reset(LinkedList * const list) {
    if (ILLEGAL_POINTER(list)) {
        return Error_IllegalPointer;
    }    

    list->head = NULL;
    list->length = 0;


    return Error_None;
}

