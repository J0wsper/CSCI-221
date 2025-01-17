CFLAGS = -g -Wall -Wextra -O0

lab9_test: lab9_main.o lab9.o
	g++ $(CFLAGS) -o lab9_test lab9_main.o lab9.o

lab9_main.o: lab9_main.cpp lab9.hpp
	g++ $(CFLAGS) -c lab9_main.cpp

lab9.o: lab9.cpp lab9.hpp
	g++ $(CFLAGS) -c lab9.cpp

clean:
	del lab9_main.o lab9_test.exe lab9.o
 