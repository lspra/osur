#TODO
#TODO

debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = 
LDFLAGS = -O3
LDLIBS =

OBJEKTI = ulaz.o 
MODULI = datoteka/datoteka.o

ZAGLAVLJA=$(OBJEKTI:.o=.d)

ulazi.o: $(OBJEKTI) $(MODULI)
	$(CC) -r $^ $(LDFLAGS) -o $@ 

.PHONY: $(MODULI)
$(MODULI):
	make -C $(dir $@)

brisi obrisi:
	make -C datoteka brisi
	rm -rf *.o *.d

-include $(ZAGLAVLJA)
