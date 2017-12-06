PRODUCT=StateTest

CFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -ISolarClock -Itest

SOURCES=$(wildcard SolarClock/SolarClock.cpp) \
        $(wildcard test/*.cpp)

HEADERS=$(wildcard SolarClock/*.h) \
        $(wildcard test/*.h)

TEST_LIBS=-lgtest -lgtest_main -lgmock -lgmock_main -pthread

CC=g++

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS) Makefile
	@$(CC) $(CFLAGS) $(SOURCES) -o $@ $(TEST_LIBS)

clean:
	@rm -rf $(PRODUCT)

test: $(PRODUCT)
	@./$(PRODUCT)