CC = gcc

flags = -std=c99 -fstack-protector-all -g -Wall -Werror

obj = main.o circle.o rectangle.o baseRadio.o block.o city.o customization.o healthCenter.o house.o hydrant.o region.o semaphore.o point.o text.o hashtable.o list.o pquadtree.o queue.o stack.o geo.o openInput.o parameters.o blockBorder.o calculateArea.o covidCases.o covidIncidence.o deleteBlocks.o deleteFigures.o innerPoint.o medicalTreatment.o overlap.o paint.o printInfo.o qry.o urbanDeletion.o sort.o svg.o tools.o


#paths:
elements = ./elements
figures = $(elements)/figures
urban_elements =  $(elements)/urban-elements

util = ./util
data_structure = $(util)/data-structure
input = $(util)/input
query = $(util)/query


siguel: $(obj)
	$(CC) $(obj) -o siguel -lm

main.o: main.c  
	$(CC) $(flags) -c main.c


#figures:
circle.o: $(figures)/circle.c 
	$(CC) $(flags) -c $(figures)/circle.c

rectangle.o: $(figures)/rectangle.c 
	$(CC) $(flags) -c $(figures)/rectangle.c


#urban elements:
block.o: $(urban_elements)/block.c
	$(CC) $(flags) -c $(urban_elements)/block.c

hydrant.o: $(urban_elements)/hydrant.c
	$(CC) $(flags) -c $(urban_elements)/hydrant.c

semaphore.o: $(urban_elements)/semaphore.c
	$(CC) $(flags) -c $(urban_elements)/semaphore.c

baseRadio.o: $(urban_elements)/baseRadio.c
	$(CC) $(flags) -c $(urban_elements)/baseRadio.c

healthCenter.o: $(urban_elements)/healthCenter.c
	$(CC) $(flags) -c $(urban_elements)/healthCenter.c

region.o: $(urban_elements)/region.c
	$(CC) $(flags) -c $(urban_elements)/region.c

house.o: $(urban_elements)/house.c
	$(CC) $(flags) -c $(urban_elements)/house.c

city.o: $(urban_elements)/city.c 
	$(CC) $(flags) -c $(urban_elements)/city.c

customization.o: $(urban_elements)/customization.c
	$(CC) $(flags) -c $(urban_elements)/customization.c


text.o: $(elements)/text.c 
	$(CC) $(flags) -c $(elements)/text.c

point.o: $(elements)/point.c 
	$(CC) $(flags) -c $(elements)/point.c


#data structures:
list.o: $(data_structure)/list.c 
	$(CC) $(flags) -c $(data_structure)/list.c

stack.o: $(data_structure)/stack.c 
	$(CC) $(flags) -c $(data_structure)/stack.c 

queue.o: $(data_structure)/queue.c 
	$(CC) $(flags) -c $(data_structure)/queue.c 

pquadtree.o: $(data_structure)/pquadtree.c 
	$(CC) $(flags) -c $(data_structure)/pquadtree.c 

hashtable.o: $(data_structure)/hashtable.c 
	$(CC) $(flags) -c $(data_structure)/hashtable.c 


#input:
parameters.o: $(input)/parameters.c
	$(CC) $(flags) -c $(input)/parameters.c

openInput.o: $(input)/openInput.c
	$(CC) $(flags) -c $(input)/openInput.c

geo.o: $(input)/geo.c
	$(CC) $(flags) -c $(input)/geo.c


#query:
qry.o: $(query)/qry.c
	$(CC) $(flags) -c $(query)/qry.c

overlap.o: $(query)/overlap.c
	$(CC) $(flags) -c $(query)/overlap.c

innerPoint.o: $(query)/innerPoint.c
	$(CC) $(flags) -c $(query)/innerPoint.c

paint.o: $(query)/paint.c
	$(CC) $(flags) -c $(query)/paint.c

deleteFigures.o: $(query)/deleteFigures.c
	$(CC) $(flags) -c $(query)/deleteFigures.c

deleteBlocks.o: $(query)/deleteBlocks.c
	$(CC) $(flags) -c $(query)/deleteBlocks.c

printInfo.o: $(query)/printInfo.c
	$(CC) $(flags) -c $(query)/printInfo.c

blockBorder.o: $(query)/blockBorder.c
	$(CC) $(flags) -c $(query)/blockBorder.c

urbanDeletion.o: $(query)/urbanDeletion.c
	$(CC) $(flags) -c $(query)/urbanDeletion.c

calculateArea.o: $(query)/calculateArea.c
	$(CC) $(flags) -c $(query)/calculateArea.c

covidCases.o: $(query)/covidCases.c
	$(CC) $(flags) -c $(query)/covidCases.c

medicalTreatment.o: $(query)/medicalTreatment.c
	$(CC) $(flags) -c $(query)/medicalTreatment.c

covidIncidence.o: $(query)/covidIncidence.c
	$(CC) $(flags) -c $(query)/covidIncidence.c


svg.o: $(util)/svg.c 
	$(CC) $(flags) -c $(util)/svg.c

sort.o: $(util)/sort.c 
	$(CC) $(flags) -c $(util)/sort.c

tools.o: $(util)/tools.c 
	$(CC) $(flags) -c $(util)/tools.c


clean: 
	rm $(obj) siguel