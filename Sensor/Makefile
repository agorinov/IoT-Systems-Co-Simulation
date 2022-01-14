program: main.cpp Sensor.o Person.o Utility.o
	g++ -o $@ main.cpp Sensor.o Person.o Utility.o

Sensor.o: Sensor.cpp
	g++ -o $@ -c Sensor.cpp

Person.o: Person.cpp
	g++ -o $@ -c Person.cpp

Utility.o: Utility.cpp
	g++ -o $@ -c Utility.cpp

clean:
	rm -rf *.o
	rm -rf program

cleandata:
	rm -rf *.dat
	rm -rf *.txt
