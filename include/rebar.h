#ifndef REBAR_H
#define REBAR_H


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

#ifndef NULL
#define NULL (void *)0
#endif


#define VARIABLE_UNUSED(x)              ((void) x)

#define IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) == (BIT))
#define IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)

#define ILLEGAL_POINTER(x)              (!(x))

#endif //REBAR_H