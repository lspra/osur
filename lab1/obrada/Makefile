#TODO

debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = 
LDFLAGS = -O3
LDLIBS =

OBJEKTI = obrada.o 
MODULI = pobroji/pobroji.o smisao/smisli.o

ZAGLAVLJA=$(OBJEKTI:.o=.d)

obradi.o: $(OBJEKTI) $(MODULI)
	$(CC) -r $^ $(LDFLAGS) -o $@ 

.PHONY: $(MODULI)
$(MODULI):
	make -C $(dir $@)

brisi obrisi:
	make -C pobroji brisi
	make -C smisao brisi
	rm -rf *.o *.d

-include $(ZAGLAVLJA)
