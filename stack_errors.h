//
//  stack_errors.h
//  unkillable_stack
//
//  Created by Alexandra Korabulina on 06.10.2020.
//

#ifndef stack_errors_h
#define stack_errors_h

const void * errptr = (void *)13;

enum error {
    OK = 0,
    FUNC_NULL_POINTER_TO_STACK,
    FUNC_ZERO_CAPACITY,
    FUNC_NULL_POINTER_TO_VALUE,
    REPEATED_STACK_CONSTR,
    STACK_CHECK,
    BAD_ALLOC,
    STACK_OVERFLOW,
    STACK_EMPTY,
    SIZE_LARGER_THEN_CAPACITY,
    BAD_CAPACITY,
    BAD_SIZE,
    BAD_DATA,
    BAD_QUANTITY
};

//! Prints clarification for every type of error
//!
//! @param [in] err type of error
void PrintError(enum error err) {
    switch (err) {
        case OK:
            fprintf(stderr, " (ok) ");
            break;
        case FUNC_NULL_POINTER_TO_STACK:
            fprintf(stderr, " (Stack function got null pointer to stack) ");
            break;
        case FUNC_ZERO_CAPACITY:
            fprintf(stderr, " (Stack constructor got zero capacity) ");
            break;
        case FUNC_NULL_POINTER_TO_VALUE:
            fprintf(stderr, " (Stack function got zero pointer to value for pop) ");
            break;
        case REPEATED_STACK_CONSTR:
            fprintf(stderr, " (Attempt to construct stack that already exists) ");
            break;
        case STACK_CHECK:
            fprintf(stderr, " (Error during checking the stack for integrity) ");
            break;
        case BAD_ALLOC:
            fprintf(stderr, " (Can't allocate memory) ");
            break;
        case STACK_OVERFLOW:
            fprintf(stderr, " (Stack is overflowed, can't make push) ");
            break;
        case STACK_EMPTY:
            fprintf(stderr, " (Stack is empty, can't make pop) ");
            break;
        case SIZE_LARGER_THEN_CAPACITY:
            fprintf(stderr, " (Stack's size is larger then capacity) ");
            break;
        case BAD_CAPACITY:
            fprintf(stderr, " (Stack's capacity is under or equal zero) ");
            break;
        case BAD_SIZE:
            fprintf(stderr, " (Stack's size is under zero) ");
            break;
        case BAD_DATA:
            fprintf(stderr, " (Something wrong with stack data) ");
            break;
        case BAD_QUANTITY:
            fprintf(stderr, " (In fact stack has more or less then size elements) ");
            break;
    }
}


#endif
