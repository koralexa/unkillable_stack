//
//  stack.h
//  unkillable_stack
//
//  Created by Alexandra Korabulina on 06.10.2020.
//

//--------------------------------------------------------------------------------

#define CAT(x) Stack_##x
#define STACK(x) CAT(x)

struct STACK(TYPE) {
    unsigned long long canary1;
    int size;
    int capacity;
    const char * name;
    TYPE * data;
    unsigned long long stack_hash;
    unsigned long long data_hash;
    unsigned long long canary2;
};

//--------------------------------------------------------------------------------

int StackInit(struct STACK(TYPE) * thou, int capacity);

int StackDestructor (struct STACK(TYPE) * thou);

int StackPush(struct STACK(TYPE) * thou, TYPE value);

int StackPop(struct STACK(TYPE) * thou, TYPE * value);

int StackCheck(struct STACK(TYPE) * thou);

void StackDump(struct STACK(TYPE) * thou);

//--------------------------------------------------------------------------------

