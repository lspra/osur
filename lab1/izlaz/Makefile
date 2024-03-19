#TODO

debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = 
LDFLAGS = -O3
LDLIBS =

OBJEKTI = izlaz.o 
MODULI = ispis/ispis.o datoteka/datoteka.o

ZAGLAVLJA=$(OBJEKTI:.o=.d)

izlazi.o: $(OBJEKTI) $(MODULI)
	$(CC) -r $^ $(LDFLAGS) -o $@ 

.PHONY: $(MODULI)
$(MODULI):
	make -C $(dir $@)

brisi obrisi:
	make -C datoteka brisi
	make -C ispis brisi
	rm -rf *.o *.d

-include $(ZAGLAVLJA)
