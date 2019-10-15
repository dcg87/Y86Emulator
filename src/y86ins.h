#ifndef Y86INS_H
#define Y86INS_H


#include "y86state.h"

union BitField
{
  struct Half
  {
    uint8_t rB:4;
    uint8_t rA:4;
  }half;
  uint8_t byte;
};

/*
 * halt()
 * parameters: pointer to  program state
 * results:  stops execution
 **/
 
void
y86_halt(struct State* state);

/*
 * noop()
 * parameters: pointer to  program state
 * results: does nothing 
 **/
 
void
y86_noop(struct State* state);


/*
 * rrmovl()
 * parameters: pointer to program state
 * results: moves a value from one register to another 
 **/
 

void
y86_rrmovl(struct State* state);

/*
 * irmovl()
 * parameters: pointer to  program state
 * results: moves an immediate into a register 
 **/
 
void 
y86_irmovl(struct State* state);

/*
 * rmmovl()
 * parameters: pointer to  program state
 * results: copies a value from a register to memory 
 **/
 
void
y86_rmmovl(struct State* state);
/*
 * mrmovl()
 * parameters: pointer to  program state
 * results: copies a value from memory to a register 
 **/
 
void
y86_mrmovl(struct State* state);
/*
 * movsbl()
 * parameters: pointer to  program state
 * results: copies a value from memory to a register, but 
 * sign-extends the value
 **/

void
y86_movsbl(struct State* state);

/*
 * op()
 * parameters: pointer to program state
 * results: rB = rA op rB 
 * side effects: sets condition codes
 **/
void
y86_addl(struct State* state);
void
y86_subl(struct State* state);
void
y86_andl(struct State* state);
void
y86_xorl(struct State* state);
void
y86_mull(struct State* state);
void
y86_cmpl(struct State* state);



/*
 * jmpxx()
 * parameters: pointer to  program state
 * results: jump if (rA xx rB) is true, (jmp always jumps)
 * 
 **/
void
y86_jump(struct State* state, int ins);

/*
 * writex()
 * parameters: pointer to  program state
 * copies x bytes of from memory and prints to the terminal
 * 
 * x values:
 * b = 1 byte
 * l = 4 bytes
 **/



void 
y86_writeb(struct State* state);
void 
y86_writel(struct State* state);


/*
 * readx()
 * parameters: pointer to  program state
 * reads x bytes from stdin and stores it in memory
 *
 * x values:
 * b = 1 byte
 * l = 4 bytes
 **/

void
y86_readb(struct State* state);
void 
y86_readl(struct State* state); 


/*
 * pushl()
 * parameters: pointer to  program state
 * results:
 * copies 4 bytes into a memory location offset by the 
 * ESP (stack pointer) register 
 *
 **/


void 
y86_pushl(struct State* state);


/*
 * popl()
 * parameters: pointer to  program state
 * results:
 * copies 4 bytes into a register from 
 * a memory location offset by the ESP (stack pointer) register 
 *
 **/


void 
y86_popl(struct State* state);


/*
 * call()
 * parameters: pointer to  program state
 * results:
 * copies 4 bytes from the next instruction and stores it
 * in memory at an offset relative to ESP (stack pointer)  
 *
 **/


void 
y86_call(struct State* state);



/*
 * ret()
 * parameters: pointer to  program state
 * results:
 * copies 4 bytes from memory at an offset relative to 
 * ESP and and stores it in a register. Then jumps to the
 * value in the register.
 *
 **/


void
y86_ret(struct State* state);


//next 
#endif
