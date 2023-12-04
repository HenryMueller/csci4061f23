CC=gcc
CFLAGS= -pthread

lab10_p1: p1.c
	$(CC) $(CFLAGS) -o main $^
	./main

lab10_p2: p2.c
	$(CC) $(CFLAGS) -o main $^
	./main

lab10_p3: p3.c
	$(CC) $(CFLAGS) -o main $^
	./main

.PHONY: clean

clean:
	rm -f main