#ifndef UTIL_H
#define UTIL_H



/* y86util.h
 * Declares useful functions that are not directly related to emulation. 
 * */
#include <stdint.h>
#include <stdio.h>
#include <string.h>


/*
  removes excess bytes from a string 
*/
void
shrink(char*);
/* 
  removes quotes from a string. 
*/
void
strip(char*);
/*TTO_byte()
 * paramters: char a, char b,
 * results: merges a,b into char c, returns c
 *
  Two-to-one byte. 
  Merges two bytes into one byte, assuming that each
  each has no hi-bits.
  Created to solve the issue of "00" in the source file
  using two bytes but representing one byte.
  e.g.)
      "F2" = 0000 1111 0000 0010 (two bytes)

       F 0000 1111 << 4 =  1111 0000
       2 0000 0010       | 0000 0010
                         -------------
                     F2 =  1111 0010  (one byte)
       
*/
char
TTO_byte(char, char);
/*
  converts a character to an integer
  e.g.)
      '0' -> 0
      'F' -> F
*/

/*
 * char_to_int()
 * parameters: char c, where c's bit-pattern represents
 * the character form of a valid hex digit.
 * results: returns the char d whose bit-pattern represents
 * the numerical form of the character represented by c's bit-pattern.
 *
 * e.g.)
 *      Let c = 'A'. Then c's bit-pattern is 0100 0001.
 *      d's bit-pattern is coverted to 0001 0000, so d = A.
 *      */
char
char_to_int(char);
/*
 *printMemory()
 *paramters: const char pointer to memory block,
  int a represeting the starting index, int b representing the 
  end index
  results:
  Outputs to stdout. Prints the address and contents of each byte of memory
  within range r: a <= r < b 
  
*/
/*
void
reverse(char*);
*/
void 
swap(char*,char*);

void
statusCodeToStr(int,char*);

void
show_bytes(char* start, int len);
void
show_int(int x);
#endif
