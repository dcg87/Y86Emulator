#ifndef Y86_DEBUG
#define Y86_DEBUG

#include <string.h>
#include <stdio.h>
#include "y86state.h"

void
debug_initializeRegisters(struct State* state);
void
debug_storeInRegister(struct State* state,int ID,int val);
void
debug_getRegisterName(char* dest,int ID);
void
debug_print(const char*);
void 
debug_dumpMemory(struct State*);
void
debug_printState(struct State*);
/*
 *printMemory()
 *paramters: 
  const char pointer to memory block,
  int a represeting the starting index, 
  int b representing the  end index
  results:
  Outputs to stdout. Prints the address and contents of each byte of memory
  within range r: a <= r < b 
  
*/
void
debug_printMemory(const char*, int,int);


#endif

