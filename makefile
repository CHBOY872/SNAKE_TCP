CC=gcc
CFLAGS=-Wall -ansi -g

CPP=g++
CPPFLAGS=-Wall -ansi -g

CSRCMODULES=$(shell find . -name '*.c' | grep -v 'main.c')
CHEDMODULES=$(CSRCMODULES:.c=.h)
COBJMODULES=$(CSRCMODULES:.c=.o)

CPPSRCMODULES=$(shell find . -name '*.cpp' | grep -v 'main.cpp')
CPPHEDMODULES=$(CPPSRCMODULES:.cpp=.hpp)
CPPOBJMODULES=$(CPPSRCMODULES:.cpp=.o)

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -c -o $@

%.o: %.cpp %.hpp
	$(CPP) $(CPPFLAGS) $< -c -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(CPPSRCMODULES) $(CSRCMODULES)
	$(CC) -MM $^ > $@

main: main.cpp $(COBJMODULES) $(CPPOBJMODULES)
	$(CPP) $(CPPFLAGS) $^ -o $@

clean:
	find . -name '*.o' -delete

all:
	make main
	make clean