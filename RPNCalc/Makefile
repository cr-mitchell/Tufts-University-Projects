###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Charles Mitchell

# this is needed to have make follow symlinks in dependency lists -- please keep
# it! (but remove this comment)
MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

main.o: main.cpp RPNCalc.o DatumStack.o Datum.o
	$(CXX) $(CXXFLAGS) -c main.cpp

CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o
	$(CXX) $(CXXFLAGS) -o CalcYouLater $^

RPNCalc.o: RPNCalc.h RPNCalc.cpp
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

DatumStack.o: DatumStack.h DatumStack.cpp
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp


unit_test: unit_test_driver.o DatumStack.o Datum.o
	$(CXX) $(CXXFLAGS) $^


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
