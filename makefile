CC = g++ -g
EXE = ass3

$(EXE): flight.o airport.o manager.o flight_manager.o
	$(CC) flight.o airport.o manager.o flight_manager.o -o $(EXE)

flight.o: flight.cpp
	$(CC) -c flight.cpp

airport.o: airport.cpp
	$(CC) -c airport.cpp

manager.o: manager.cpp
	$(CC) -c manager.cpp

flight_manager.o: flight_manager.cpp
	$(CC) -c flight_manager.cpp 

clean: 
	rm -f *.o $(EXE)

leak_check: flight.o airport.o manager.o flight_manager.o
	$(CC) flight.o airport.o manager.o flight_manager.o -o $(EXE)
	valgrind --leak-check=full ./$(EXE)