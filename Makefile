CXX      = g++
CXXFLAGS = -pedantic-errors -std=c++11 -Wall -Wextra -Iinclude
SRCS     = $(wildcard src/*.cpp)
OBJS     = $(SRCS:.cpp=.o)
TARGET   = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

asan: CXXFLAGS += -fsanitize=address,undefined -g
asan: clean all

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run asan
