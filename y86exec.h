#ifndef Y86EXEC_H
#define Y86EXEC_H

#include "y86state.h"

/* parameters: pointer to program state
 * results: prints the instruction pointer, status,
 * step
 *
 * prints informative information about the program state immediately
 * following the end of execution
 *
 **/
 
void
printExitStatus(struct State* state);
/*
 * parameters: pointer to program state
 * returns: none
 * side effects: 
 * starts execution of instrutions
 * sets program status to AOK
 *
 * 
 * 
 **/
void
execute(struct State* state);

#endif
