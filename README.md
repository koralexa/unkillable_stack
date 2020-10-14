# Unkillable stack
This project is created to provide the ability to use a software-implemented reliable stack.

## Description

Now there are only base stack functions implemeted: constructor, destructor, push and pop. Stay tuned for coming versions. 
Stack protection is provided (dump, canaries and hash function).
To use stack you must include to your program stack_errors.h, define TYPE, include stack.h and stack.cpp and define CHECK_TYPE:
0 - no checks
1 - use of dump
2 - use of dump and canaries
3 - use of dump, canaries and hash
There is a simple example of using stack in main.cpp.

## Getting Started

### Installing

* Download the project from GitHub or clone it by
```
 git clone https://github.com/koralexa/unkillable_stack.git
```

### Executing program

* Go to the project folder through your terminal.
* To execute example run
```
make
```
* Then run
```
./main
```

* To execute example  in debug mode run
```
make debug
```
* Then run
```
./main
```

* To delete executable files run
```
make clean
```
