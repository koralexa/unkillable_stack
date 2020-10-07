//
//  main.c
//  unkillable_stack
//
//  Created by Alexandra Korabulina on 06.10.2020.
//

#include <stdio.h>

#include "stack_errors.h"

#undef TYPE
#define TYPE int
#include "stack.h"
#include "stack.cpp"
#undef TYPE

#define TYPE double
#include "stack.h"
#include "stack.cpp"

int main() {
    struct Stack_int s1;
    s1.data = NULL;
    StackConstructor(&s1, 5);
    StackPush(&s1, 10);
    StackPush(&s1, 11);
    StackPush(&s1, 12);
    StackPush(&s1, 13);
    StackDump((&s1));
    int x;
    StackPop(&s1, &x);
    
    struct Stack_double s2;
    StackConstructor(&s2, 10);
    StackPush(&s2, 5.0);
    StackPush(&s2, 0.2378);
    StackPush(&s2, 3792.0);
    StackPush(&s2, 1389.2);
    StackDump((&s2));
    
    StackDestructor(&s1);
    StackDestructor(&s2);
    return 0;
}
