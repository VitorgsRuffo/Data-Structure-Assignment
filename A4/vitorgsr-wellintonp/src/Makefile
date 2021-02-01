CC = gcc

flags = -std=c99 -fstack-protector-all -g -Wall -Werror

obj = main.o drawing.o customization.o parameters.o openInput.o geo.o svg.o tools.o list.o stack.o queue.o pquadtree.o hashtable.o circle.o rectangle.o text.o point.o block.o hydrant.o semaphore.o baseRadio.o healthCenter.o region.o house.o qry.o overlap.o innerPoint.o paint.o deleteFigures.o deleteBlocks.o printInfo.o blockBorder.o urbanDeletion.o calculateArea.o covidCases.o medicalTreatment.o covidIncidence.o

util_path = ./util/
data_structure_path = ./util/data-structure/
elements_path = ./elements/
urban_elements_path = ./urban-elements/
drawing_path = ./drawing/
qry_path = ./query/


siguel: $(obj)
	$(CC) $(obj) -o siguel -lm

main.o: main.c  
	$(CC) $(flags) -c main.c


#drawing files:
drawing.o: $(drawing_path)drawing.c 
	$(CC) $(flags) -c $(drawing_path)drawing.c

customization.o: $(drawing_path)customization.c
	$(CC) $(flags) -c $(drawing_path)customization.c


#util files:
parameters.o: $(util_path)parameters.c
	$(CC) $(flags) -c $(util_path)parameters.c

openInput.o: $(util_path)openInput.c
	$(CC) $(flags) -c $(util_path)openInput.c

geo.o: $(util_path)geo.c
	$(CC) $(flags) -c $(util_path)geo.c

svg.o: $(util_path)svg.c 
	$(CC) $(flags) -c $(util_path)svg.c

tools.o: $(util_path)tools.c 
	$(CC) $(flags) -c $(util_path)tools.c


#data structures files:
list.o: $(data_structure_path)list.c 
	$(CC) $(flags) -c $(data_structure_path)list.c

stack.o: $(data_structure_path)stack.c 
	$(CC) $(flags) -c $(data_structure_path)stack.c 

queue.o: $(data_structure_path)queue.c 
	$(CC) $(flags) -c $(data_structure_path)queue.c 

pquadtree.o: $(data_structure_path)pquadtree.c 
	$(CC) $(flags) -c $(data_structure_path)pquadtree.c 

hashtable.o: $(data_structure_path)hashtable.c 
	$(CC) $(flags) -c $(data_structure_path)hashtable.c 


#element files:
circle.o: $(elements_path)circle.c 
	$(CC) $(flags) -c $(elements_path)circle.c

rectangle.o: $(elements_path)rectangle.c 
	$(CC) $(flags) -c $(elements_path)rectangle.c

text.o: $(elements_path)text.c 
	$(CC) $(flags) -c $(elements_path)text.c

point.o: $(elements_path)point.c 
	$(CC) $(flags) -c $(elements_path)point.c


#urban elements files:
block.o: $(urban_elements_path)block.c
	$(CC) $(flags) -c $(urban_elements_path)block.c

hydrant.o: $(urban_elements_path)hydrant.c
	$(CC) $(flags) -c $(urban_elements_path)hydrant.c

semaphore.o: $(urban_elements_path)semaphore.c
	$(CC) $(flags) -c $(urban_elements_path)semaphore.c

baseRadio.o: $(urban_elements_path)baseRadio.c
	$(CC) $(flags) -c $(urban_elements_path)baseRadio.c

healthCenter.o: $(urban_elements_path)healthCenter.c
	$(CC) $(flags) -c $(urban_elements_path)healthCenter.c

region.o: $(urban_elements_path)region.c
	$(CC) $(flags) -c $(urban_elements_path)region.c

house.o: $(urban_elements_path)house.c
	$(CC) $(flags) -c $(urban_elements_path)house.c


#query files:
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

covidCases.o: $(qry_path)covidCases.c
	$(CC) $(flags) -c $(qry_path)covidCases.c

medicalTreatment.o: $(qry_path)medicalTreatment.c
	$(CC) $(flags) -c $(qry_path)medicalTreatment.c

covidIncidence.o: $(qry_path)covidIncidence.c
	$(CC) $(flags) -c $(qry_path)covidIncidence.c


clean: 
	rm $(obj) siguel