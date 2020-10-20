CXX = g++
CFLAGS = -Wall -Wextra
DEBUGFLAGS = -Wall -Wextra -g -DDEBUG

FILES = main.cpp
DEBUGFILES = tests.cpp
OTHER = stack.cpp
HEADERS = stack_errors.h stack.h 
TESTS = tests.h tests.cpp

all: $(FILES) $(HEADERS) $(OTHER)
	$(CXX) $(CFLAGS) -o main $(FILES)

debug: $(FILES) $(HEADERS) $(OTHER) $(TESTS)
	$(CXX) $(DEBUGFLAGS) -o main $(FILES) $(DEBUGFILES)

clean: 
	rm main