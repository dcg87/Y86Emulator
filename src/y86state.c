#include <stdint.h>
#include <stdlib.h>

#include "y86state.h"
#include "y86fileio.h"
#include "y86exec.h"
#include "y86debug.h"
#include "y86ins.h"
#include "y86codes.h"


/* y86state.c 
 *
 * Holds information about the program state. 
 * */







/*
 * Allocates memory for State.
 * TODO: update error conditons to use fprintf with stderr and exit()
 * */
struct State*
state_CreateState(uint32_t mem_size)
{
  // allocate memory
  struct State* state = malloc(sizeof(struct State));
  
  if (state == NULL)
  {
    printf("state_CreateState(): Failed to allocate memory for state.\n");

    return 0;
  }
  state->ADDRESS_SPACE = calloc(mem_size,sizeof(uint8_t));
  if (state->ADDRESS_SPACE == NULL)
  {
    printf("state_CreateState(): Failed to allocate memory for ADDRESS_SPACE. \n");
    return 0;
  } 
  // set condition codes to nothing
  state->ZF = 0;
  state->SF = 0;
  state->OF = 0;

  // set registers to nil
  uint8_t i = 0;
  for (;i < 9;i++)
  {
    state->reg[i] = 0;
  }

  // and send it back
  return state;
}


/*
 * Frees memory for State
 * */
void
state_destroyState(struct State* state)
{

  free(state->ADDRESS_SPACE);   
  free(state);
} 

