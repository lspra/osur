#TODO
debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = 
LDFLAGS = -O3
LDLIBS =

tipkovnica.o: tipkovnica.c tipkovnica.h
	gcc $(CFLAGS) -o tipkovnica.o -c tipkovnica.c

brisi obrisi:
	rm -rf *.o *.d
