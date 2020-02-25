
/* y86ins.go
 *
 *
 * Contains the y86 instructions. 
 * */

/*
 * y86 halt instruction. 
 * sets cpu status to HALT
 **/
package y86
import "fmt"

func y86_halt(state *State) {
  state.status = STATUS_HALT
  state.IP+=1
}


func y86_noop(state *State){ 
  state.IP+=1
}

func
y86_rrmovl(state *State){
  mem := state.ADDRESS_SPACE
  IP := &state.IP 
   
  // grab register byte
  union BitField regbyte
  regbyte.byte = mem[*IP + 1]
  
  //get register IDs
  rA_ID = regbyte.half.rA
  rB_ID = regbyte.half.rB

  //get registers
  rA *int = &state.reg[rA_ID]
  rB *int = &state.reg[rB_ID]

  // finally, move the value in rA to rB
  

  char nameRegA[3]
  char nameRegB[3]
  debug_getRegisterName(nameRegA,rA_ID)
  debug_getRegisterName(nameRegB,rB_ID)
  printf("rrmovl %s, %s   %x -> %s \n",nameRegA,nameRegB,*rA,nameRegB) 
  

  /* copy the data to the destination register */ 
  *rB = *rA 

  *IP+=2
 }
func
y86_irmovl(state *State){
   mem *int8 = state.ADDRESS_SPACE 
   IP *uint = &state.IP
  
  // get registers
  union BitField regbyte
  regbyte.byte =  mem[*IP + 1]
  int rB_ID = regbyte.half.rB
  rB *int = &state.reg[rB_ID]

  //store immediate value
  *rB = *(int*)(mem + *IP + 2)
  
  char registerName[3]
  debug_getRegisterName(registerName,rB_ID)
  printf("irmovl %x, %s \n",*(int*)(mem + *IP + 2),registerName)
  

  *IP+=6
 } 

