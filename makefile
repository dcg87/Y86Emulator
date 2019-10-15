Y86EMUL_FLAGS = gcc -Wall -g -D EXE #-D DEBUG  

EMUL_FILES = src/y86emul.c src/y86util.c src/y86fileio.c src/y86state.c src/y86debug.c src/y86ins.c src/y86exec.c

all:
	$(Y86EMUL_FLAGS) $(EMUL_FILES) -o y86emul 

y86emul: $(EMUL_FILES)
	$(Y86EMUL_FLAGS) $(EMUL_FILES) -o y86emul 
clean:
	rm y86emul
