CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS_1 = my_string.o gen_vector.o AVL_tree.o string_process.o main.o

String_driver: $(OBJECTS_1)
	$(CC) $(CFLAGS) -o String_driver $(OBJECTS_1)
my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
gen_vector.o: gen_vector.c gen_vector.h
	$(CC) $(CFLAGS) -c gen_vector.c -o gen_vector.o
AVL_tree.o: AVL_tree.c AVL_tree.h
	$(CC) $(CFLAGS) -c AVL_tree.c -o AVL_tree.o
string_process.o: string_process.c string_process.h
	$(CC) $(CFLAGS) -c string_process.c -o string_process.o
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm String_driver $(OBJECTS_1)

