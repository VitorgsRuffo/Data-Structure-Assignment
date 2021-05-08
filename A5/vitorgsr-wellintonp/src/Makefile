CC = gcc

flags = -std=c99 -fstack-protector-all -g -Wall -Werror

obj = main.o circle.o rectangle.o address.o baseRadio.o block.o city.o covidAddress.o customization.o region.o establishment.o establishmentType.o healthCenter.o house.o hydrant.o person.o semaphore.o street.o idedPoint.o point.o text.o prim.o dijkstra.o convexhull.o sort.o graph.o hashtable.o priorityQueue.o list.o pquadtree.o queue.o stack.o ec.o geo.o openInput.o parameters.o pm.o via.o blockBorder.o blockResidents.o calculateArea.o changeAddress.o covidCases.o covidIncidence.o deleteBlocks.o deleteFigures.o establishmentInformation.o highlightEstablishment.o innerPoint.o medicalTreatment.o overlap.o paint.o printInfo.o urbanDeletion.o personalInfo.o urbanDeletionInRange.o printTree.o qry.o svg.o tools.o

#paths:
elements = ./elements
figures = $(elements)/figures
urban_elements =  $(elements)/urban-elements

util = ./util
algorithm = $(util)/algorithm
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
city.o: $(urban_elements)/city.c 
	$(CC) $(flags) -c $(urban_elements)/city.c

block.o: $(urban_elements)/block.c
	$(CC) $(flags) -c $(urban_elements)/block.c

baseRadio.o: $(urban_elements)/baseRadio.c
	$(CC) $(flags) -c $(urban_elements)/baseRadio.c

hydrant.o: $(urban_elements)/hydrant.c
	$(CC) $(flags) -c $(urban_elements)/hydrant.c

semaphore.o: $(urban_elements)/semaphore.c
	$(CC) $(flags) -c $(urban_elements)/semaphore.c

customization.o: $(urban_elements)/customization.c
	$(CC) $(flags) -c $(urban_elements)/customization.c

region.o: $(urban_elements)/region.c
	$(CC) $(flags) -c $(urban_elements)/region.c

address.o: $(urban_elements)/address.c
	$(CC) $(flags) -c $(urban_elements)/address.c

covidAddress.o: $(urban_elements)/covidAddress.c
	$(CC) $(flags) -c $(urban_elements)/covidAddress.c

establishment.o: $(urban_elements)/establishment.c
	$(CC) $(flags) -c $(urban_elements)/establishment.c

establishmentType.o: $(urban_elements)/establishmentType.c
	$(CC) $(flags) -c $(urban_elements)/establishmentType.c

healthCenter.o: $(urban_elements)/healthCenter.c
	$(CC) $(flags) -c $(urban_elements)/healthCenter.c

house.o: $(urban_elements)/house.c
	$(CC) $(flags) -c $(urban_elements)/house.c

person.o: $(urban_elements)/person.c
	$(CC) $(flags) -c $(urban_elements)/person.c

street.o: $(urban_elements)/street.c
	$(CC) $(flags) -c $(urban_elements)/street.c


idedPoint.o: $(elements)/idedPoint.c 
	$(CC) $(flags) -c $(elements)/idedPoint.c

point.o: $(elements)/point.c 
	$(CC) $(flags) -c $(elements)/point.c

text.o: $(elements)/text.c 
	$(CC) $(flags) -c $(elements)/text.c


#data structures:
list.o: $(data_structure)/list.c 
	$(CC) $(flags) -c $(data_structure)/list.c

stack.o: $(data_structure)/stack.c 
	$(CC) $(flags) -c $(data_structure)/stack.c 

queue.o: $(data_structure)/queue.c 
	$(CC) $(flags) -c $(data_structure)/queue.c 

pquadtree.o: $(data_structure)/pquadtree.c 
	$(CC) $(flags) -c $(data_structure)/pquadtree.c 

graph.o: $(data_structure)/graph.c 
	$(CC) $(flags) -c $(data_structure)/graph.c 

hashtable.o: $(data_structure)/hashtable.c 
	$(CC) $(flags) -c $(data_structure)/hashtable.c

priorityQueue.o: $(data_structure)/priorityQueue.c 
	$(CC) $(flags) -c $(data_structure)/priorityQueue.c 


#algorithms:
sort.o: $(algorithm)/sort.c 
	$(CC) $(flags) -c $(algorithm)/sort.c

convexhull.o: $(algorithm)/convexhull.c 
	$(CC) $(flags) -c $(algorithm)/convexhull.c

prim.o: $(algorithm)/prim.c 
	$(CC) $(flags) -c $(algorithm)/prim.c

dijkstra.o: $(algorithm)/dijkstra.c 
	$(CC) $(flags) -c $(algorithm)/dijkstra.c


#input:
ec.o: $(input)/ec.c
	$(CC) $(flags) -c $(input)/ec.c

geo.o: $(input)/geo.c
	$(CC) $(flags) -c $(input)/geo.c

openInput.o: $(input)/openInput.c
	$(CC) $(flags) -c $(input)/openInput.c

parameters.o: $(input)/parameters.c
	$(CC) $(flags) -c $(input)/parameters.c

pm.o: $(input)/pm.c
	$(CC) $(flags) -c $(input)/pm.c

via.o: $(input)/via.c
	$(CC) $(flags) -c $(input)/via.c


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

establishmentInformation.o: $(query)/establishmentInformation.c
	$(CC) $(flags) -c $(query)/establishmentInformation.c

highlightEstablishment.o: $(query)/highlightEstablishment.c
	$(CC) $(flags) -c $(query)/highlightEstablishment.c

changeAddress.o: $(query)/changeAddress.c
	$(CC) $(flags) -c $(query)/changeAddress.c

personalInfo.o: $(query)/personalInfo.c
	$(CC) $(flags) -c $(query)/personalInfo.c

urbanDeletionInRange.o: $(query)/urbanDeletionInRange.c
	$(CC) $(flags) -c $(query)/urbanDeletionInRange.c

printTree.o: $(query)/printTree.c
	$(CC) $(flags) -c $(query)/printTree.c

blockResidents.o: $(query)/blockResidents.c
	$(CC) $(flags) -c $(query)/blockResidents.c


svg.o: $(util)/svg.c 
	$(CC) $(flags) -c $(util)/svg.c

tools.o: $(util)/tools.c 
	$(CC) $(flags) -c $(util)/tools.c


clean: 
	rm $(obj) siguel