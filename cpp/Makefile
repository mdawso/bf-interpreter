CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = bfi
SRCS = bf-interpreter.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET) clean_objs

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

clean_objs:
	rm -f $(OBJS)

.PHONY: all clean clean_objs
