CFLAGS = -g -Wall -Wextra -Werror -O0

homework4_test: homework4_main.o homework4.o
	gcc $(CFLAGS) -o homework4_test homework4_main.o homework4.o

homework4_main.o: homework4_main.c homework4.h
	gcc $(CFLAGS) -c homework4_main.c

homework4.o: homework4.c homework4.h
	gcc $(CFLAGS) -c homework4.c
 