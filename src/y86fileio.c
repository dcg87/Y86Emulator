#include "y86fileio.h"
#include "y86state.h"
#include "y86util.h"
#include "y86codes.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* y86fileio.c 
 *
 * Describes how data from a source file (.y86) is read into memory. 
 * */

/*
 * error()
 * input: pointer to a file
 * output: 0
 *
 * Prints an error message and then closes the file.
 * */

void
error(FILE* file)
{ 
  printf("Error: Bad input.\n Exiting...\n");
  fclose(file);
}
   
/*
 * Finite state machine event describing what to
 * do when a '.' is found in file.
 * */
void 
dot_found(FILE* file,struct State* state)
{

 int8_t input = fgetc(file);
  
  switch(input)
  {
    case 's':
      s_found(file,state);
      break;
    case 't':
      store_text(file,state);
      break;
    case 'b':
      b_found(file,state);
      break;
    case 'l':
      store_long(file,state);
      break;
    default:
      error(file);
      break;
  } 
       
}

/*
 * Store a byte in state
 * */

void
store_byte(FILE* file, struct State* state)
{
  uint32_t address = 0;
  char data[50];

  /* move past directive */  
  fscanf(file,"%s",data);
  /* get address byte */
  fscanf(file,"%s",data);
  /* convert address string to hex */ 
  address = strtol(data,NULL,16);
  /* get byte string */
  fscanf(file,"%s",data);
   //printf("Retrieved '%s'...\n",data);

  /* convert byte string to hex */
  long int value = strtol(data,NULL,16);

 /* store byte */
  #if DEBUG
  printf(".byte %#x %lx \n",address,value); 
  #endif
  *(state->ADDRESS_SPACE + address) = value;
  }
/*
 * Event triggered when ".size" is found in file. 
 * Reallocates state to the appropriate size.
 * */
void
store_size(FILE* file,struct State* state )
{
  char* input = malloc(8*sizeof(char));
  
  /* move past directive */  
  fscanf(file,"%s",input);
  /* get size */
  fscanf(file,"%s",input);
 

  /*
 *
 *  TODO:
 *  catch size too big    
 *
 *   */ 
  /* convert from hex string to int */
  int size = strtol(input,NULL,16);
  free(input); 


  state->reg[ESP] = size-1;
  /* realloate to new size */
  #if DEBUG
  printf(".size %.2x \n",size);
  #endif
  state->ADDRESS_SPACE =  realloc(state->ADDRESS_SPACE,size*sizeof(char));
  state->mem_size = size;
}
void
store_bss(FILE* file,struct State* state )
{
   #if DEBUG
   #endif

   int address;
   int size;
  char* value_str = malloc(8*sizeof(char));

  /* move past directive */  
  fscanf(file,"%s",value_str);
  /* get address of data */
  fscanf(file,"%s",value_str);
  /* convert address to hex */ 
  address = strtol(value_str,NULL,16);
  /* get size */
  fscanf(file,"%s",value_str);
 
  size = strtol(value_str,NULL,16);
  #if DEBUG
  printf(".bss %#x \n",size); 
  #endif
  /* Allocate data */
  memset((state->ADDRESS_SPACE + address),0,size*sizeof(char));
  free(value_str); 

}
/*
 * Event triggered when ".text" is found in file.
 * Stores machine instructions in state.
 * 
 * todo: remove the code setting the IP. 
 * it should be its own function.
 * */
void
store_text(FILE* file, struct State* state)
{
  int address;
  char* value = malloc(0xFFFF*sizeof(char));
  if (value == NULL)
  {
    printf("Error. malloc failed.\n");
    return;
  }
  // junk
  fscanf(file,"%s",value); // 'ext'

  // get address
  fscanf(file,"%s",value); // '0'
  address = strtol(value,NULL,16); 
  state->IP = address;
  // get machine instructions
  fscanf(file,"%s",value); // 'j0230402340320'
 
  #if DEBUG
  printf(".text %#x %s \n",address,value); 
  #endif 

  int n = strlen(value);
  int i = 0;
  int pos = 0;
  for (;i+1 < n;i+=2)
  {
   int8_t a = value[i];
   int8_t b;
    if (i + 1 >= n )
    {
      b = '0';
    }
    else
    {
      b = value[i+1];
    } 
    
  *(state->ADDRESS_SPACE + address + pos) = TTO_byte(a,b);
   pos++;
  } 
  free(value); 
}
    /* store machine instructions */
  /* 
   strcpy((state->ADDRESS_SPACE + address),value); // segfault
  //free(value); 
  printf("Freed value...\n"); 
  */ 

/*
 * Event triggered when ".long" is found in file.
 * Stores a 4-byte little-endian integer in state
 * */
void
store_long(FILE* file, struct State* state )
{
  char* value_str = malloc(0xFFFF*sizeof(char));

  /* move past directive */  
  fscanf(file,"%s",value_str);
  
  /* get address string */
  fscanf(file,"%s",value_str);
  /* convert to hex */ 
  int address = strtol(value_str,NULL,16);
 
  fscanf(file,"%s",value_str);
  int value = strtol(value_str,NULL,16);
  free(value_str);
 
 /* store long */
    
  *(int*)(state->ADDRESS_SPACE + address) = value;
  #if DEBUG
  printf(".long %x %x \n",address,value);
  #endif
}

/*
 * Event triggered when the character 'b' is found in file.
 * */
void
b_found(FILE* file, struct State* state)
{
 int8_t input = fgetc(file);
  
  switch(input)
  {
    case 'y':
      store_byte(file,state);
      break;
    case 's':
      store_bss(file,state);
      break;
    default:
      error(file);
  }

}
/*
 * Event triggered when 's' is found in file.
 */
void
s_found(FILE* file, struct State* state )
{
 int8_t input = fgetc(file);
  switch(input)
  {
    case 't':
      store_string(file,state);
      break;
    case 'i':
      store_size(file,state); 
      break;
    default:
      error(file);
  }
}
/*
 * Event triggered when ".string" is found in file.
 * Stores a string in state.
 * */
void
store_string(FILE* file,struct State* state)
{

  int address;
  char* value = malloc(100*sizeof(char));

  // junk
  fscanf(file,"%s",value); 

  fscanf(file,"%s",value);
  
  address = strtol(value,NULL,16);
  
  memset(value,0,strlen(value)*sizeof(char));

  char* tmp = malloc(0xFFFF*sizeof(char));
  fscanf(file,"%s",tmp);
  strcat(value,tmp);
  strcat(value," ");
  while(tmp[strlen(tmp)-1] != '"')     
  {
    
    fscanf(file,"%s",tmp);
    strcat(value,tmp);
    strcat(value," ");

  }
  free(tmp);
  // remove extra " "
//  value[strlen(value)-1] = ' ';


  //TODO: remove these/find better solution? 
//  strip(value);
  shrink(value);  

  /* store string in state */  
  #if DEBUG
//  printf("Storing '%s' at %#.2x...\n",value,address); 
  printf(".string %#.2x %s \n",address,value);
  #endif
  memcpy((state->ADDRESS_SPACE + address),value,strlen((char*)value));
  free(value); 
  //printf("Freed value...\n");
}
/*
 * Starting point for finite state machine. 
 * Loads data and instructions into state.
 * */
void
loadFile(FILE* file,struct State* state)
{
  #if DEBUG
  printf("Loading file...\n");
  #endif 
  while (!feof(file))
  {

   int8_t input = fgetc(file);
    if (input == '.')
    {
      dot_found(file,state);
    }
  }
  
}

