CFLAGS=-g -Wall -Wextra  -O0

lab5_test: lab5_main.o lab5.o
	gcc $(CFLAGS) -o lab5_test lab5_main.o lab5.o

lab5_main.o: lab5_main.c lab5.h
	gcc $(CFLAGS) -c lab5_main.c

lab5.o: lab5.c lab5.h
	gcc $(CFLAGS) -c lab5.c

clean:
	del lab5_main.o lab5_test.exe lab5.o
 