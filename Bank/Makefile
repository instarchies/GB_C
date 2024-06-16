bank.exe: main.o functions.o 
	gcc -o bank main.o functions.o

main.o: main.c 
	gcc -c main.c -o main.o 

functions.o: functions.c 
	gcc -c functions.c -o functions.o 


clean:
	rm -rf *.o bank