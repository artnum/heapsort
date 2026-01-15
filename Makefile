DEBUG ?= 1
ifeq ($(DEBUG), 1)
CFLAGS=-ggdb -Wall -Wextra -pedantic
else
CFLAGS=-O2 -DNDEBUG -march=native
endif
NAME=heapsort.a
CC=gcc
AR=ar
RM=rm -Rf

all: $(NAME) test

$(NAME): build/heapsort.o
	$(AR) rcs $@ $^

build/heapsort.o: src/heapsort.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME) src/test.c
	$(CC) $(CFLAGS) $^ -o $@ -L./ -l:$(NAME)

clean:
	$(RM) build/heapsort.o build/test.o heapsort.a test




