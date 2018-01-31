

CC=g++
CFLAGS=-g -Wall -O3
CPPFLAGS=$(CFLAGS) -std=c++11
LINKFLAGS=-pthread


SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

EXECUTABLE=threadtest

.cpp.o:
	$(CC) -o $@ $(CPPFLAGS) -c $<

all: $(OBJS)
	$(CC) $(LINKFLAGS)  -o $(EXECUTABLE) $(OBJS) 

clean:
	rm -fr $(OBJS) $(EXECUTABLE)

