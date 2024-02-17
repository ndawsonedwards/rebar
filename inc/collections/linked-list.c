#include "linked-list.h"






Error LinkedList_Initialize(LinkedList *const list)
{

    list->head = NULL;
    list->length = 0;
    
    return Error_None;

}

Error LinkedList_Add(LinkedList *const list, LinkedListNode *const node)
{
    return Error_None;
}


Error LinkedList_Remove(LinkedList *const list, LinkedListNode *const node)
{
    return Error_None;
}

uint16_t LinkedList_GetLength()
{
    return 0;
}
