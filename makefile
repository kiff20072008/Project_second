all: second_project
second_project: main.o 
	g++ main.o  -o second_project

main.o: main.c
	g++ -c main.c

clean:
	rm -rf *.o second_project