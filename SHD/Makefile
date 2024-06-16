shd.exe: main.o drone.o field.o menu.o
	gcc -o shd main.o drone.o field.o menu.o -lncurses

main.o: main.c 
	gcc -c main.c -o main.o 

drone.o: drone.c 
	gcc -c drone.c -o drone.o 

field.o: field.c
	gcc -c field.c -o field.o

menu.o: menu.c
	gcc -c menu.c -o menu.o
clean:
	rm -rf *.o shd