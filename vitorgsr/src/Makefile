obj = main.o parameters.o geo.o qry.o

siguel: $(obj)
	gcc $(obj) -o siguel

main.o: main.c parameters.h geo.h qry.h
	gcc -c main.c

parameters.o: parameters.c parameters.h
	gcc -c parameters.c

geo.o: geo.c parameters.h
	gcc -c geo.c

qry.o: qry.c parameters.h
	gcc -c qry.c

clean: 
	rm $(obj) siguel