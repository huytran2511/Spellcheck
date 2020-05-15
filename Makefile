CC=gcc
CCFLAGS=-std=c11 -g

spellcheck : dictionary.o spellcheck.o
	$(CXX) $(CXXFLAGS) -o dictionary $^

dictionary.o : dictionary.h dictionary.c

spellcheck.o : dictionary.h spellcheck.c

clean :
	rm -fr spellcheck $(OBJS) *.o

