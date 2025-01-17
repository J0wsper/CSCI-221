CFLAGS=-g -Wall -Wextra  -O0

homework5_test: homework5_main.o homework5.o
	gcc $(CFLAGS) -o homework5_test homework5_main.o homework5.o

homework5_main.o: homework5_main.c homework5.h
	gcc $(CFLAGS) -c homework5_main.c

homework5.o: homework5.c homework5.h
	gcc $(CFLAGS) -c homework5.c

clean:
	del homework5_main.o homework5_test.exe homework5.o
 