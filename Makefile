CXX = clang++
DEBUG ?= 0
CXXFLAGS = --std=c++17 -static

ifeq ($(DEBUG), 1)
	CXXFLAGS += -Og -g3 -DDEBUG
else
	CXXFLAGS += -Ofast -g0 -DNDEBUG
endif

bf_interpreter: bf_interpreter.o bf_opcode.hpp bf_tape.hpp
	$(CXX) $(CXXFLAGS) -o bf_interpreter bf_interpreter.o
