LIBS = -lnuma
CFLAGS = -Wall
CC = gcc

SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS)) 

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)	-o $@ $< $(LIBS)
