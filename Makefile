CFLAGS = -Wall -g  -D_POSIX_C_SOURCE=199309L


all: clean test go

%.o: %.cpp 
	g++ -c $(CFLAGS) $<

test: test.o AaronClass.o
	g++ $(CFLAGS) test.o AaronClass.o -o test
go: test
	./test
clean:
	rm -f *.o test