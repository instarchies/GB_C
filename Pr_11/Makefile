report: main.o temp_functions.o 
	gcc -o report main.o temp_functions.o  

main.o: main.c 
	gcc -c main.c -o main.o 

temp_functions.o: temp_functions.c 
	gcc -c temp_functions.c -o temp_functions.o 

clean:
	rm -rf *.o report