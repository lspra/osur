#TODO
debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = 
LDFLAGS = -O3
LDLIBS =

generator.o: generator.c generator.h
	gcc $(CFLAGS) -o generator.o -c generator.c

brisi obrisi:
	rm -rf *.o *.d
