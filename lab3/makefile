lab3_test: lab3_main.o lab3_imp.o
	gcc -o -Wall -Wextra -Werror -o lab3_test lab3_main.o lab3_imp.o

lab3_main.o: lab3_main.c lab3_imp.h
	gcc -Wall -Wextra -Werror -c lab3_main.c

lab3_imp.o: lab3_imp.c lab3_imp.h
	gcc -Wall -Wextra -Werror -c lab3_imp.c

clean:
	rm lab3_test lab3_main.o lab3.o
 