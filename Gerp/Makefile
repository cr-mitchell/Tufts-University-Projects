
#########################################################
#             PROJECT 4: Gerp Makefile                   #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -O2
LDFLAGS  = -g3 



gerp: process.o values.o FSTreeTraversal.o DirNode.o FSTree.o stringProcessing.o main.o
	$(CXX) $(CXXFLAGS) -o gerp $^

vals: values.o stringProcessing.o main.o
	$(CXX) $(CXXFLAGS) -o vals $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

process.o: process.h process.cpp FSTreeTraversal.o
	$(CXX) $(CXXFLAGS) -c process.cpp

values.o: values.h values.cpp 
	$(CXX) $(CXXFLAGS) -c values.cpp

keys.o: keys.h keys.cpp 
	$(CXX) $(CXXFLAGS) -c keys.cpp

runtree: FSTreeTraversal.o
	$(CXX) $(CXXFLAGS) -o runtree FSTreeTraversal.o DirNode.o FSTree.o

stringProcessing.o: stringProcessing.cpp stringProcessing.h 
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

FSTreeTraversal.o: FSTreeTraversal.cpp FSTreeTraversal.h 
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp

unit_test: unit_test_driver.o stringProcessing.o
	$(CXX) $(CXXFLAGS) $^


provide: provide comp15 proj4_gerp README Makefile main.cpp process.cpp \
	process.h values.cpp values.h FSTreeTraversal.cpp FSTreeTraversal.h \
	DirNode.h FSTree.h stringProcessing.h stringProcessing.cpp ourSorted.txt \ 
	refSorted.txt banana_apple.txt sentences.txt

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm -f process.o values.o main.o stringProcessing.o FSTreeTraversal.o gerp \
	runtree vals
	