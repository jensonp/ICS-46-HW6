CXX      = g++
CXXFLAGS := -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic -fsanitize=address,undefined 

SRCDIR  = src
SRCS    = $(SRCDIR)/main.cpp $(SRCDIR)/bst.cpp $(SRCDIR)/bstree.cpp $(SRCDIR)/avltree.cpp
OBJS    = $(SRCS:.cpp=.o)
TARGET  = hw6

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
