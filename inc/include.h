#ifndef _INCLUDE_H_
#define _INCLUDE_H_


/*****************************************************
 *  Includes
******************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "errors.h"

/*****************************************************
 *  Macros
******************************************************/
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif //ARRAY_SIZE


#define VARIABLE_UNUSED(x)              ((void) x)

#define IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) == (BIT))
#define IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)

#define ILLEGAL_POINTER(x)              (!(x))

#endif //_INCLUDE_H_