#
#
#
OKBIN=ok
LEAKBIN=leak

OKOBJS=ok.o
LEAKOBJS=leak.o impl.o

CXXFLAGS=-c -Wall -std=c++11

all: $(OKBIN) $(LEAKBIN)

valgrind: all
	valgrind --leak-check=yes --tool=memcheck ./leak

$(OKBIN): $(OKOBJS)
	g++ -o $@ $^

$(LEAKBIN): $(LEAKOBJS)
	g++ -o $@ $^

clean:
	rm -rf $(OKOBJS) $(LEAKOBJS) $(OKBIN) $(LEAKBIN) *~
