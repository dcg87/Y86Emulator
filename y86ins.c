/* y86ins.c 
 *
 *
 * Contains the y86 instructions. 
 * */

/*
 * y86 halt instruction. 
 * sets cpu status to HALT
 **/
y86_halt(struct State* state)
{ 
  #if DEBUG || DISSASSEMBLER|| DISSASSEMBLER
  printf("hlt \n");
  #endif
  state->status = STATUS_HALT;
  state->IP+=1;
}

void
y86_noop(struct State* state)
{ 
  #if DEBUG || DISSASSEMBLER
  printf("nop\n");
  #endif
  state->IP+=1;
}

void
y86_rrmovl(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP; 
   
  // grab register byte
  union BitField regbyte;
  regbyte.byte = mem[*IP + 1];
  
  //get register IDs
  int  rA_ID = regbyte.half.rA;
  int  rB_ID = regbyte.half.rB;

  //get registers
  int* rA = &state->reg[rA_ID];
  int* rB = &state->reg[rB_ID];

  // finally, move the value in rA to rB
  #if DEBUG || DISSASSEMBLER

  char nameRegA[3];
  char nameRegB[3];
  debug_getRegisterName(nameRegA,rA_ID);
  debug_getRegisterName(nameRegB,rB_ID);
  printf("rrmovl %s, %s   %x -> %s \n",nameRegA,nameRegB,*rA,nameRegB); 
  #endif

  /* copy the data to the destination register */ 
  *rB = *rA; 

  *IP+=2;
 }
void
y86_irmovl(struct State* state)
{
   unsigned char* mem = state->ADDRESS_SPACE; 
   unsigned int* IP = &state->IP;
  
  // get registers
  union BitField regbyte;
  regbyte.byte =  mem[*IP + 1];
  int rB_ID = regbyte.half.rB;
  int* rB = &state->reg[rB_ID];

  //store immediate value
  *rB = *(int*)(mem + *IP + 2);
  #if DEBUG || DISSASSEMBLER|| DISSASSEMBLER
  char registerName[3];
  debug_getRegisterName(registerName,rB_ID);
  printf("irmovl %x, %s \n",*(int*)(mem + *IP + 2),registerName);
  #endif
  *IP+=6;
 } 

void
y86_rmmovl(struct State* state)
{
   unsigned char* mem = state->ADDRESS_SPACE; 
   unsigned int* IP = &state->IP;

  // get registers
  union BitField regbyte;
  regbyte.byte = mem[*IP+1];
  int rA_ID = regbyte.half.rA;
  int rB_ID = regbyte.half.rB;
  int32_t* rA = &state->reg[rA_ID]; 
  int32_t* rB = &state->reg[rB_ID];

  //get 32-bit displacement
  int32_t disp = *(int32_t*)(mem + *IP + 2);
    
  // calculate offset
  unsigned int offset = disp + *rB;

  if (offset < 0 || offset > state->mem_size)
  {
    printf("rmmovl: Error. Invalid address (%#x) Exiting...\n",offset);
    exit(EXIT_FAILURE);
  }
  // move value in rA to memory
  *(int*)(mem + offset ) = *rA;

  #if DEBUG || DISSASSEMBLER|| DISSASSEMBLER 
  char nameRegA[3];
  char nameRegB[3];
  debug_getRegisterName(nameRegA,rA_ID);
  debug_getRegisterName(nameRegB,rB_ID);
  printf("rmmovl %s, (%x) %x -> (%x)\n",nameRegA,offset,*rA,offset);
  #endif


  *IP+=6;

}

