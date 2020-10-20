//
//  tests.cpp
//  
//
//  Created by Alexandra Korabulina on 12.10.2020.
//

#include "tests.h"
#include <stdio.h>

//--------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0;37m"

//--------------------------------------------------------------------------------

void Test1() {
    struct Stack_int s;
    s.size = 0;
    s.capacity = 0;
    s.data = NULL;
    StackConstructor(s, 1);
    if (StackPush(&s, 1) != 0) {
        std::cout << "Test1: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (StackPush(&s, 1) == 0) {
        std::cout << "Test1: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    int x = 0;
    if (StackPop(&s, &x) != 0) {
        std::cout << "Test1: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (x != 1) {
        std::cout << "Test1: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (StackDestructor(&s) != 0) {
        std::cout << "Test1: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test1: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test2() {
    struct Stack_char s;
    s.size = 0;
    s.capacity = 0;
    s.data = NULL;
    StackConstructor(s, 5);
    if (StackPush(&s, 'a') != 0) {
        std::cout << "Test2: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    char x = 0;
    if (StackPop(&s, &x) != 0) {
        std::cout << "Test2: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (x != 'a') {
        std::cout << "Test2: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (StackPush(&s, 's') != 0) {
        std::cout << "Test2: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (StackPop(&s, &x) != 0) {
        std::cout << "Test2: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (x != 's') {
        std::cout << "Test2: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (StackDestructor(&s) != 0) {
        std::cout << "Test2: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test2: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test3() {
    struct Stack_long s;
    s.size = 0;
    s.capacity = 0;
    s.data = NULL;
    StackConstructor(s, 1);
    if (StackPush(&s, 2393849) != 0) {
        std::cout << "Test3: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    long x = 0;
    if (StackPop(&s, &x) != 0) {
        std::cout << "Test3: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (x != 2393849) {
        std::cout << "Test3: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (StackPop(&s, &x) == 0) {
        std::cout << "Test3: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    if (StackDestructor(&s) != 0) {
        std::cout << "Test3: " << RED << "ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test3: " << GREEN << "PASSED" << WHITE << std::endl;
}
