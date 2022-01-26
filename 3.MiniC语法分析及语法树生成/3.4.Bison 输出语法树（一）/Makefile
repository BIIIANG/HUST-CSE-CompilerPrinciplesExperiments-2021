all: minic
LLVM_CONFIG = llvm-config
LLVM_CXXFLAGS = $(shell $(LLVM_CONFIG) --cxxflags)

OBJS = parser.o \
		token.o  \
		astnode.o \
		main.o \

astnode.cpp: astnode.h

parser.cpp: parser.y
	bison -d parser.y -o $@

token.cpp: token.l parser.hpp 
	flex -o $@ token.l

%.o: %.cpp
	g++  -o $@ $< $(LLVM_CXXFLAGS) -lpthread -ldl -c 

minic: $(OBJS)
	g++ -o $@ $(OBJS) $(LLVM_CXXFLAGS) -lfl -lstdc++  -lpthread -ldl

clean:
	$(RM) -rf $(OBJS) minic