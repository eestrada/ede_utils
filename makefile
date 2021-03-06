CXX ?= c++
CXXFLAGS ?= -ansi -g -Wall -I . -I inc/

BIN = bin/test.bin
ARGS = 
OBJ_FILES = obj/main.o
DEPS = inc/nullstream.hpp inc/edelist.hpp inc/string.hpp

.PHONY : run bin test clean memcheck

run : bin
	./bin/test.bin

bin : $(BIN)

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -rf obj
	rm -rf bin
	@ echo

memcheck : bin
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(OBJ_FILES) $(DEPS)
	@ echo "Compiling binary"
	@- mkdir -p bin
	$(CXX) -o $@ $(OBJ_FILES) $(CXXFLAGS)
	@ echo

obj/%.o : src/%.cpp $(DEPS)
	@ echo "Creating object file: " $@
	@- mkdir -p obj
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	@ echo
