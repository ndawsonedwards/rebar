#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "include.h"
#include "data-element.h"

typedef struct LinkedListNode{
    DataElement * data;

    LinkedListNode *next;

}LinkedListNode;


typedef struct {
    LinkedListNode *head;

    uint16_t length;

}LinkedList;



typedef bool (*LinkedList_Search)(DataElement *element);

/**
 * @brief Initialized linked list for first time use
 * 
 * @param list pointer to Linked List structure
 * @return Error 
 */
Error LinkedList_Initialize(LinkedList *const list);


/**
 * @brief Appends node to end of Linked List
 * 
 * @param list Linked list to append to the end
 * @param node Node to append to the end
 * @return Error 
 */
Error LinkedList_Append(LinkedList *const list, LinkedListNode *const node);

/**
 * @brief Adds Node at the speciied index, or appends if index is larger than current length. 
 * 
 * @param list Linked list
 * @param node Node to add 
 * @param index index position to add the node at
 * @return Error 
 */
Error LinkedList_AddAt(LinkedList *const list, LinkedListNode *const node, uint16_t index);

/**
 * @brief Adds the node after the specified node
 * 
 * @param list Linked List
 * @param after Node in the linked list that the new node will be added after
 * @param node Node to be added 
 * @return Error 
 */
Error LinkedList_AddAfter(LinkedList *const list, LinkedListNode *const after, LinkedListNode * const node);

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
 * @return Error 
 */
Error LinkedList_Contains(LinkedList *const list, LinkedList_Search searchFunction);

uint16_t LinkedList_GetLength();

Error LinkedList_Terminate(LinkedList * const list);

#endif // LINKED_LIST_H