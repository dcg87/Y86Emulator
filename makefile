Y86EMUL_FLAGS = gcc -Wall -g -D EXE #-D DEBUG  

EMUL_FILES = y86emul.c y86util.c y86fileio.c y86state.c y86debug.c y86ins.c y86exec.c

all:
	$(Y86EMUL_FLAGS) $(EMUL_FILES) -o y86emul 

y86emul: $(EMUL_FILES)
	$(Y86EMUL_FLAGS) $(EMUL_FILES) -o y86emul 
clean:
	rm y86emul
	rm -r *.dSYM
