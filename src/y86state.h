#ifndef Y86STATE_H
#define Y86STATE_H

#include <stdint.h>
#include <stdlib.h>

/* y86state.h
 *
 * This is the program state. It contains 
 * the instruction pointer (IP), 8 registers (reg), 
 * a status code (status), 3 condition codes (ccode), 
 * a step counter (step), main memory (ADDRESS_SPACE),
 * and the size of main memory (mem_size).
 *
 * Remarks:
 * IP should always be greater than 0 (uint).
 * y86 provides 8 registers.
 * emulated program status should never be negative (note: this is not
 * the emulator's return status, which can be negative).
 * SF = sign flag; 1 if negative, 0 otherwise
 * OF = overflow flag; 1 true, 0 otherwise
 * ZF = zero flag; 1 true, 0 otherwise
 * step increments 1 after each instruction
 * ADDRESS_SPACE is an array of byte-addressable memory 
 * mem_size is the size of ADDRESS_SPACE
 * */
struct State
{
  uint32_t  IP;
 int32_t reg[8];
  uint8_t  status;
 uint32_t ccode[3];
  unsigned int SF:1;
  unsigned int OF:1;
  unsigned int ZF:1;
  uint32_t  step;
  uint8_t* ADDRESS_SPACE;
  uint32_t  mem_size;
  
};
/*
 * state_CreateState()
 * parameters: 
 * 32-bit integer representing desired size of memory space in bytes
 *
 * returns: 
 * struct State* 
 * allocates memory for ptr, allocates memory for
 *         ptr->ADDRESS_SPACE, returns ptr
 *         */ 
struct State* 
state_CreateState(uint32_t);
/*
 * state_destroyState()
 * parameters: a pointer ptr that points to the program State.
 * returns:
 * None.
 * deallocates memory for ptr->ADDRESS_SPACE, ptr.
 */

 
void 
state_destroyState(struct State*);


#endif
