CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = jak_dojade

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean
