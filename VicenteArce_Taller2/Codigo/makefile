FLAGS = -O2

all: main testClique testMenu

main: Clique.o Menu.o main.cpp
	g++ ${FLAGS} Clique.o Menu.o main.cpp -o main

Clique.o: Clique.cpp Clique.h
	g++ ${FLAGS} -c Clique.cpp

Menu.o: Menu.cpp Menu.h
	g++ ${FLAGS} -c Menu.cpp

testClique: Clique.o testClique.cpp
	g++ ${FLAGS} Clique.o testClique.cpp -o testClique

testMenu: Menu.o Clique.o testMenu.cpp
	g++ ${FLAGS} Menu.o Clique.o testMenu.cpp -o testMenu

clean:
	rm -rf *.o main testClique testMenu