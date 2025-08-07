# Makefile for building prodcons
CXX       := g++
CXXFLAGS  := -std=c++14 -pthread -Wall -Wextra -O2
TARGET    := prodcons
SRC       := prodcons.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
