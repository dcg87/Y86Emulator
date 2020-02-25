#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y86state.h"
#include "y86fileio.h"
#include "y86exec.h"
#include "y86debug.h"
#include "y86codes.h"


/* y86emul.c 
 *
 * The main entry point for the y86 emulator. 
 *
 * Two compile flags here:
 * EXE
 *    enabled: executes the loaded program (e.g. prog1.y86)
 *    disabled: loads prog1.y86 into memory (but does not execute it)
 *
 * DEBUG 
 *    enabled: prints helpful info during execution, dumps final state to .txt
 *    disabled: do not print state info (will only print output if, e.g., prog1.y86 
 *    contains a 'print' instruction)
 * 
 * Refer to makefile 
 * */

int
main (int argc, char* argv[])
{
  /* command help info */
  if (strcmp(argv[1],"-h") == 0 || argc != 2)
  {
    printf("Usage: y86emul [-h] <y86 input file> \n");
    return 0;
  }
  /* create address space (temporarily allocate 65536 bytes (far more than needed);
   * will be resized when .size is found) */
   struct State* state = state_CreateState(0xFFFF);
  
  /* load data + instructions into memory */
  FILE* file = fopen(argv[1],"r");
  loadFile(file,state);  
  fclose(file); 

   #if EXE
  /* start emulation */
   execute(state); 
   #endif

   #if DEBUG
  debug_printState(state);
  debug_dumpMemory(state);
   #endif 

  /* cleanup and exit */
  state_destroyState(state); 
  
  return 0;
}

