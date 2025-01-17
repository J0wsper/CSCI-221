CFLAGS = -g -Wall -Wextra -O0

lab10_test: lab10_main.o lab10.o
	g++ $(CFLAGS) -o lab10_test lab10_main.o lab10.o

lab10_main.o: lab10_main.cpp lab10.hpp
	g++ $(CFLAGS) -c lab10_main.cpp

lab10.o: lab10.cpp lab10.hpp
	g++ $(CFLAGS) -c lab10.cpp

clean:
	del lab10_main.o lab10_test.exe lab10.o
 