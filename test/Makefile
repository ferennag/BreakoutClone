INCLUDEDIR=../include
TEST_SOURCES=$(wildcard *.c)
TEST_OBJECTS=$(TEST_SOURCES:%.c=%.o)
TARGET=tests
MAIN_OBJECTS=$(filter-out ../build/src/main.o, $(wildcard ../build/src/*.o)) $(wildcard ../build/src/**/*.o)

CC=gcc
CHECK_CFLAGS=-Wall -pedantic --std=c11 -ggdb -I$(INCLUDEDIR) -I. -I../lib/include
LDFLAGS=-lSDL2 -lSDL2_image -lm -lcheck -L ../lib

.PHONY: all run clean

all: run

run: $(TARGET)
	./$(TARGET)

build: $(TEST_OBJECTS) $(TARGET)

clean:
	@rm -f *.o
	@rm -f $(TARGET)

$(TARGET): $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) $(MAIN_OBJECTS) $(CHECK_CFLAGS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CHECK_CFLAGS) $(LDFLAGS) -c $< -o $@