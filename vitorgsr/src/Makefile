
siguel: main.o parameters.o
	gcc main.o parameters.o -o siguel

main.o: main.c parameters.h
	gcc -c main.c

parameters.o: parameters.c parameters.h
	gcc -c parameters.c


clean: 
	rm main.o parameters.o siguel