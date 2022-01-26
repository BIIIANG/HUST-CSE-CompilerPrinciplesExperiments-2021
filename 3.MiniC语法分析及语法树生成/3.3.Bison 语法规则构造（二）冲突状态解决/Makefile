all: minic

OBJS =  parser.o \
		token.o  \
		main.o \

parser.cpp: parser.y
	bison -d -v parser.y -o $@

token.cpp: token.l parser.hpp 
	flex -o $@ token.l

%.o: %.cpp
	g++  -o $@ $<  -lpthread -ldl -c 

minic: $(OBJS)
	g++ -o $@ $(OBJS)  -lfl -lstdc++  -lpthread -ldl

clean:
	$(RM) -rf $(OBJS) minic