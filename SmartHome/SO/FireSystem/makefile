

all: *.so

*.so: *.cpp
	g++ *.cpp -fPIC -c
	g++ -shared *.o -o FireSystemCreator.so -pthread
	mv FireSystemCreator.so ../../SOS/
	
clean:
	-rm -f *.o *.so
	-rm -f ../../SOS/FireSystemCreator.so
