
all: compile
	g++ *.o -o test.exe

compile:
	g++ -c *.cpp
clean:
	rm *.o test	
