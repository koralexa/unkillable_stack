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
#include <typeinfo> // use .cpp only for STACKDUMP
#include <iostream>
#include <fstream>

//--------------------------------------------------------------------------------

//! Outputs stack info into stack.log file
//!
//! @param [in] thou pointer to stack
#define STACKDUMP(thou) { \
    TYPE poison_t = (TYPE)poison; \
    int check = StackCheck(thou); \
    FILE * log = fopen("stack.log", "a"); \
    fprintf(log, "Stack %s [TYPE = %s]", thou->name, typeid(TYPE).name()); \
    fclose(log); \
    PrintError((enum error)check); \
    log = fopen("stack.log", "a"); \
    fprintf(log, "[%s:%d in function %s()] ", __FILE__, __LINE__, __func__); \
    fprintf(log, "{\n"); \
    fprintf(log, "  size = %d\n", thou->size); \
    fprintf(log, "  capacity = %d\n", thou->capacity); \
    if (CHECK_TYPE > 1) { \
        if (thou->canary1 == good_canary) { \
            fprintf(log, "  stack canary left : ok\n"); \
        } else { \
            fprintf(log, "  stack canary left : error\n"); \
        } \
        if (thou->canary2 == good_canary) { \
            fprintf(log, "  stack canary right : ok\n"); \
        } else { \
            fprintf(log, "  stack canary right : error\n"); \
        } \
        if (*(unsigned long long *)((char *)thou->data - sizeof(unsigned long long)) \
            == good_canary) { \
            fprintf(log, "  data canary left : ok\n"); \
        } else { \
            fprintf(log, "  stack canary left : error\n"); \
        } \
        if (*(unsigned long long *)((char *)thou->data + thou->capacity * sizeof(thou->data[0])) \
            == good_canary) { \
            fprintf(log, "  data canary right : ok\n"); \
        } else { \
            fprintf(log, "  stack canary right : error\n"); \
        } \
    } \
    \
    if (CHECK_TYPE > 2) { \
        unsigned long long h_stack = thou->stack_hash; \
        unsigned long long h_data = thou->data_hash; \
        thou->stack_hash = 0; \
        StackHash((char *)&(thou->canary1), sizeof(struct STACK(TYPE)), &(thou->stack_hash)); \
        if (thou->stack_hash != h_stack) { \
            fprintf(log, "  stack hash : error\n"); \
        } else { \
            fprintf(log, "  stack hash : ok\n"); \
        } \
        char * tmp = (char *)thou->data - sizeof(unsigned long long); \
        StackHash(tmp, 2 * sizeof(unsigned long long) + thou->capacity * sizeof(TYPE), &(thou->data_hash)); \
        if (thou->data_hash != h_data) { \
            fprintf(log, "  data hash : error\n"); \
        } else { \
            fprintf(log, "  data hash : ok\n"); \
        } \
        thou->data_hash = h_data; \
        thou->stack_hash = h_stack; \
    } \
    \
    if (thou->data == errptr) { \
        fprintf(log, "  data = error pointer = (void *)13.\n}\n"); \
    } else if (thou->data == NULL) { \
        fprintf(log, "  data = NULL.\n}\n"); \
    } else { \
        fprintf(log, "  data [%p] {\n", thou->data); \
        int i = 0; \
        fclose(log); \
        std::ofstream fout; \
        fout.open("stack.log", std::ios::app); \
        while (i < thou->capacity) { \
            if (i < thou->size) { \
                fout << "    *[%d] = "; \
            } else { \
                fout << "     [%d] = "; \
            } \
            if (thou->data[i] == poison_t) { \
                fout << "POISON!\n"; \
            } else { \
                fout << thou->data[i] << std::endl; \
            } \
            i++; \
        } \
        fout.close(); \
        log = fopen("stack.log", "a"); \
        if (i == 0) { \
            fprintf(log, "    Stack is empty.\n"); \
        } \
        fprintf(log, "  }\n"); \
        fprintf(log, "}\n\n"); \
    } \
    fclose(log); \
}

