all: encryption divideix div
encryption: encryption.o
	g++ -o encryption encryption.o

encryption.o: encryption.cc
	g++ -c encryption.cc

divideix: divideix.o
	g++ -o divideix divideix.o

divideix.o: divideix.cc
	g++ -c divideix.cc

div: div.o
	g++ -o div div.o

div.o: div.cc
	g++ -c div.cc

codificat:

test:
	./encryption <input.inp > codificat.out
	./divideix  <codificat.out> clau.key
	./div  <codificat.out> cody.42	
	cat clau.key
	cat cody.42
debug:
	./encryption <input.inp > codificat.out
	cat codificat.out

clean:
	rm *.o
	rm *.out
