//
//  stack.h
//  unkillable_stack
//
//  Created by Alexandra Korabulina on 06.10.2020.
//

//--------------------------------------------------------------------------------

#define CAT1(x) Stack_##x
#define CAT2(x) Stack_elem_##x
#define STACK(x) CAT1(x)
#define ELEM(x) CAT2(x)

struct ELEM(TYPE) {
    TYPE value;
    struct ELEM(TYPE) * next;
};

struct STACK(TYPE) {
    int size;
    int capacity;
    struct ELEM(TYPE) * data;
};

//--------------------------------------------------------------------------------

int StackConstructor(struct STACK(TYPE) * thou, int capacity);

int StackDestructor (struct STACK(TYPE) * thou);

int StackPush(struct STACK(TYPE) * thou, TYPE value);

int StackPop(struct STACK(TYPE) * thou, TYPE * value);

int StackCheck(struct STACK(TYPE) * thou);

void StackDump(struct STACK(TYPE) * thou);

void PrintError(enum error err);

//--------------------------------------------------------------------------------

