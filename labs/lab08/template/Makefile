all: matmul.c
	gcc -pthread -o main matmul.c
	./main 10000 10000 1
	./main 10000 10000 2
	./main 10000 10000 4
	./main 10000 10000 8
	./main 10000 10000 16

.PHONY: clean

clean:
	rm main