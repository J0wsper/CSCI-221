CFLAGS=-g -Wall -Wextra  -O0

lab6_test: lab6_main.o lab6.o
	gcc $(CFLAGS) -o lab6_test lab6_main.o lab6.o

lab6_main.o: lab6_main.c lab6.h
	gcc $(CFLAGS) -c lab6_main.c

lab6.o: lab6.c lab6.h
	gcc $(CFLAGS) -c lab6.c

clean:
	del lab6_main.o lab6_test.exe lab6.o
 