//--------------------------------------------------------------------------------

//! Saves stack variable name and calls StackInit()
//!
//! @param [in] s  stack variable
//! @param [in] capacity  capacity for stack
//!
//! @note use macro only for saving variable name, all needed actions for constructor are executet in function StackInit()
#define StackConstructor(s, capacity) { \
    s.name = #s; \
    StackInit(&s, capacity); \
}

//--------------------------------------------------------------------------------

//! Prepares stack for using
//!
//! @param [in] thou  pointer to stack
//! @param [in] capacity capacity for stack
//!
//! @return 0 in case there are no errors, otherwise type of error (see enum error definition in stack_errors.h)
int StackInit(struct STACK(TYPE) * thou, int capacity) {
    if (!thou) {
        return FUNC_NULL_POINTER_TO_STACK;
    }
    if (!capacity) {
        return FUNC_ZERO_CAPACITY;
    }
    
    thou->size = 0;
    thou->capacity = capacity;
    thou->canary1 = good_canary;
    thou->canary2 = good_canary;
    char * tmp = (char *)calloc(2 * sizeof(unsigned long long) + thou->capacity * sizeof(TYPE), sizeof(char));
    if (tmp == NULL) {
        return BAD_ALLOC;
    }
    
    *(unsigned long long *)tmp = good_canary;
    *(unsigned long long *)(tmp + sizeof(unsigned long long) + thou->capacity * sizeof(TYPE)) = good_canary;
    thou->data = (TYPE *)(tmp + sizeof(unsigned long long));
    int i = 0;
    for (i = 0; i < capacity; i++) {
        thou->data[i] = (TYPE)poison;
    }
    
    if (CHECK_TYPE > 2) {
        thou->stack_hash = 0;
        thou->data_hash = 0;
        int hash_res = StackHash(tmp, 2 * sizeof(unsigned long long) + thou->capacity * sizeof(TYPE), &(thou->data_hash));
        if (hash_res != 0) {
            return HASH_FUNC;
        }
        hash_res = StackHash((char *)&(thou->canary1), sizeof(struct STACK(TYPE)), &(thou->stack_hash));
        if (hash_res != 0) {
            return HASH_FUNC;
        }
    }
    
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
    
    if (CHECK_TYPE > 0) {
        int check = StackCheck(thou);
        if (check != 0) {
            STACKDUMP(thou);
            assert(!"Stack destructor check stack error."); // only in debug mode
            // get here only in release mode
            fprintf(stderr, "StackDestructor() got bad stack.\n");
            return STACK_CHECK;
        }
    }
    
    if (thou->size > 0) {
        int i = 0;
        for (i = 0; i < thou->size; i++) {
            thou->data[i] = (TYPE)poison;
        }
    }
    thou->size = 0;
    thou->capacity = 0;
    char * tmp = (char *)thou->data - sizeof(unsigned long long);
    free(tmp);
    thou->data = (TYPE *)errptr;
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
    
    if (CHECK_TYPE > 0) {
        int check = StackCheck(thou);
        if (check != 0) {
            STACKDUMP(thou);
            assert(!"Stack push: check stack error."); // only in debug mode
            // get here only in release mode
            fprintf(stderr, "StackPush() got bad stack.\n");
            return STACK_CHECK;
        }
    }
    
    if (thou->size == thou->capacity) {
        return STACK_OVERFLOW;
    }
    
    // save stack for tansaction rollback
    char * tmp_stack = (char *)calloc(sizeof(struct STACK(TYPE)), 1);
    if (tmp_stack == NULL) {
        return BAD_ALLOC;
    }
    char * tmp_data = (char *)calloc(sizeof(TYPE) * thou->capacity +
                                     2 * sizeof(unsigned long long), 1);
    if (tmp_data == NULL) {
        free(tmp_stack);
        return BAD_ALLOC;
    }
    memcpy(tmp_stack, thou, sizeof(struct STACK(TYPE)));
    memcpy(tmp_data, (char *)(thou->data) - sizeof(unsigned long long),
           sizeof(TYPE) * thou->capacity + 2 * sizeof(unsigned long long));
    
    
    thou->data[thou->size] = value;
    thou->size++;
    
    if (CHECK_TYPE > 2) {
        thou->stack_hash = 0;
        thou->data_hash = 0;
        char * tmp = (char *)thou->data - sizeof(unsigned long long);
        int hash_res = StackHash(tmp, 2 * sizeof(unsigned long long) + thou->capacity * sizeof(TYPE), &(thou->data_hash));
        if (hash_res != 0) {
            memcpy(thou, tmp_stack, sizeof(struct STACK(TYPE)));
            memcpy((char *)(thou->data) - sizeof(unsigned long long), tmp_data,
                   sizeof(TYPE) * thou->capacity + 2 * sizeof(unsigned long long));
            free(tmp_stack);
            free(tmp_data);
            return HASH_FUNC;
        }
        hash_res = StackHash((char *)&(thou->canary1), sizeof(struct STACK(TYPE)), &(thou->stack_hash));
        if (hash_res != 0) {
            memcpy(thou, tmp_stack, sizeof(struct STACK(TYPE)));
            memcpy((char *)(thou->data) - sizeof(unsigned long long), tmp_data,
                   sizeof(TYPE) * thou->capacity + 2 * sizeof(unsigned long long));
            free(tmp_stack);
            free(tmp_data);
            return HASH_FUNC;
        }
    }
    
    if (CHECK_TYPE > 0) {
        int check = StackCheck(thou);
        if (check != 0) {
            STACKDUMP(thou);
            memcpy(thou, tmp_stack, sizeof(struct STACK(TYPE)));
            memcpy((char *)(thou->data) - sizeof(unsigned long long), tmp_data,
                   sizeof(TYPE) * thou->capacity + 2 * sizeof(unsigned long long));
            free(tmp_stack);
            free(tmp_data);
            // assert(!"Stack push: check stack error."); // only in debug mode
            // get here only in release mode
            fprintf(stderr, "StackPush() error. Transaction aborted.\n");
            return STACK_CHECK;
        }
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
    
    if (CHECK_TYPE > 0) {
        int check = StackCheck(thou);
        if (check != 0) {
            STACKDUMP(thou);
            assert(!"Stack pop: check stack error."); // only in debug mode
            // get here only in release mode
            fprintf(stderr, "StackPop() got bad stack.\n");
            return STACK_CHECK;
        }
    }
    
    if (thou->size == 0) {
        return STACK_EMPTY;
    }
    
    // save stack for tansaction rollback
    char * tmp_stack = (char *)calloc(sizeof(struct STACK(TYPE)), 1);
    if (tmp_stack == NULL) {
        return BAD_ALLOC;
    }
    char * tmp_data = (char *)calloc(sizeof(TYPE) * thou->capacity +
                                     2 * sizeof(unsigned long long), 1);
    if (tmp_data == NULL) {
        free(tmp_stack);
        return BAD_ALLOC;
    }
    memcpy(tmp_stack, thou, sizeof(struct STACK(TYPE)));
    memcpy(tmp_data, (char *)(thou->data) - sizeof(unsigned long long),
           sizeof(TYPE) * thou->capacity + 2 * sizeof(unsigned long long));
    
    *value = thou->data[thou->size - 1];
    thou->data[thou->size - 1] = (TYPE)poison;
    thou->size--;
    
    if (CHECK_TYPE > 2) {
        thou->stack_hash = 0;
        thou->data_hash = 0;
        char * tmp = (char *)thou->data - sizeof(unsigned long long);
        int hash_res = StackHash(tmp, 2 * sizeof(unsigned long long) + thou->capacity * sizeof(TYPE), &(thou->data_hash));
        if (hash_res != 0) {
            memcpy(thou, tmp_stack, sizeof(struct STACK(TYPE)));
            memcpy((char *)(thou->data) - sizeof(unsigned long long), tmp_data,
                   sizeof(TYPE) * thou->capacity + 2 * sizeof(unsigned long long));
            free(tmp_stack);
            free(tmp_data);
            return HASH_FUNC;
        }
        hash_res = StackHash((char *)&(thou->canary1), sizeof(struct STACK(TYPE)), &(thou->stack_hash));
        if (hash_res != 0) {
            memcpy(thou, tmp_stack, sizeof(struct STACK(TYPE)));
            memcpy((char *)(thou->data) - sizeof(unsigned long long), tmp_data,
                   sizeof(TYPE) * thou->capacity + 2 * sizeof(unsigned long long));
            free(tmp_stack);
            free(tmp_data);
            return HASH_FUNC;
        }
    }
    
    if (CHECK_TYPE > 0) {
        int check = StackCheck(thou);
        if (check != 0) {
            memcpy(thou, tmp_stack, sizeof(struct STACK(TYPE)));
            memcpy((char *)(thou->data) - sizeof(unsigned long long), tmp_data,
                   sizeof(TYPE) * thou->capacity + 2 * sizeof(unsigned long long));
            free(tmp_stack);
            free(tmp_data);
            STACKDUMP(thou);
            assert(!"Stack pop: check stack error."); // only in debug mode
            // get here only in release mode
            fprintf(stderr, "StackPop() error. Transaction aborted.\n");
            return STACK_CHECK;
        }
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
    
    if (thou->capacity < 0) {
        return BAD_CAPACITY;
    }
    if (thou->size < 0) {
        return BAD_SIZE;
    }
    if (thou->size > thou->capacity) {
        return SIZE_LARGER_THEN_CAPACITY;
    }
    if ((thou->capacity != 0) && ((thou->data == NULL) || ((void *)thou->data == errptr))) {
        return BAD_DATA;
    }
    
    if (CHECK_TYPE > 1) {
        if (thou->canary1 != good_canary) {
            return BAD_STACK_CANARY;
        }
        if (thou->canary2 != good_canary) {
            return BAD_STACK_CANARY;
        }
        if (*(unsigned long long *)((char *)thou->data - sizeof(unsigned long long))
            != good_canary) {
            return BAD_DATA_CANARY;
        }
        if (*(unsigned long long *)((char *)thou->data + thou->capacity * sizeof(TYPE))
            != good_canary) {
            return BAD_DATA_CANARY;
        }
    }
    
    if (CHECK_TYPE > 2) {
        unsigned long long h_stack = thou->stack_hash;
        unsigned long long h_data = thou->data_hash;
        thou->stack_hash = 0;
        int hash_res = StackHash((char *)&(thou->canary1), sizeof(struct STACK(TYPE)), &(thou->stack_hash));
        if (hash_res != 0) {
            thou->data_hash = h_data;
            thou->stack_hash = h_stack;
            return HASH_FUNC;
        }
        if (thou->stack_hash != h_stack) {
            thou->data_hash = h_data;
            thou->stack_hash = h_stack;
            return BAD_HASH;
        }
        char * tmp = (char *)thou->data - sizeof(unsigned long long);
        hash_res = StackHash(tmp, 2 * sizeof(unsigned long long) + thou->capacity * sizeof(TYPE), &(thou->data_hash));
        if (hash_res != 0) {
            thou->data_hash = h_data;
            thou->stack_hash = h_stack;
            return HASH_FUNC;
        }
        if (thou->data_hash != h_data) {
            thou->data_hash = h_data;
            thou->stack_hash = h_stack;
            return BAD_HASH;
        }
        thou->data_hash = h_data;
        thou->stack_hash = h_stack;
    }
    
    
    int i = 0;
    while ((thou->data[i] != (TYPE)poison) && (i < thou->capacity)) {
        i++;
    }
    if (i != thou->size) {
        return BAD_QUANTITY;
    }
    
    return OK;
}

//--------------------------------------------------------------------------------

