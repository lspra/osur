# TODO
# Sad se sve prevodi od ovuda.
# Maknuti to neka se sve prevodi zasebnim Makefileovima po direktorijima.

debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = 
LDFLAGS = -O3
LDLIBS =

OBJEKTI = main.o 
MODULI = izlaz/izlazi.o obrada/obradi.o ulaz/ulazi.o

ZAGLAVLJA=$(OBJEKTI:.o=.d)

PROG=prog

$(PROG): $(OBJEKTI) $(MODULI)
	$(CC) $^ $(LDFLAGS) -o $@ 

main.o: main.c postavke.h
	gcc $(CFLAGS) -o main.o -c main.c

.PHONY: $(MODULI)
$(MODULI):
	make -C $(dir $@)

run: $(PROG)
	./$(PROG)

brisi obrisi:
	make -C izlaz brisi
	make -C obrada brisi
	make -C ulaz brisi
	rm -rf *.o *.d $(PROG)

-include $(ZAGLAVLJA)
