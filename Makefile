all:
	g++ -std=c++11 -g -Wall -O0 -o a.out *.[ch]

.PHONY: clean
clean:
	rm -f *.o *.gch a.out
