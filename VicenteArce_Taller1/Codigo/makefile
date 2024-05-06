FLAGS = -O2

all: main testAStarAlgorithm testHeap testPairInt testState

main: AStarAlgorithm.o Heap.o PairInt.o State.o main.cpp
	g++ ${FLAGS} AStarAlgorithm.o Heap.o PairInt.o State.o main.cpp -o main 

AStarAlgorithm.o: AStarAlgorithm.cpp AStarAlgorithm.h
	g++ ${FLAGS} -c AStarAlgorithm.cpp

Heap.o: Heap.cpp Heap.h
	g++ ${FLAGS} -c Heap.cpp

PairInt.o: PairInt.cpp PairInt.h
	g++ ${FLAGS} -c PairInt.cpp

State.o: State.cpp State.h
	g++ ${FLAGS} -c State.cpp

testAStarAlgorithm: AStarAlgorithm.o Heap.o PairInt.o State.o
		g++ ${FLAGS} AStarAlgorithm.o Heap.o PairInt.o State.o testAStarAlgorithm.cpp -o testAStarAlgorithm

testHeap: Heap.o PairInt.o State.o testHeap.cpp
		g++ ${FLAGS} Heap.o PairInt.o State.o testHeap.cpp -o testHeap

testPairInt: PairInt.o testPairInt.cpp
		g++ ${FLAGS} PairInt.o testPairInt.cpp -o testPairInt

testState: State.o PairInt.o testState.cpp
		g++ ${FLAGS} State.o PairInt.o testState.cpp -o testState

clean:
	rm -rf *.o main testAStarAlgorithm testHeap testPairInt testState