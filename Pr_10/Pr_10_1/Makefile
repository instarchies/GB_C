prog: main.o solution.o
	gcc -o prog main.o solution.o 

main.o: main.c 
	gcc -c main.c -o main.o 

solution.o: solution.c 
	gcc -c solution.c -o solution.o 

clean:
	rm -rf *.o prog