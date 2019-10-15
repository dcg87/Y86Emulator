#include "y86exec.h"
#include "y86state.h"
#include "y86fileio.h"
#include "y86debug.h"
#include "y86codes.h"
#include "y86ins.h"
#include "y86util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* y86exec.c 
 *
 * Describes the process of running a program. 
 *
 * */

void
printExitStatus(struct State* state)
{
  char status[4];
  statusCodeToStr(state->status,status);

  printf("-----------------------\n");
  printf("Execution terminated.\n");
  printf("STATUS: %s\n",status);
  printf("IP: %.8x\n",state->IP);  
  printf("STEP: %.8x\n",state->step);

 } 

void
execute(struct State* state)
{
  #if DEBUG || DISSASSEMBLER

    printf("\n execute(): Starting execution... \n"); 
    #endif

  /* Set status to STATUS_OK to allow execution. */
  state->status = STATUS_AOK;
do{
    state->step++;
    int ins = state->ADDRESS_SPACE[state->IP]; 
   
  /* Decode the instruction that was fetched from memory. */  
  switch(ins)
  {
    case HALT:
      y86_halt(state); 
      break;
    case NOP:
      y86_noop(state);
      break;
    case RRMOVL:
      y86_rrmovl(state);
      break;
    case IRMOVL:
      y86_irmovl(state);
      break;
    case RMMOVL:
      y86_rmmovl(state);
      break;
    case MRMOVL:
      y86_mrmovl(state);
      break;
    case ADDL:
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
      y86_addl(state);
       #if DEBUG || DISSASSEMBLER

 //     printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
      
      break;
    case SUBL:
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      y86_subl(state);
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      break;
    case ANDL:
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      y86_andl(state);
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      break;
    case XORL:
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      y86_xorl(state);
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      break;
    case MULL:
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      y86_mull(state);
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      break;
    case CMPL:
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      y86_cmpl(state);
      #if DEBUG || DISSASSEMBLER

//      printf("ZF = %x OF = %x SF = %x \n",state->ZF,state->OF,state->SF); 
      #endif
 
      break;
    case JMP:
      y86_jump(state,ins);
      break;
    case JLE:
      y86_jump(state,ins);
      break;
   case JL:
      y86_jump(state,ins);
      break;
   case JNE:
      y86_jump(state,ins);
      break;
   case JE:
      y86_jump(state,ins);
      break;
   case JGE:
      y86_jump(state,ins);
      break;
    case JG:
      y86_jump(state,ins);
      break;
    case MOVSBL:
      y86_movsbl(state);
      break;
    case WRITEB:
      y86_writeb(state);
      break;
    case WRITEL:
      y86_writel(state);
      break;
    case READB:
      y86_readb(state);
      break;
    case READL:
      y86_readl(state);
      break;
    case PUSHL:
      y86_pushl(state);
      break;
    case POPL:
      y86_popl(state);
      break;
    case CALL:
      y86_call(state);
      break;
    case RET:
      y86_ret(state);
      break;
    //next
  }
}while(state->status == STATUS_AOK);

  
  printExitStatus(state);  

} 


