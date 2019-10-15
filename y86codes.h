/* y86codes.h 
 *
 * Contains defintions for registers, instructions, condition codes
 * status flags.
 * */





/* registers */
#define EAX 0
#define ECX 1
#define EDX 2
#define EBX 3
#define ESP 4
#define EBP 5
#define ESI 6
#define EDI 7
#define NOREG 0xF


/* misc */
#define PUSHL 0xA0
#define POPL 0xB0
#define RET 0x90
#define CALL 0x80
#define NOP 0x00
#define HALT 0x10
#define OP1 0x60

/* io */
#define READB 0xC0
#define READL 0xC1
#define WRITEB 0xD0
#define WRITEL 0xD1

/* operations */
#define ADDL 0x60 
#define SUBL 0x61
#define ANDL 0x62
#define XORL 0x63
#define MULL 0x64
#define CMPL  0x65

/* branches */
#define JMP 0x70
#define JLE 0x71
#define JL 0x72
#define JE 0x73
#define JNE 0x74 
#define JGE 0x75
#define JG 0x76

/* moves */
#define RRMOVL 0x20
#define IRMOVL 0x30
#define RMMOVL 0x40
#define MRMOVL 0x50
#define MOVSBL 0xE0


/* status */
#define STATUS_AOK 1
#define STATUS_HALT 2
#define STATUS_ADR 3
#define STATUS_INS 4


/*
 * TODO: Why aren't these used?
 * */

/* condition codes 
#define ZF 0x00
#define OF 0x01
#define SF 0x02
*/


