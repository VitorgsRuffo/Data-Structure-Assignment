CC = gcc

flags = -std=c99 -fstack-protector-all -g -Wall -Werror

obj = main.o drawing.o customization.o parameters.o openInput.o geo.o list.o svg.o tools.o circle.o rectangle.o text.o block.o hydrant.o semaphore.o baseRadio.o qry.o overlap.o innerPoint.o paint.o deleteFigures.o deleteBlocks.o printInfo.o blockBorder.o urbanDeletion.o calculateArea.o

utils_path = ./utils/
figures_path = ./figures/
urban_elements_path = ./urban-elements/
qry_path = ./qry/

siguel: $(obj)
	$(CC) $(obj) -o siguel -lm

main.o: main.c  
	$(CC) $(flags) -c main.c

drawing.o: drawing.c 
	$(CC) $(flags) -c drawing.c

customization.o: customization.c
	$(CC) $(flags) -c customization.c



parameters.o: $(utils_path)parameters.c
	$(CC) $(flags) -c $(utils_path)parameters.c

openInput.o: $(utils_path)openInput.c
	$(CC) $(flags) -c $(utils_path)openInput.c

geo.o: $(utils_path)geo.c
	$(CC) $(flags) -c $(utils_path)geo.c

list.o: $(utils_path)list.c 
	$(CC) $(flags) -c $(utils_path)list.c

svg.o: $(utils_path)svg.c 
	$(CC) $(flags) -c $(utils_path)svg.c

tools.o: $(utils_path)tools.c 
	$(CC) $(flags) -c $(utils_path)tools.c



circle.o: $(figures_path)circle.c 
	$(CC) $(flags) -c $(figures_path)circle.c

rectangle.o: $(figures_path)rectangle.c 
	$(CC) $(flags) -c $(figures_path)rectangle.c

text.o: $(figures_path)text.c 
	$(CC) $(flags) -c $(figures_path)text.c

block.o: $(urban_elements_path)block.c
	$(CC) $(flags) -c $(urban_elements_path)block.c

hydrant.o: $(urban_elements_path)hydrant.c
	$(CC) $(flags) -c $(urban_elements_path)hydrant.c

semaphore.o: $(urban_elements_path)semaphore.c
	$(CC) $(flags) -c $(urban_elements_path)semaphore.c

baseRadio.o: $(urban_elements_path)baseRadio.c
	$(CC) $(flags) -c $(urban_elements_path)baseRadio.c



qry.o: $(qry_path)qry.c
	$(CC) $(flags) -c $(qry_path)qry.c

overlap.o: $(qry_path)overlap.c
	$(CC) $(flags) -c $(qry_path)overlap.c

innerPoint.o: $(qry_path)innerPoint.c
	$(CC) $(flags) -c $(qry_path)innerPoint.c

paint.o: $(qry_path)paint.c
	$(CC) $(flags) -c $(qry_path)paint.c

deleteFigures.o: $(qry_path)deleteFigures.c
	$(CC) $(flags) -c $(qry_path)deleteFigures.c

deleteBlocks.o: $(qry_path)deleteBlocks.c
	$(CC) $(flags) -c $(qry_path)deleteBlocks.c

printInfo.o: $(qry_path)printInfo.c
	$(CC) $(flags) -c $(qry_path)printInfo.c

blockBorder.o: $(qry_path)blockBorder.c
	$(CC) $(flags) -c $(qry_path)blockBorder.c

urbanDeletion.o: $(qry_path)urbanDeletion.c
	$(CC) $(flags) -c $(qry_path)urbanDeletion.c

calculateArea.o: $(qry_path)calculateArea.c
	$(CC) $(flags) -c $(qry_path)calculateArea.c


clean: 
	rm $(obj) siguel