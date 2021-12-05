program: main.cpp Sensor.o
	g++ -o $@ main.cpp Sensor.o

Sensor.o: Sensor.cpp
	g++ -o $@ -c Sensor.cpp

clean:
	rm -rf *.o
	rm -rf program

cleandata:
	rm -rf *.dat
