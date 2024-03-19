#TODO
#TODO

debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = 
LDFLAGS = -O3
LDLIBS =

OBJEKTI = ulaz.o 
MODULI = datoteka/datoteka.o generator/generator.o tipkovnica/tipkovnica.o

ZAGLAVLJA=$(OBJEKTI:.o=.d)

ulazi.o: $(OBJEKTI) $(MODULI)
	$(CC) -r $^ $(LDFLAGS) -o $@ 

.PHONY: $(MODULI)
$(MODULI):
	make -C $(dir $@)

brisi obrisi:
	make -C datoteka brisi
	make -C generator brisi
	make -C tipkovnica brisi
	rm -rf *.o *.d

-include $(ZAGLAVLJA)
