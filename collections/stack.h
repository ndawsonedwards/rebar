#ifndef STACK_H
#define STACK_H

#include "rebar.h"
#include "data-element.h"

typedef struct {

    DataElement *top;

    uint16_t length;

    uint16_t capacity;

}Stack;

/**
 * @brief Initializes stack for first time use
 * 
 * @param stack Stack structure to initialize
 * @param elementSize Size of each element in Stack, in bytes
 * @param capacity total amount of elements stack can contain 
 * @return Error 
 */
Error Stack_Initialize(Stack *stack, uint16_t elementSize, uint32_t capacity);

/**
 * @brief Enstackse an item onto the stack
 * 
 * @param stack Stack to add to 
 * @param item item to add to the stack
 * @return Error 
 */
Error Stack_Enstack(Stack *stack, void *item);

/**
 * @brief Destacks an item off of the stack
 * 
 * @param stack Stack to remove from 
 * @param item item that is removed from the stack
 * @return Error 
 */
Error Stack_Destack(Stack *stack,void *item);

/**
 * @brief Checks if there is an element to Destack. This does not remove the item from the stack
 * 
 * @param stack Stack to peek from 
 * @param item Next itme, if available. or NULL if there is no item to peek
 * @return Error 
 */
Error Stack_Peek(Stack *stack, void *item);

/**
 * @brief Returns the total number of items on the stack
 * 
 * @param stack Stack
 * @return Error 
 */
Error Stack_GetCount(Stack *stack);

/**
 * @brief Checks if the stack is full
 * 
 * @param stack Stack to check 
 * @return true If stack is full
 * @return false If stack is not full
 */
bool Stack_IsFull(Stack *stack);

/**
 * @brief Checks if the stack is emtpy
 * 
 * @param stack Stack to check
 * @return true If stack is empty
 * @return false If stack is not empty
 */
bool Stack_IsEmpty(Stack *stack);


#endif // STACK_H