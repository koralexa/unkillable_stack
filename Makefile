CFLAGS = -Wall -Wextra
DEBUGFLAGS = -Wall -Wextra -g -DDEBUG

FILES = main.cpp
OTHER = stack.cpp
HEADERS = stack_errors.h stack.h 
TESTS = tests.h tests.cpp

all: $(FILES) $(HEADERS)
	g++ $(CFLAGS) -o main main.cpp

debug: $(FILES) $(HEADERFILES) $(TESTS)
	g++ $(DEBUGFLAGS) -o main main.cpp tests.cpp

clean: 
	rm main