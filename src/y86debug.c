#include "y86debug.h"
#include "y86codes.h"




/* y86debug.c
 *
 * Implementations of various debugging tools 
 * */

void
debug_initializeRegisters(struct State* state)
{
  int i = 0;
  for (;i < 9;i++)
  {
    state->reg[i] = 0;
  }
}
/*
 * dump
 * input: void pointer to arbitrary data
 * output: none
 * 
 * First, dump() creates a file called "dump.txt" and opens it. 
 * . Next, for each byte of data, it writes the following to
 * dump.txt:
 *           hex address: byte
 *
 * Where byte is in hexadecimal notation. Each write starts on a new line.
 * */

void
debug_dumpMemory(struct State* state)
{
  printf("\nDumping memory...\n");

  FILE* file = fopen("dump.txt","w");
  int i = 0;
  while (i < state->mem_size)
  {
    fprintf(file,"%x: %x \n",i,*(state->ADDRESS_SPACE+i));

    i++;
  } 
  fclose(file);
}

void
debug_storeInRegister(struct State* state,int32_t ID,int32_t val)
{
  char reg_name[4];
  debug_getRegisterName(reg_name,ID);
  
  state->reg[ID] = val;
  printf("%s = %d\n",reg_name,val);
} 

void
debug_print(const char* str)
{
  printf("debug: %s\n",str);
}

void
debug_getRegisterName(char* str, int ID)
{
 
  switch (ID)
  {
    case EAX:
      strcpy(str,"EAX"); 
      break;
     case ECX:
      strcpy(str,"ECX"); 
      break;
     case EDX:
      strcpy(str,"EDX"); 
      break;
     case EBX:
      strcpy(str,"EBX"); 
      break;
     case ESP:
      strcpy(str,"ESP"); 
      break;
     case EBP:
      strcpy(str,"EBP"); 
      break;
     case ESI:
      strcpy(str,"ESI"); 
      break;
     case EDI:
      strcpy(str,"EDI"); 
      break;
   }  
}
void
debug_printState(struct State* state)
{
  printf("\n");
  printf("IP:%.8x\n",state->IP);
  // translate status number to string
  printf("Status: %x\n",state->status);
  printf("Step: %.8x\n",state->step);
  printf("EAX: %.8x\n",state->reg[EAX]);
  printf("ECX: %.8x\n",state->reg[ECX]);
  printf("EDX: %.8x\n",state->reg[EDX]);
  printf("EBX: %.8x\n",state->reg[EBX]);
  printf("ESP: %.8x\n",state->reg[ESP]);
  printf("EBP: %.8x\n",state->reg[EBP]);
  printf("ESI: %.8x\n",state->reg[ESI]);
  printf("EDI: %.8x\n",state->reg[EDI]);
  
  printf("ZF: %x\n",state->ZF);
  printf("SF: %x\n",state->SF);
  printf("OF: %x\n",state->OF);
  printf("\n");


}
void 
debug_printMemory(const char* mem,int start, int end)
{
  int i = start;
  for (; i < end;i++)
  {
    printf("%.8x: %.8x\n",i,mem[i]);
  }
}

