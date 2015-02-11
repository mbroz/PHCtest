EXE=twocats.a

default: $(EXE)

$(EXE):
	(cd twocats; make $(EXE))
	-ln -s twocats/$(EXE) $(EXE)
clean:
	(cd twocats; make clean)
	rm -f *.o $(EXE)

.PHONY: clean default
