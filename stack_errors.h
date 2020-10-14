//
//  stack_errors.h
//  unkillable_stack
//
//  Created by Alexandra Korabulina on 06.10.2020.
//

#ifndef stack_errors_h
#define stack_errors_h

//--------------------------------------------------------------------------------

const void * errptr = (void *)13;
const long poison = 0xDEADBEEFDEADBE7F;
const unsigned long long good_canary = 0xDEADBEEFBADF00DULL;

//--------------------------------------------------------------------------------

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
    BAD_QUANTITY,
    BAD_STACK_CANARY,
    BAD_DATA_CANARY,
    BAD_HASH_POINTER_TO_DATA,
    BAD_HASH_POINTER_TO_HASH,
    BAD_HASH,
    HASH_FUNC
};

//--------------------------------------------------------------------------------

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
        case BAD_STACK_CANARY:
            fprintf(stderr, " (Stack canary is spoiled) ");
            break;
        case BAD_DATA_CANARY:
            fprintf(stderr, " (Data canary is spoiled) ");
            break;
        case BAD_HASH_POINTER_TO_DATA:
            fprintf(stderr, " (Hash function got null pointer to data) ");
            break;
        case BAD_HASH_POINTER_TO_HASH:
            fprintf(stderr, " (Hash function got null pointer to hash) ");
            break;
        case BAD_HASH:
            fprintf(stderr, " (Hash is incorrect) ");
            break;
        case HASH_FUNC:
            fprintf(stderr, " (Error in StackHash function) ");
            break;
    }
}

//--------------------------------------------------------------------------------

//! Counts hash for stack structure
//!
//! @param [in] p  pointer to stack
//! @param [in] count  number of bytes to count hash
//! @param [out] h  pointer to place to write answer
//!
//! @return 0 in case hash counted successfully, otherwise type of error (see enum error definition in stack_errors.h)
int StackHash(char * p, int count, unsigned long long * h) {
    if (!p) {
        return BAD_HASH_POINTER_TO_DATA;
    }
    if (!h) {
        return BAD_HASH_POINTER_TO_HASH;
    }
    unsigned long long tmp = 0;
    while (count > 0) {
        tmp = tmp + *p;
        tmp = tmp - ((tmp << 8) | (tmp >> 10));
        p++;
        count--;
    }
    *h = tmp;
    return 0;
}

#endif
