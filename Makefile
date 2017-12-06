PRODUCT=StateTest

CFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -ISolarClock -Itest

SOURCES=$(wildcard SolarClock/*.cpp) \
        $(wildcard test/*.cpp)

HEADERS=$(wildcard SolarClock/*.h) \
        $(wildcard test/*.h)

TEST_LIBS=-lgtest -lgmock -lgmock_main -lpthread

CC=g++

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS) Makefile
	@$(CC) $(CFLAGS) $(SOURCES) -o $@ $(TEST_LIBS)

clean:
	@rm -rf $(PRODUCT)

test: $(PRODUCT)
	@./$(PRODUCT)
