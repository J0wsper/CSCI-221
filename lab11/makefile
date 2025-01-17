CFLAGS = -g -Wall -Wextra -O0

lab11_test: lab11_main.o lab11.o
	g++ $(CFLAGS) -o lab11_test lab11_main.o lab11.o

lab11_main.o: lab11_main.cpp lab11.hpp
	g++ $(CFLAGS) -c lab11_main.cpp

lab11.o: lab11.cpp lab11.hpp
	g++ $(CFLAGS) -c lab11.cpp

clean:
	rm lab11_main.o lab11_test lab11.o
 