func
y86_rmmovl(state *State){
   mem *int8 = state.ADDRESS_SPACE 
   IP *uint = &state.IP

  // get registers
  union BitField regbyte
  regbyte.byte = mem[*IP+1]
  int rA_ID = regbyte.half.rA
  int rB_ID = regbyte.half.rB
  int32_t* rA = &state.reg[rA_ID] 
  int32_t* rB = &state.reg[rB_ID]

  //get 32-bit displacement
  int32_t disp = *(int32_t*)(mem + *IP + 2)
    
  // calculate offset
  unsigned int offset = disp + *rB

  if (offset < 0 || offset > state.mem_size)
  {
    printf("rmmovl: Error. Invalid address (%
    exit(EXIT_FAILURE)
  }
  // move value in rA to memory
  *(int*)(mem + offset ) = *rA

  
  char nameRegA[3]
  char nameRegB[3]
  debug_getRegisterName(nameRegA,rA_ID)
  debug_getRegisterName(nameRegB,rB_ID)
  printf("rmmovl %s, (%x) %x -> (%x)\n",nameRegA,offset,*rA,offset)
  


  *IP+=6

}

func
y86_addl(state *State){
   mem *int8 = state.ADDRESS_SPACE 
   IP *uint = &state.IP

  //get register IDs
  union BitField regbyte
  regbyte.byte =  mem[*IP+1]
  int32_t rA_ID = regbyte.half.rA
  int32_t rB_ID = regbyte.half.rB
  rA *int = &state.reg[rA_ID] 
  rB *int = &state.reg[rB_ID] 

  

  char nameRegA[3]
  char nameRegB[3]
  debug_getRegisterName(nameRegA,rA_ID)
  debug_getRegisterName(nameRegB,rB_ID)
  printf("addl %s, %s %x -> %s \n",nameRegA,nameRegB,*rB + *rA,nameRegB)
  


  // set flags
  int s = *rA + *rB

  // OF
  // case: a >= 0, b >=0 pos + pos should never be neg
  if (*rA >= 0 && *rB >= 0 && s < 0)  state.OF = 1
  // case: a < 0, b < 0 neg + neg should never be pos
  else if (*rA < 0 && *rB < 0 && s >= 0) state.OF = 1
  else state.OF = 0

 // ZF
  if (s == 0) state.ZF = 1
  else state.ZF = 0
  
  // SF
  if (s < 0) state.SF = 1
  else state.SF = 0
  
  // computation
  *rB += *rA
  *IP += 2
}

func
y86_subl(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP

  // get registers
  union BitField regbyte
  regbyte.byte =  mem[*IP+1]
  int32_t rA_ID = regbyte.half.rA
  int32_t rB_ID = regbyte.half.rB
  rA *int = &state.reg[rA_ID] 
  rB *int = &state.reg[rB_ID] 

  // flags
  int s = *rB - *rA

  //OF 
  if ((*rA < 0 && *rB > 0 && s < 0)  
     || (*rA > 0 && *rB < 0 && s > 0) ) state.OF = 1
  else state.OF = 0
  
  //ZF 
  if (*rA == *rB ) state.ZF = 1
  else state.ZF = 0
  
  //SF
  if (s < 0) state.SF = 1
  else state.SF = 0

 

  char nameRegA[3]
  char nameRegB[3]
  debug_getRegisterName(nameRegA,rA_ID)
  debug_getRegisterName(nameRegB,rB_ID)
  printf("subl %s, %s %x -> %s \n",nameRegA,nameRegB,*rB - *rA,nameRegB)
  

  // computation
  *rB -= *rA
   
  *IP+=2
}
func
y86_andl(state *State){  
   mem *int8 = state.ADDRESS_SPACE 
   IP *uint = &state.IP

  // get registers
  union BitField regbyte
  regbyte.byte =  mem[*IP+1]
  int32_t rA_ID = regbyte.half.rA
  int32_t rB_ID = regbyte.half.rB
  rA *int = &state.reg[rA_ID] 
  rB *int = &state.reg[rB_ID] 

  //computation
  *rB &= *rA

   // set flags 

  /* OF */
  state.OF = 0 
  /* SF */
  if (*rB > 0) state.SF = 0
  else state.SF = 1
  /* ZF */
  if (*rB == 0) state.ZF = 1
  else state.ZF = 0

  *IP+=2
}
func
y86_xorl(state *State){
   mem *int8 = state.ADDRESS_SPACE 
   IP *uint = &state.IP

  // get registers 
  union BitField regbyte
  regbyte.byte =  mem[*IP + 1]
  int32_t rA_ID = regbyte.half.rA
  int32_t rB_ID = regbyte.half.rB
  rA *int = &state.reg[rA_ID] 
  rB *int = &state.reg[rB_ID] 

  // computation 
  *rB ^= *rA

  // set flags
  int s = *rB ^= *rA

  //ZF
  state.OF = 0
  if (s == 0) state.ZF = 1
  else state.ZF = 0

  //OF
  state.OF = 0

  //SF
  if(s < 0) state.SF = 1
  else state.SF = 0

  *IP+=2

}
func
y86_mull(state *State){
   mem *int8 = state.ADDRESS_SPACE 
   IP *uint = &state.IP

  /* get registers */ 
  union BitField regbyte
  regbyte.byte =  mem[*IP+1]
  int32_t rA_ID = regbyte.half.rA
  int32_t rB_ID = regbyte.half.rB
  rA *int = &state.reg[rA_ID] 
  rB *int = &state.reg[rB_ID] 

    //flags
  int s = *rA * *rB 
  //OF
  // case a >= 0, b >= 0 pos x pos should never be neg
  if (*rA >= 0 && *rB >= 0 && s < 0) state.OF = 1
  // case a < 0, b < 0 neg x neg should never be neg
  else if (*rA < 0 && *rB < 0 && s < 0)state.OF = 1 
  // case a < 0, b > 0 neg x pos should never be pos unless pos is zero
  else if (*rA < 0 && *rB > 0 && s > 0) state.OF = 1
  else state.OF = 0

  // ZF
  if (s == 0) state.ZF = 1
  else state.ZF = 0
  
  //SF 
  if (s < 0) state.SF = 1
  else state.SF = 0
 

/* computation */
  *rB *= *rA
 


 

  char nameRegA[3]
  char nameRegB[3]
  debug_getRegisterName(nameRegA,rA_ID)
  debug_getRegisterName(nameRegB,rB_ID)
  printf("mull %s, %s %x -> %s\n",nameRegA,nameRegB,*rA * *rB,nameRegB)
  

  *IP+=2

}

/*
 * cmpl rA, rB
 *
 * Compares rA to rB and sets the condition codes accordingly.
 * */

func
y86_cmpl(state *State){
   mem *int8 = state.ADDRESS_SPACE 
   IP *uint = &state.IP

  /* get registers */
  union BitField regbyte
  regbyte.byte =  mem[*IP+1]
  int32_t rA_ID = regbyte.half.rA
  int32_t rB_ID = regbyte.half.rB
  rA *int = &state.reg[rA_ID] 
  rB *int = &state.reg[rB_ID] 
  
  

  char nameRegA[3]
  char nameRegB[3]
  debug_getRegisterName(nameRegA,rA_ID)
  debug_getRegisterName(nameRegB,rB_ID)
  printf("cmpl %s, %s    %x, %x\n",nameRegB,nameRegA,*rB,*rA)
  

  // flags
  int s = *rB - *rA
 
  //OF 
  if ((*rA < 0 && *rB > 0 && s < 0)  
     || (*rA > 0 && *rB < 0 && s > 0) ) state.OF = 1
  else state.OF = 0
  
  //ZF 
  if (*rA == *rB )  state.ZF = 1
  else state.ZF = 0
  
  //SF
  if (s < 0) state.SF = 1
  else state.SF = 0

  *IP+=2
  
}



func
y86_jump(state *State, int ins){
  mem *int8 = state.ADDRESS_SPACE 
  IP *uint = &state.IP

  // get 4-byte destination
  int32_t D = *(int*)(mem + *IP + 1) 

  switch(ins)
  {
     case JG:
     if (!(state.SF ^ state.OF) && !state.ZF)
      {
      *IP = D
     

     printf("jg %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
     
      break
    }
    else
    {
      

      printf("jg %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
      
 

      *IP+=5
      break
    }
     case JLE:
    // jle
  
    if ((state.SF ^ state.OF) || state.ZF)
   {
     

     printf("jle %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
     
 
   // jump to destination
    *IP = D
    break
   }
    else
    {
    

      printf("jle %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
      
 

      *IP+=5
      break
    }

//jl 
    case JL:

 
  if (state.SF ^ state.OF)
   {
      

     printf("jl %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
     
    
   // jump to destination
    *IP = D
 
     break
    } 
      else
    {
          

      printf("je %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
      
 
      *IP+=5
      break
    }

  // je

    case JE:
 
    if (state.ZF)
    {
     

     printf("je %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
     
  
       *IP=D
      break
    }
    else
    {
      

      printf("je %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
      
 
      *IP+=5
       break
    } 
  // jne 

    case JNE:
   
   if (!state.ZF)
    {
     

     printf("jne %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
     
 
   // jump to destination
   *IP = D 
    break
    }
   else
   {
    

      printf("jne %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
      
 

      *IP+=5
      break
   }

  //JGE
     case JGE:
    

   printf("jge %.8x ",D)
   
    if (!(state.SF ^ state.OF))
    {
 

     printf("jge %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
 
    
 
     // jump to destination
    *IP = D

      break
    }
    else
    {
     

      printf("jge %.8x (false)   ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
      
 
      *IP+=5
       break
    }
//jmp
 case JMP:
   *IP = D
   

   printf("jmp %.8x (true)  ZF= %d SF = %d OF = %d\n",D,state.ZF,state.SF,state.OF)
   
    break

 default:
   printf("jmp: Error. Exiting...\n")
   exit(EXIT_FAILURE)
   break

  }
}

func
y86_mrmovl(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP
 
  /* get registers */
  union BitField regbyte
  regbyte.byte = mem[*IP + 1]
  int32_t rA_ID = regbyte.half.rA
  int32_t rB_ID = regbyte.half.rB
  int32_t* rA = &state.reg[rA_ID]
  int32_t* rB = &state.reg[rB_ID]

   //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2)
 
  // calculate offset 
  int offset = disp + *rB 

  //store value in rA 
  *rA = *(int*)(mem + offset)
  
  

  char nameRegA[3]
  char nameRegB[3]
  debug_getRegisterName(nameRegA,rA_ID)
  debug_getRegisterName(nameRegB,rB_ID)
  printf("mrmovl (%x), %s    %x -> %s \n",offset,nameRegA,*rA,nameRegA)
  

 //move to next instruction
  *IP += 6
}
func
y86_movsbl(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP
 
  /* get registers */
  union BitField regbyte
  regbyte.byte = mem[*IP + 1]
  int32_t rA_ID = regbyte.half.rA
  int32_t rB_ID = regbyte.half.rB
  int32_t* rA = &state.reg[rA_ID]
  int32_t* rB = &state.reg[rB_ID]

   //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2)
 
  // calculate offset 
  int offset = disp + *rB 

  // get desired byte of data
  char desired_data = *(mem + offset)
  // promote this data to a 32-bit signed int
  *rA = (int)desired_data 

  

  char nameRegA[3]
  debug_getRegisterName(nameRegA,rA_ID)
  printf("movsbl (%x), %s  %x -> %s     \n",offset,nameRegA,*rA,nameRegA)
  

 //move to next instruction
  *IP += 6
}
func
y86_writeb(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP

  /* get registers */ 
  union BitField regbyte
  regbyte.byte = mem[*IP + 1]
  int rA_ID = regbyte.half.rA
  rA *int = &state.reg[rA_ID]

  //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2)

  //calculate offset
  int offset = disp + *rA

 
 // write this byte to the terminal
  

 
  char nameRegA[3]
  debug_getRegisterName(nameRegA,rA_ID)
  printf("writeb (%x) \n",offset)

  
  // get desired byte of data
  char desired_data = mem[offset]
  printf("%c",desired_data)
  
  
 //move to next instruction
  *IP += 6
}
func
y86_writel(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP
 
  /* get registers */ 
  union BitField regbyte
  regbyte.byte = mem[*IP + 1]
  int32_t rA_ID = regbyte.half.rA
  int32_t* rA = &state.reg[rA_ID]

  //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2)

  //calculate offset
  int offset = disp + *rA

 
  // write these 4-bytes to the terminal
 
  // get desired 4-bytes of data
 
  char nameRegA[3]
  debug_getRegisterName(nameRegA,rA_ID)
  printf("writel (%x)\n",offset)
  
  // get desired 4-bytes of data
  int desired_data = *(int*)(mem + offset)
  printf("%x",desired_data)
  


  //move to next instruction
  *IP += 6
}

func
y86_readb(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP

  // read in the byte to store (from the terminal)
  char input[2]
  if (scanf("%c%c",&input[0],&input[1]) != EOF) state.ZF = 0
  else state.ZF = 1
  state.OF = 0
  state.SF = 0

  int converted_input = TTO_byte(input[0],input[1])  
  
  // get offset register, rA
  union BitField regbyte
  regbyte.byte = mem[*IP + 1]
  int32_t rA_ID = regbyte.half.rA
  int32_t* rA = &state.reg[rA_ID]
  
  /* grab 32-bit displacement */
  int disp = *(int*)(mem + *IP + 2)

  //calculate offset
  int offset = disp + *rA

 // write this byte to memory
  *(mem + offset) = converted_input
  

  char nameRegA[3]
  debug_getRegisterName(nameRegA,rA_ID)
  printf("readb %x(%x) (wrote: %c)\n",disp,*rA,converted_input)
  
 
  //move to next instruction
  *IP += 6
}
func 
y86_readl(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP

  // get rA
  union BitField regbyte
  regbyte.byte = mem[*IP + 1]
  int32_t rA_ID = regbyte.half.rA
  int32_t* rA = &state.reg[rA_ID]

  //grab 32-bit displacement
  int disp = *(int*)(mem + *IP + 2)
 
  //calculate offset
  int offset = disp + *rA

  // read in the byte to store 
  int input 
  if(scanf("%x",&input) != EOF) state.ZF = 0
  else state.ZF = 1
  state.SF = 0
  state.OF = 0

 // write 4 bytes to memory
 *(int*)(mem + offset) = input

  

  char nameRegA[3]
  debug_getRegisterName(nameRegA,rA_ID)
  printf("readl (%x) (wrote: %x)\n",offset,input)
  
 
 //move to next instruction
  *IP += 6
} 
func
y86_pushl(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP

  // get rA, the register to push
  union BitField regbyte
  regbyte.byte = mem[*IP + 1]
  int32_t rA_ID = regbyte.half.rA
  int32_t* rA = &state.reg[rA_ID]
  
  // get stack pointer 
  int32_t* rESP = &state.reg[ESP]


  
  int old_rESP = *rESP

  char nameRegA[3]
  debug_getRegisterName(nameRegA,rA_ID)
  printf("pushl %s ESP(%.8x -> %.8x) %x -> %.8x \n",nameRegA,old_rESP,*rESP,*rA,*rESP) 
  
 
  // push: decrement, copy to address pointed by ESP
  *rESP -= 4 
  *(int*)(mem + *rESP) = *rA
 
 
  //increment IP  
  *IP += 2   
}
func
y86_popl(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP

  // get rA, the register to pop to
  union BitField regbyte
  regbyte.byte = mem[*IP + 1]
  int rA_ID = regbyte.half.rA
  rA *int = &state.reg[rA_ID]
 


  // get stack pointer 
  rESP *int = &state.reg[ESP]

  
  int old_rESP = *rESP  

  char nameRegA[3]
  debug_getRegisterName(nameRegA,rA_ID)
  printf("popl %s ESP(%.8x -> %.8x) %x -> %s \n",nameRegA,old_rESP,*rESP,*rA,nameRegA) 
  
 
  // pop: increment ESp, copy from address pointed by ESP to rA,
  // decrement ESP
  *rA = *(int*)(mem + *rESP)
  *rESP += 4


  //increment IP  
  *IP += 2   
}
// push return address onto stack ( address of next instruction)

func
y86_call(state *State){
  mem *int8 = state.ADDRESS_SPACE
  IP *uint = &state.IP

  /* get return address (address of next instruction) */
  int ret_addr = *IP+5
  
  // get stack pointer 
  rESP *int = &state.reg[ESP]

  // push: increment (grows toward negative), copy to address pointed by ESP
  *rESP -= 4
  *(int*)(mem + *rESP) = ret_addr

  /* get jump target (32-bit address) */
  int offset = *(int*)(mem + *IP + 1)

  
  printf("call %.8x  IP(%.8x -> %.8x) ret_addr=%x \n",offset,*IP,offset,ret_addr)
  

  /* jump to destination   */
  *IP = offset
} 
/* return:
  pop return address
  decrement stack pointer 
  set IP to return address
  
*/           
func
y86_ret(state *State){
  rESP *int = &state.reg[ESP]
  mem *int8 = state.ADDRESS_SPACE 
  IP *uint = &state.IP


  // pop return address
  int ret_addr = *(int*)(mem +  *rESP)
 
  
  int old_rESP = *rESP

  printf("ret %.8x ESP(%x -> %x)\n",ret_addr,old_rESP,*rESP+4)
  


  *rESP += 4

  // set IP to return address (jump)
  *IP = ret_addr

} 
