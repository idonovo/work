

all: *.so

*.so: *.cpp
	g++ *.cpp -fPIC -c
	g++ -shared *.o -o TempControlSystem.so -pthread
	mv TempControlSystem.so ../../SOS/
	
clean:
	-rm -f *.o *.so
	-rm -f ../../SOS/TempControlSystem.so.so
