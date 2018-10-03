# compiler

CC = g++

# execution flags

CFLAGS = -std=c++11 -Wall -g #-Werror

# Sources (all files ending in .c)

SRCS = $(wildcard *.cpp)

# Make all sources into .o obj files

OBJS = $(SRCS:.c=.o)

DEPS = $(wildcard *.h)


%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: all

all: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Makefile clean

.PHONY: clean 
clean:
	rm -f *.o all

