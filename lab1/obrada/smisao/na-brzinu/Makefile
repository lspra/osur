#TODO
debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = 
LDFLAGS = -O3
LDLIBS =

na-brzinu.o: na-brzinu.c na-brzinu.h
	gcc $(CFLAGS) -o na-brzinu.o -c na-brzinu.c

brisi obrisi:
	rm -rf *.o *.d
