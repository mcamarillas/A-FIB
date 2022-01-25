TARGET = greedy basics local_search metaheuristic
CXXFLAGS = -ansi -O3 -fpermissive -std=c++17
OBJS = basicsC.o Graph.o greedyC.o State.o local_searchC.o
CPLOBJS = basicsC.o Graph.o greedyC.o State.o local_searchC.o

SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic
GCC = gcc
CCC = g++
CCOPT = -m64 -O -fPIC -fexceptions -DNDEBUG -DIL_STD -std=c++17 -fpermissive -w

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR)

all: ${TARGET}

greedy: greedy.cpp $(OBJS)
	${CCC} ${CXXFLAGS} -o $@ $^

basics: basics.cpp $(OBJS)
	${CCC} ${CXXFLAGS} -o $@ $^

local_search: local_search.cpp $(OBJS)
	${CCC} ${CXXFLAGS} -o $@ $^


metaheuristic: metaheuristic.cpp $(OBJS)
	${CCC} ${CXXFLAGS} -o $@ $^

clean:
	@rm -f *~ *.o ${TARGET} core
