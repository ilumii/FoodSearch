food: Main.o Logic.o
	g++ Main.o Logic.o -o food

Main.o: Main.cpp
	g++ -c -std=c++11 Main.cpp

Logic.o: Logic.cpp Logic.h
	g++ -c -std=c++11 Logic.cpp

clean:
	rm *.o food
