# dependencies?
linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c
# dependencies?
# incomplete gcc command
main: linked_list.o
	gcc -o main main.c linked_list.o

run: main
	./main

# used to specify targets without dependencies
.PHONY: clean

clean:
	rm linked_list.o main