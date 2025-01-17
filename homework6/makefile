CFLAGS=-g -Wall -Wextra  -O0

homework6_test: homework6_main.o homework6.o
	gcc $(CFLAGS) -o homework6_test homework6_main.o homework6.o

homework6_main.o: homework6_main.c homework6.h
	gcc $(CFLAGS) -c homework6_main.c

homework6.o: homework6.c homework6.h
	gcc $(CFLAGS) -c homework6.c

clean:
	del homework6_main.o homework6_test.exe homework6.o
 