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
    FILE * log = fopen("stack.log", "a");
    switch (err) {
        case OK:
            fprintf(log, " (ok) ");
            break;
        case FUNC_NULL_POINTER_TO_STACK:
            fprintf(log, " (Stack function got null pointer to stack) ");
            break;
        case FUNC_ZERO_CAPACITY:
            fprintf(log, " (Stack constructor got zero capacity) ");
            break;
        case FUNC_NULL_POINTER_TO_VALUE:
            fprintf(log, " (Stack function got zero pointer to value for pop) ");
            break;
        case REPEATED_STACK_CONSTR:
            fprintf(log, " (Attempt to construct stack that already exists) ");
            break;
        case STACK_CHECK:
            fprintf(log, " (Error during checking the stack for integrity) ");
            break;
        case BAD_ALLOC:
            fprintf(log, " (Can't allocate memory) ");
            break;
        case STACK_OVERFLOW:
            fprintf(log, " (Stack is overflowed, can't make push) ");
            break;
        case STACK_EMPTY:
            fprintf(log, " (Stack is empty, can't make pop) ");
            break;
        case SIZE_LARGER_THEN_CAPACITY:
            fprintf(log, " (Stack's size is larger then capacity) ");
            break;
        case BAD_CAPACITY:
            fprintf(log, " (Stack's capacity is under or equal zero) ");
            break;
        case BAD_SIZE:
            fprintf(log, " (Stack's size is under zero) ");
            break;
        case BAD_DATA:
            fprintf(log, " (Something wrong with stack data) ");
            break;
        case BAD_QUANTITY:
            fprintf(log, " (In fact stack has more or less then size elements) ");
            break;
        case BAD_STACK_CANARY:
            fprintf(log, " (Stack canary is spoiled) ");
            break;
        case BAD_DATA_CANARY:
            fprintf(log, " (Data canary is spoiled) ");
            break;
        case BAD_HASH_POINTER_TO_DATA:
            fprintf(log, " (Hash function got null pointer to data) ");
            break;
        case BAD_HASH_POINTER_TO_HASH:
            fprintf(log, " (Hash function got null pointer to hash) ");
            break;
        case BAD_HASH:
            fprintf(log, " (Hash is incorrect) ");
            break;
        case HASH_FUNC:
            fprintf(log, " (Error in StackHash function) ");
            break;
    }
    fclose(log);
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
