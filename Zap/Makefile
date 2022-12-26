#########################################################
#             PROJECT 3: Zap Makefile                   #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

main.o: main.cpp HuffmanCoder.o
	$(CXX) $(CXXFLAGS) -c main.cpp

zap: main.o HuffmanCoder.o HuffmanTreeNode.o BinaryIO.o
	$(CXX) $(CXXFLAGS) -o zap $^

HuffmanCoder.o: HuffmanCoder.cpp HuffmanCoder.h 
	$(CXX) $(CXXFLAGS) -c HuffmanCoder.cpp


unit_test: unit_test_driver.o HuffmanCoder.o
	$(CXX) $(CXXFLAGS) $^


provide: provide comp15 proj3_zap README Makefile unit_tests.h main.cpp \
		 HuffmanCoder.h HuffmanCoder.cpp testmain.cpp

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out