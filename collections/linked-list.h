#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "rebar.h"
#include "data-element.h"

typedef struct LinkedListNode{
    struct LinkedListNode *next;

}LinkedListNode;


typedef struct {
    LinkedListNode *head;

    uint32_t capacity;
    uint16_t length;

}LinkedList;


#define LINKED_LIST_FOR_EACH(i, list)   for((i) = (list).head;\
                                            (i) != (NULL);\
                                            (i) = (LinkedListNode *)((i)->next))

typedef bool (*LinkedList_Search)(LinkedListNode *node);

/**
 * @brief Initialized linked list for first time use
 * 
 * @param list pointer to Linked List structure
 * @return Error 
 */
Error LinkedList_Initialize(LinkedList *const list, uint32_t capacity);


/**
 * @brief Appends a node to end of Linked List
 * 
 * @param list Linked list to append to the end
 * @param addNode Node to append to the end
 * @return Error 
 */
Error LinkedList_Append(LinkedList *const list, LinkedListNode *const addNode);


/**
 * @brief Removes the node from the linked list
 * 
 * @param list Linked lIst
 * @param node node to remove
 * @return Error 
 */
Error LinkedList_Remove(LinkedList *const list, LinkedListNode *const node);

/**
 * @brief Checks if the node exists withing the linked list. Search function will be run against each node. 
 * 
 * @param list Linked List
 * @param searchFunction Search function to perform the per node check
 * @param foundlist Returns list of items which match search criteria
 * @return Error 
 */
Error LinkedList_Contains(LinkedList *const list, LinkedList_Search searchFunction, LinkedList * foundList);

/**
 * @brief returns the count of nodes in the list
 * 
 * @param list Linked List to return count for
 * @return uint16_t 
 */
uint16_t LinkedList_GetLength(LinkedList *const list);


Error LinkedList_Reset(LinkedList * const list);

#endif // LINKED_LIST_H