void
y86_addl(struct State* state)
{
   unsigned char* mem = state->ADDRESS_SPACE; 
   unsigned int* IP = &state->IP;

  //get register IDs
  union BitField regbyte;
  regbyte.byte =  mem[*IP+1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t rB_ID = regbyte.half.rB;
  int* rA = &state->reg[rA_ID]; 
  int* rB = &state->reg[rB_ID]; 

  #if DEBUG || DISSASSEMBLER

  char nameRegA[3];
  char nameRegB[3];
  debug_getRegisterName(nameRegA,rA_ID);
  debug_getRegisterName(nameRegB,rB_ID);
  printf("addl %s, %s %x -> %s \n",nameRegA,nameRegB,*rB + *rA,nameRegB);
  #endif


  // set flags
  int s = *rA + *rB;

  // OF
  // case: a >= 0, b >=0; pos + pos should never be neg
  if (*rA >= 0 && *rB >= 0 && s < 0)  state->OF = 1;
  // case: a < 0, b < 0; neg + neg should never be pos
  else if (*rA < 0 && *rB < 0 && s >= 0) state->OF = 1;
  else state->OF = 0;

 // ZF
  if (s == 0) state->ZF = 1;
  else state->ZF = 0;
  
  // SF
  if (s < 0) state->SF = 1;
  else state->SF = 0;
  
  // computation
  *rB += *rA;
  *IP += 2;
}

void
y86_subl(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;

  // get registers
  union BitField regbyte;
  regbyte.byte =  mem[*IP+1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t rB_ID = regbyte.half.rB;
  int* rA = &state->reg[rA_ID]; 
  int* rB = &state->reg[rB_ID]; 

  // flags
  int s = *rB - *rA;

  //OF 
  if ((*rA < 0 && *rB > 0 && s < 0)  
     || (*rA > 0 && *rB < 0 && s > 0) ) state->OF = 1;
  else state->OF = 0;
  
  //ZF 
  if (*rA == *rB ) state->ZF = 1;
  else state->ZF = 0;
  
  //SF
  if (s < 0) state->SF = 1;
  else state->SF = 0;

 #if DEBUG || DISSASSEMBLER

  char nameRegA[3];
  char nameRegB[3];
  debug_getRegisterName(nameRegA,rA_ID);
  debug_getRegisterName(nameRegB,rB_ID);
  printf("subl %s, %s %x -> %s \n",nameRegA,nameRegB,*rB - *rA,nameRegB);
  #endif

  // computation
  *rB -= *rA;
   
  *IP+=2;
}
void
y86_andl(struct State* state)
{  
   unsigned char* mem = state->ADDRESS_SPACE; 
   unsigned int* IP = &state->IP;

  // get registers
  union BitField regbyte;
  regbyte.byte =  mem[*IP+1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t rB_ID = regbyte.half.rB;
  int* rA = &state->reg[rA_ID]; 
  int* rB = &state->reg[rB_ID]; 

  //computation
  *rB &= *rA;

   // set flags 

  /* OF */
  state->OF = 0; 
  /* SF */
  if (*rB > 0) state->SF = 0;
  else state->SF = 1;
  /* ZF */
  if (*rB == 0) state->ZF = 1;
  else state->ZF = 0;

  *IP+=2;
}
void
y86_xorl(struct State* state)
{
   unsigned char* mem = state->ADDRESS_SPACE; 
   unsigned int* IP = &state->IP;

  // get registers 
  union BitField regbyte;
  regbyte.byte =  mem[*IP + 1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t rB_ID = regbyte.half.rB;
  int* rA = &state->reg[rA_ID]; 
  int* rB = &state->reg[rB_ID]; 

  // computation 
  *rB ^= *rA;

  // set flags
  int s = *rB ^= *rA;

  //ZF
  state->OF = 0;
  if (s == 0) state->ZF = 1;
  else state->ZF = 0;

  //OF
  state->OF = 0;

  //SF
  if(s < 0) state->SF = 1;
  else state->SF = 0;

  *IP+=2;

}
void
y86_mull(struct State* state)
{
   unsigned char* mem = state->ADDRESS_SPACE; 
   unsigned int* IP = &state->IP;

  /* get registers */ 
  union BitField regbyte;
  regbyte.byte =  mem[*IP+1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t rB_ID = regbyte.half.rB;
  int* rA = &state->reg[rA_ID]; 
  int* rB = &state->reg[rB_ID]; 

    //flags
  int s = *rA * *rB; 
  //OF
  // case a >= 0, b >= 0; pos x pos should never be neg
  if (*rA >= 0 && *rB >= 0 && s < 0) state->OF = 1;
  // case a < 0, b < 0; neg x neg should never be neg
  else if (*rA < 0 && *rB < 0 && s < 0)state->OF = 1; 
  // case a < 0, b > 0; neg x pos should never be pos unless pos is zero
  else if (*rA < 0 && *rB > 0 && s > 0) state->OF = 1;
  else state->OF = 0;

  // ZF
  if (s == 0) state->ZF = 1;
  else state->ZF = 0;
  
  //SF 
  if (s < 0) state->SF = 1;
  else state->SF = 0;
 

/* computation */
  *rB *= *rA;
 


 #if DEBUG || DISSASSEMBLER

  char nameRegA[3];
  char nameRegB[3];
  debug_getRegisterName(nameRegA,rA_ID);
  debug_getRegisterName(nameRegB,rB_ID);
  printf("mull %s, %s %x -> %s\n",nameRegA,nameRegB,*rA * *rB,nameRegB);
  #endif

  *IP+=2;

}

/*
 * cmpl rA, rB
 *
 * Compares rA to rB and sets the condition codes accordingly.
 * */

void
y86_cmpl(struct State* state)
{
   unsigned char* mem = state->ADDRESS_SPACE; 
   unsigned int* IP = &state->IP;

  /* get registers */
  union BitField regbyte;
  regbyte.byte =  mem[*IP+1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t rB_ID = regbyte.half.rB;
  int* rA = &state->reg[rA_ID]; 
  int* rB = &state->reg[rB_ID]; 
  
  #if DEBUG || DISSASSEMBLER

  char nameRegA[3];
  char nameRegB[3];
  debug_getRegisterName(nameRegA,rA_ID);
  debug_getRegisterName(nameRegB,rB_ID);
  printf("cmpl %s, %s    %x, %x\n",nameRegB,nameRegA,*rB,*rA);
  #endif 

  // flags
  int s = *rB - *rA;
 
  //OF 
  if ((*rA < 0 && *rB > 0 && s < 0)  
     || (*rA > 0 && *rB < 0 && s > 0) ) state->OF = 1;
  else state->OF = 0;
  
  //ZF 
  if (*rA == *rB )  state->ZF = 1;
  else state->ZF = 0;
  
  //SF
  if (s < 0) state->SF = 1;
  else state->SF = 0;

  *IP+=2;
  
}



void
y86_jump(struct State* state, int ins)
{
  unsigned char* mem = state->ADDRESS_SPACE; 
  unsigned int* IP = &state->IP;

  // get 4-byte destination
  int32_t D = *(int*)(mem + *IP + 1); 

  switch(ins)
  {
     case JG:
     if (!(state->SF ^ state->OF) && !state->ZF)
      {
      *IP = D;
     #if DEBUG || DISSASSEMBLER

     printf("jg %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
     #endif
      break;
    }
    else
    {
      #if DEBUG || DISSASSEMBLER

      printf("jg %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
      #endif
 

      *IP+=5;
      break;
    }
     case JLE:
    // jle
  
    if ((state->SF ^ state->OF) || state->ZF)
   {
     #if DEBUG || DISSASSEMBLER

     printf("jle %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
     #endif
 
   // jump to destination
    *IP = D;
    break;
   }
    else
    {
    #if DEBUG || DISSASSEMBLER

      printf("jle %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
      #endif
 

      *IP+=5;
      break;
    }

//jl 
    case JL:

 
  if (state->SF ^ state->OF)
   {
      #if DEBUG || DISSASSEMBLER

     printf("jl %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
     #endif
    
   // jump to destination
    *IP = D;
 
     break;
    } 
      else
    {
          #if DEBUG || DISSASSEMBLER

      printf("je %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
      #endif
 
      *IP+=5;
      break;
    }

  // je

    case JE:
 
    if (state->ZF)
    {
     #if DEBUG || DISSASSEMBLER

     printf("je %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
     #endif
  
       *IP=D;
      break;
    }
    else
    {
      #if DEBUG || DISSASSEMBLER

      printf("je %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
      #endif
 
      *IP+=5;
       break;
    } 
  // jne 

    case JNE:
   
   if (!state->ZF)
    {
     #if DEBUG || DISSASSEMBLER

     printf("jne %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
     #endif
 
   // jump to destination
   *IP = D; 
    break;
    }
   else
   {
    #if DEBUG || DISSASSEMBLER

      printf("jne %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
      #endif
 

      *IP+=5;
      break;
   }

  //JGE
     case JGE:
    #if DEBUG || DISSASSEMBLER

   printf("jge %.8x ",D);
   #endif
    if (!(state->SF ^ state->OF))
    {
 #if DEBUG || DISSASSEMBLER

     printf("jge %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
 
    #endif
 
     // jump to destination
    *IP = D;

      break;
    }
    else
    {
     #if DEBUG || DISSASSEMBLER

      printf("jge %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
      #endif
 
      *IP+=5;
       break;
    }
//jmp
 case JMP:
   *IP = D;
   #if DEBUG || DISSASSEMBLER

   printf("jmp %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state->ZF,state->SF,state->OF);
   #endif
    break;

 default:
   printf("jmp: Error. Exiting...\n");
   exit(EXIT_FAILURE);
   break;

  }
}

void
y86_mrmovl(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;
 
  /* get registers */
  union BitField regbyte;
  regbyte.byte = mem[*IP + 1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t rB_ID = regbyte.half.rB;
  int32_t* rA = &state->reg[rA_ID];
  int32_t* rB = &state->reg[rB_ID];

   //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2);
 
  // calculate offset 
  int offset = disp + *rB; 

  //store value in rA 
  *rA = *(int*)(mem + offset);
  
  #if DEBUG || DISSASSEMBLER

  char nameRegA[3];
  char nameRegB[3];
  debug_getRegisterName(nameRegA,rA_ID);
  debug_getRegisterName(nameRegB,rB_ID);
  printf("mrmovl (%x), %s    %x -> %s \n",offset,nameRegA,*rA,nameRegA);
  #endif

 //move to next instruction
  *IP += 6;
}
void
y86_movsbl(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;
 
  /* get registers */
  union BitField regbyte;
  regbyte.byte = mem[*IP + 1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t rB_ID = regbyte.half.rB;
  int32_t* rA = &state->reg[rA_ID];
  int32_t* rB = &state->reg[rB_ID];

   //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2);
 
  // calculate offset 
  int offset = disp + *rB; 

  // get desired byte of data
  char desired_data = *(mem + offset);
  // promote this data to a 32-bit signed int
  *rA = (int)desired_data; 

  #if DEBUG || DISSASSEMBLER

  char nameRegA[3];
  debug_getRegisterName(nameRegA,rA_ID);
  printf("movsbl (%x), %s  %x -> %s     \n",offset,nameRegA,*rA,nameRegA);
  #endif

 //move to next instruction
  *IP += 6;
}
void
y86_writeb(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;

  /* get registers */ 
  union BitField regbyte;
  regbyte.byte = mem[*IP + 1];
  int rA_ID = regbyte.half.rA;
  int* rA = &state->reg[rA_ID];

  //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2);

  //calculate offset
  int offset = disp + *rA;

 
 // write this byte to the terminal
  #if DEBUG || DISSASSEMBLER

 
  char nameRegA[3];
  debug_getRegisterName(nameRegA,rA_ID);
  printf("writeb (%x) \n",offset);

  #else
  // get desired byte of data
  char desired_data = mem[offset];
  printf("%c",desired_data);
  #endif
  
 //move to next instruction
  *IP += 6;
}
void
y86_writel(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;
 
  /* get registers */ 
  union BitField regbyte;
  regbyte.byte = mem[*IP + 1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t* rA = &state->reg[rA_ID];

  //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2);

  //calculate offset
  int offset = disp + *rA;

 
  // write these 4-bytes to the terminal
 #if DEBUG || DISSASSEMBLER|| DISSASSEMBLER
  // get desired 4-bytes of data
 
  char nameRegA[3];
  debug_getRegisterName(nameRegA,rA_ID);
  printf("writel (%x)\n",offset);
  #else
  // get desired 4-bytes of data
  int desired_data = *(int*)(mem + offset);
  printf("%x",desired_data);
  #endif 


  //move to next instruction
  *IP += 6;
}

void
y86_readb(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;

  // read in the byte to store (from the terminal)
  char input[2];
  if (scanf("%c%c",&input[0],&input[1]) != EOF) state->ZF = 0;
  else state->ZF = 1;
  state->OF = 0;
  state->SF = 0;

  int converted_input = TTO_byte(input[0],input[1]);  
  
  // get offset register, rA
  union BitField regbyte;
  regbyte.byte = mem[*IP + 1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t* rA = &state->reg[rA_ID];
  
  /* grab 32-bit displacement */
  int disp = *(int*)(mem + *IP + 2);

  //calculate offset
  int offset = disp + *rA;

 // write this byte to memory
  *(mem + offset) = converted_input;
  #if DEBUG || DISSASSEMBLER

  char nameRegA[3];
  debug_getRegisterName(nameRegA,rA_ID);
  printf("readb %x(%x) (wrote: %c)\n",disp,*rA,converted_input);
  #endif
 
  //move to next instruction
  *IP += 6;
}
void 
y86_readl(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;

  // get rA
  union BitField regbyte;
  regbyte.byte = mem[*IP + 1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t* rA = &state->reg[rA_ID];

  //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2);
 
  //calculate offset
  int offset = disp + *rA;

  // read in the byte to store 
  int input; 
  if(scanf("%x",&input) != EOF) state->ZF = 0;
  else state->ZF = 1;
  state->SF = 0;
  state->OF = 0;

 // write 4 bytes to memory
 *(int*)(mem + offset) = input;

  #if DEBUG || DISSASSEMBLER

  char nameRegA[3];
  debug_getRegisterName(nameRegA,rA_ID);
  printf("readl (%x) (wrote: %x)\n",offset,input);
  #endif
 
 //move to next instruction
  *IP += 6;
} 
void
y86_pushl(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;

  // get rA, the register to push
  union BitField regbyte;
  regbyte.byte = mem[*IP + 1];
  int32_t rA_ID = regbyte.half.rA;
  int32_t* rA = &state->reg[rA_ID];
  
  // get stack pointer 
  int32_t* rESP = &state->reg[ESP];


  #if DEBUG || DISSASSEMBLER
  int old_rESP = *rESP;

  char nameRegA[3];
  debug_getRegisterName(nameRegA,rA_ID);
  printf("pushl %s ESP(%.8x -> %.8x) %x -> %.8x \n",nameRegA,old_rESP,*rESP,*rA,*rESP); 
  #endif 
 
  // push: decrement, copy to address pointed by ESP
  *rESP -= 4; 
  *(int*)(mem + *rESP) = *rA;
 
 
  //increment IP  
  *IP += 2;   
}
void
y86_popl(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;

  // get rA, the register to pop to
  union BitField regbyte;
  regbyte.byte = mem[*IP + 1];
  int rA_ID = regbyte.half.rA;
  int* rA = &state->reg[rA_ID];
 


  // get stack pointer 
  int* rESP = &state->reg[ESP];

  #if DEBUG || DISSASSEMBLER
  int old_rESP = *rESP;  

  char nameRegA[3];
  debug_getRegisterName(nameRegA,rA_ID);
  printf("popl %s ESP(%.8x -> %.8x) %x -> %s \n",nameRegA,old_rESP,*rESP,*rA,nameRegA); 
  #endif
 
  // pop: increment ESp, copy from address pointed by ESP to rA,
  // decrement ESP
  *rA = *(int*)(mem + *rESP);
  *rESP += 4;


  //increment IP  
  *IP += 2;   
}
// push return address onto stack ( address of next instruction)

void
y86_call(struct State* state)
{
  unsigned char* mem = state->ADDRESS_SPACE;
  unsigned int* IP = &state->IP;

  /* get return address (address of next instruction) */
  int ret_addr = *IP+5;
  
  // get stack pointer 
  int* rESP = &state->reg[ESP];

  // push: increment (grows toward negative), copy to address pointed by ESP
  *rESP -= 4;
  *(int*)(mem + *rESP) = ret_addr;

  /* get jump target (32-bit address) */
  int offset = *(int*)(mem + *IP + 1);

  #if DEBUG || DISSASSEMBLER|| DISSASSEMBLER
  printf("call %.8x  IP(%.8x -> %.8x) ret_addr=%x \n",offset,*IP,offset,ret_addr);
  #endif

  /* jump to destination   */
  *IP = offset;
} 
/* return:
  pop return address
  decrement stack pointer 
  set IP to return address
  
*/           
void
y86_ret(struct State* state)
{
  int* rESP = &state->reg[ESP];
  unsigned char* mem = state->ADDRESS_SPACE; 
  unsigned int* IP = &state->IP;


  // pop return address
  int ret_addr = *(int*)(mem +  *rESP);
 
  #if DEBUG || DISSASSEMBLER|| DISSASSEMBLER
  int old_rESP = *rESP;

  printf("ret %.8x ESP(%x -> %x)\n",ret_addr,old_rESP,*rESP+4);
  #endif


  *rESP += 4;

  // set IP to return address (jump)
  *IP = ret_addr;

} 
