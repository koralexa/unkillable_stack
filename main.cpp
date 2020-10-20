//
//  main.c
//  unkillable_stack
//
//  Created by Alexandra Korabulina on 06.10.2020.
//

#include <iostream>
#include <stdio.h>

#ifndef DEBUG

#define CHECK_TYPE 3
#include "stack_errors.h"

#undef TYPE
#define TYPE int
#include "stack.h"
#include "stack.cpp"
#undef TYPE

#define TYPE char
#include "stack.h"
#include "stack.cpp"
#undef TYPE

#define TYPE long
#include "stack.h"
#include "stack.cpp"

#endif


#ifdef DEBUG
#include "tests.h"
#endif


int main() {
    
#ifdef DEBUG
    Test1();
    Test2();
    Test3();
    return 0;
#endif
    
#ifndef DEBUG
    struct Stack_int s1;
    s1.size = 0;
    s1.capacity = 0;
    s1.data = NULL;
    StackConstructor(s1, 5);
    StackPush(&s1, 10);
    StackPush(&s1, 11);
    StackPush(&s1, 12);
    StackPush(&s1, 13);
    int x = 0;
    StackPop(&s1, &x);
    std::cout << "Values for Stack_int:" << std::endl;
    std::cout << x << std::endl;
    StackPop(&s1, &x);
    std::cout << x << std::endl;
    StackPop(&s1, &x);
    std::cout << x << std::endl;
    StackPop(&s1, &x);
    std::cout << x << std::endl << std::endl;
    
    struct Stack_long s2;
    s2.size = 0;
    s2.capacity = 0;
    s2.data = NULL;
    StackConstructor(s2, 10);
    StackPush(&s2, 20);
    StackPush(&s2, 28048204930);
    StackPush(&s2, 23892);
    long y = 0;
    StackPop(&s2, &y);
    std::cout << "Values for Stack_long:" << std::endl;
    std::cout << y << std::endl;
    StackPop(&s2, &y);
    std::cout << x << std::endl;
    StackPop(&s2, &y);
    std::cout << x << std::endl;
    
    StackDestructor(&s1);
    StackDestructor(&s2);
#endif
    return 0;
}
