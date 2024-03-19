#TODO
#TODO

debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = 
LDFLAGS = -O3
LDLIBS =

OBJEKTI = smisao.o 
MODULI = dublje/dublje.o na-brzinu/na-brzinu.o

ZAGLAVLJA=$(OBJEKTI:.o=.d)

smisli.o: $(OBJEKTI) $(MODULI)
	$(CC) -r $^ $(LDFLAGS) -o $@ 


.PHONY: $(MODULI)
$(MODULI):
	make -C $(dir $@)

brisi obrisi:
	make -C dublje brisi
	make -C na-brzinu brisi
	rm -rf *.o *.d

-include $(ZAGLAVLJA)
