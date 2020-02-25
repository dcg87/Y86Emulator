#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "y86util.h"
#include "y86state.h"
#include "y86codes.h"

/* y86util.c 
 *
 * Implements useful functions not directly related to emulation.
 * */

char
TTO_byte(char a, char b)
{
  
   /* change the bit pattern */
   a = char_to_int(a);
   b = char_to_int(b);

   a <<= 4;
   a |= b;
  
   return a; 
}

char
char_to_int(char ch)
{
 if (ch >= '0' && ch <= '9')
  {
    return ch - '0';
  }
  else if (ch >= 'A' && ch <= 'F')
  {
    return ch - 55;
   }
  else if (ch >= 'a' && ch <= 'f')
  {
    return ch - 87;
  } 
  else
  {
    printf("char_to_int(): error. invalid data. exiting...\n"); 
    exit(-1);
  }
} 
/* 
 * Modifies pointer
 * */

void
strip(char* str)
{
  size_t len = strlen(str);
  
  for (size_t k = 1;k < len;k++)
  {
    str[k-1] = str[k];
  }
  str[len-1] = 0;
  str[len-2] = 0;
  str[len-3] = 0;
} 
void
shrink(char* str)
{
  size_t len = strlen((char*)str);
  str = realloc(str,len*sizeof(char));  
}
  /* 
void
reverse(char* str)
{
  uint32_t n = strlen(str) / 2;
  int i = 0;
  uint32_t j = strlen(str) - 1;
  while (i < n)
  {
    swap(&str[i],&str[j]);
    i++;
    j--;
  }
} 
*/

void
swap(char* a, char* b)
{
  const char tmp = *a;
  *a = *b;
  *b = tmp;
}
void
statusCodeToStr(int status, char* output)
{

  switch(status)
  {
    case STATUS_AOK:
      strcpy(output,"AOK");
      break;
    case STATUS_HALT:
      strcpy(output,"HALT");
      break;
    case STATUS_ADR:
      strcpy(output,"ADR");
      break;
    case STATUS_INS:
      strcpy(output,"INS");

    default:
      printf("statusCodeToStr: Error. Exiting... \n");
      exit(EXIT_FAILURE);
      break;
  }
}
void 
show_bytes(char* start, size_t len)
{

 for (size_t i = 0; i < len; i++)
 printf(" %.2x", start[i]);
printf("\n");

 }  

void
show_int(int x) {
show_bytes((char*) &x, sizeof(int));
}
