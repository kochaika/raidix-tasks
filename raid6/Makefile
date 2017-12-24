all: GF_tables.o GF_operations.o raid6.o main.o
	gcc GF_tables.o GF_operations.o raid6.o main.o

main.o: main.c
	gcc -c main.c

raid6.o: raid6.c
	gcc -c raid6.c

GF_tables.o: GF_tables.c
	gcc -c GF_tables.c

GF_operations.o: GF_operations.c
	gcc -c GF_operations.c

clean:
	rm -rf *.o *.out
