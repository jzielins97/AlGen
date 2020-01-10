CC	= g++

all: AlGen

AlGen: main.o functions.o product.o
	$(CC) $^ -o $@

%.o: %.cxx
	$(CC) $^ -o $@

clean:
	rm -f *.o AlGen *.d
