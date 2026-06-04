CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET   = library_app
SRCDIR   = src
SRCS     = $(SRCDIR)/main.cpp $(SRCDIR)/Book.cpp $(SRCDIR)/Member.cpp \
           $(SRCDIR)/Library.cpp $(SRCDIR)/Utils.cpp
OBJS     = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
