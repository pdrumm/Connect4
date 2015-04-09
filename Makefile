connect4: main.o connect4.o
	g++ -o connect4 main.o connect4.o

main.o: main.cpp
	g++ -c main.cpp

connect4.o: connect4.cpp C4Col.h C4Board.h
	g++ -c connect4.cpp

clean:
	rm connect4 *.o
