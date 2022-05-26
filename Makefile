# Compiler
CXX = gcc

# Compiler flags (including debug info)
CXXFLAGS = -std=c99 -lm -Wall -Werror -g3

assembler : assembler.c
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY : clean
clean: 
	rm assembler