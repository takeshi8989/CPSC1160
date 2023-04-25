# CPSC 1160 by Gladys Monagan
# Do not submit and do post anywhere.

.PHONY: all clean remove test

CXX = g++

#DEBUG  = -g

VERSION = -std=c++17

CFLAGS = -pedantic -Wall -Wextra $(DEBUG) $(VERSION)

LFLAGS = $(DEBUG) $(VERSION)

SRC = llist

INCS = $(SRC).h  \
	$(SRC)_utils.h 

SRCS = $(SRC).cpp \
	$(SRC)_utils.cpp 

OBJS = $(SRCS:.cpp=.o)

# To make an object from source
%.o:%.cpp $(INCS)
	$(CXX) $(CFLAGS) -c $< -o $@

# a main program that runs with doctest
UNITTEST = unittest_$(SRC)

# a main that produces a main executable without doctest
TEST_PROG = test_$(SRC)

all: $(SRCS) $(UNITTEST)

test: $(SRCS) $(TEST_PROG)

$(UNITTEST).o : $(INCS) $(UNITTEST).cpp
	$(CXX) $(CFLAGS) -c $(UNITTEST).cpp -o $@

$(UNITTEST) : $(OBJS)  $(UNITTEST).o
	$(CXX) $(LFLAGS) $^ -o $@

$(TEST_PROG).o : $(INCS) $(TEST_PROG).cpp
	$(CXX) $(CFLAGS) -c $(TEST_PROG).cpp -o $@

$(TEST_PROG) : $(OBJS) $(TEST_PROG).o
	$(CXX) $(LFLAGS) $^ -o $@

# for Windows
clean:
	del $(UNITTEST).exe $(TEST_PROG).exe *.o  /Q
	@echo clean done

# for UNIX / Linux 
remove:
	\rm -f $(UNITTEST) $(TEST_PROG) *.o
	@echo clean done

# © 2022 Gladys Monagan 
