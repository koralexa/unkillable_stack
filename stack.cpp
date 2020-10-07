//
//  stack.c
//  unkillable_stack
//
//  Created by Alexandra Korabulina on 06.10.2020.
//

#include "stack_errors.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <typeinfo> // use .cpp only for StackDump
#include <iostream>

//--------------------------------------------------------------------------------

//! Outputs stack info into stderr
//!
//! @param [in] thou pointer to stack
void StackDump(struct STACK(TYPE) * thou) {
    int check = StackCheck(thou);
    fprintf(stderr, "Stack [TYPE = %s]", typeid(TYPE).name());
    PrintError((enum error)check);
    fprintf(stderr, "{\n");
    fprintf(stderr, "  size = %d\n", thou->size);
    fprintf(stderr, "  capacity = %d\n", thou->capacity);
    
    if (thou->data == errptr) {
        fprintf(stderr, "  data = error pointer = (void *)13.\n}\n");
        return;
    }
    fprintf(stderr, "  data {\n");
    struct ELEM(TYPE) * tmp = thou->data;
    int i = 0;
    while ((tmp != NULL) && (i <= thou->size)) {
        fprintf(stderr, "    [%d] = ", i);
        std::cerr << tmp->value << std::endl;
        tmp = tmp->next;
        i++;
    }
    if (i == 0) {
        fprintf(stderr, "    Stack is empty.\n  }\n}\n");
        return;
    }
    fprintf(stderr, "  }\n");
    if (i < thou->size) {
        fprintf(stderr, "    ATTENTION: in fact stack has less then size elements.\n");
    }
    if ((i == thou->size) && (tmp != NULL)) {
        fprintf(stderr, "    ATTENTION: in fact stack has more then size elements.\n");
    }
        
    fprintf(stderr, "}\n");
}

//--------------------------------------------------------------------------------

//! Prepares stack for using
//!
//! @param [in] thou  pointer to stack
//! @param [in] capacity capacity for stack
//!
//! @return 0 in case there are no errors, otherwise type of error (see enum error definition in stack_errors.h)
int StackConstructor(struct STACK(TYPE) * thou, int capacity) {
    if (!thou) {
        return FUNC_NULL_POINTER_TO_STACK;
    }
    if (!capacity) {
        return FUNC_ZERO_CAPACITY;
    }
    
    if ((thou->capacity) || (thou->size) ||
        ((thou->data != NULL) && ((void *)thou->data != errptr))) {
        return REPEATED_STACK_CONSTR;
    }
    
    thou->size = 0;
    thou->capacity = capacity;
    thou->data = NULL;
    return OK;
}

//--------------------------------------------------------------------------------

//! Destructs stack
//!
//! @param [in] thou  pointer to stack
//!
//! @return 0 in case there are no errors, otherwise type of error (see enum error definition in stack_errors.h)
int StackDestructor (struct STACK(TYPE) * thou) {
    if (!thou) {
        return FUNC_NULL_POINTER_TO_STACK;
    }
    
    int check = StackCheck(thou);
    if (check != 0) {
        StackDump(thou);
        assert(!"Stack destructor check stack error."); // only in debug mode
        // get here only in release mode
        fprintf(stderr, "StackDestructor() got bad stack.");
        return STACK_CHECK;
    }
    
    struct ELEM(TYPE) * tmp = thou->data;
    if (thou->size > 0) {
        int i = 0; for (i = 0; i < thou->size; i++) {
            thou->data = tmp->next;
            free(tmp);
            tmp = thou->data;
        }
    }
    thou->size = 0;
    thou->capacity = 0;
    thou->data = (struct ELEM(TYPE) *)errptr;
    return OK;
}

//--------------------------------------------------------------------------------

//! Pushes element to the stack top
//!
//! @param [in] thou  pointer to stack
//! @param [in] value element to push
//!
//! @return 0 in case there are no errors, otherwise type of error (see enum error definition in stack_errors.h)
int StackPush(struct STACK(TYPE) * thou, TYPE value) {
    if (!thou) {
        return FUNC_NULL_POINTER_TO_STACK;
    }
    
    int check = StackCheck(thou);
    if (check != 0) {
        StackDump(thou);
        assert(!"Stack push: check stack error."); // only in debug mode
        // get here only in release mode
        fprintf(stderr, "StackPush() got bad stack.");
        return STACK_CHECK;
    }
    
    if (thou->size == thou->capacity) {
        return STACK_OVERFLOW;
    }
    
    struct ELEM(TYPE) * tmp = (struct ELEM(TYPE) *)calloc(1, sizeof(struct ELEM(TYPE)));
    if (!tmp) {
        return BAD_ALLOC;
    }
    tmp->value = value;
    tmp->next = thou->data;
    thou->data = tmp;
    thou->size++;
    
    check = StackCheck(thou);
    if (check != 0) {
        StackDump(thou);
        assert(!"Stack push: check stack error."); // only in debug mode
        // get here only in release mode
        fprintf(stderr, "StackPush() got bad stack.");
        return STACK_CHECK;
    }
    
    return OK;
}

//--------------------------------------------------------------------------------

//! Pops elements from the stack top
//!
//! @param [in] thou  pointer to stack
//! @param [out] value pointer to element for saving
//!
//! @return 0 in case there are no errors, otherwise type of error (see enum error definition in stack_errors.h)
int StackPop(struct STACK(TYPE) * thou, TYPE * value) {
    if (!thou) {
        return FUNC_NULL_POINTER_TO_STACK;
    }
    if (!value) {
        return FUNC_NULL_POINTER_TO_VALUE;
    }
    
    int check = StackCheck(thou);
    if (check != 0) {
        StackDump(thou);
        assert(!"Stack pop: check stack error."); // only in debug mode
        // get here only in release mode
        fprintf(stderr, "StackPop() got bad stack.");
        return STACK_CHECK;
    }
    
    if (thou->size == 0) {
        return STACK_EMPTY;
    }
    
    struct ELEM(TYPE) * tmp = thou->data;
    thou->data = thou->data->next;
    *value = tmp->value;
    free(tmp);
    thou->size--;
    
    check = StackCheck(thou);
    if (check != 0) {
        StackDump(thou);
        assert(!"Stack pop: check stack error."); // only in debug mode
        // get here only in release mode
        fprintf(stderr, "StackPop() got bad stack.");
        return STACK_CHECK;
    }
    
    return OK;
}

//--------------------------------------------------------------------------------

//! Checks if stack is correct
//!
//! @param [in] thou  pointer to stack
//!
//! @return 0 in case stack is correct, otherwise type of error (see enum error definition in stack_errors.h)
int StackCheck(struct STACK(TYPE) * thou) {
    if (!thou) {
        return FUNC_NULL_POINTER_TO_STACK;
    }
    
    if (thou->capacity <= 0) {
        return BAD_CAPACITY;
    }
    if (thou->size < 0) {
        return BAD_SIZE;
    }
    if (thou->size > thou->capacity) {
        return SIZE_LARGER_THEN_CAPACITY;
    }
    if ((thou->size == 0) && (thou->data != NULL) && ((void *)thou->data != errptr)) {
        return BAD_DATA;
    }
    
    int i = 0;
    struct ELEM(TYPE) * tmp = thou->data;
    while (tmp != NULL) {
        tmp = tmp->next;
        i++;
    }
    if (i != thou->size) {
        return BAD_QUANTITY;
    }
    
    return OK;
}

//--------------------------------------------------------------------------------
