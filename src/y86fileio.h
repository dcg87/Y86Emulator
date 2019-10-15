#ifndef Y86FILEIO_H
#define Y86FILEIO_H

#include <stdio.h>
#include "y86state.h"

/*  y86fileio.h
 * 
 * Declarations of functions concerned with reading source files (e.g. prog1.y86)
 * into memory.
 *
 * This is a finite state machine. Each void function receives the pointer to the 
 * open source file, and the emulated program state. The initial state is entered
 * from loadFile() (see y86emul.c).
 * */

/* 
 * parameters: pointer to program state
 * 		pointer to file
 * result:
 * loads the data from file to state->ADDRESS_SPACE
 *  
 *
 * */

void
loadFile(FILE* file,struct State*);

/* error()
 * parameters: pointer to program state
 * 		pointer to file
 * result:
 * prints an error message indicating that the input stream is
 * invalid. closes file. 
 *  
 *
 * */

void
error(FILE* file);

/* {input}_found()
 * parameters: pointer to program state
 * 		pointer to file
 * result:
 * Called when  {input} is found. Grabs the next character from the 
 * stream.
 * . 
 *  
 *
 * */


void 
dot_found(FILE* file,struct State*);
void
b_found(FILE* file,struct State* );
void
s_found(FILE* file, struct State* );

/* store_{data}()
 * parameters: pointer to program state
 * 		pointer to file
 * result:
 * Called when  {data} is found. stores a {data} in memory 
 * . 
 *  
 *
 * */



void
store_byte(FILE* file,struct State*);
void
store_size(FILE* file,struct State* );
void
store_bss(FILE* file,struct State* );
void
store_text(FILE* file,struct State* );
void
store_long(FILE* file,struct State* );
void
store_string(FILE* file, struct State*);


#endif
