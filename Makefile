all : cppLLRBTree

cppLLRBTree: main.o LLRBTree.o LLRBNode.o socket.o
	g++  -g main.o LLRBTree.o LLRBNode.o socket.o -o cppLLRBTree

main.o: main.cpp LLRBTree.h LLRBNode.h
	g++ -c -g main.cpp

LLRBTree.o: LLRBTree.cpp LLRBNode.h
	g++ -c -g LLRBTree.cpp

LLRBNode.o: LLRBNode.cpp
	g++ -c -g LLRBNode.cpp

socket.o: socket.cpp
	g++ -c -g socket.cpp

clean:
	rm *.o cppLLRBTree
