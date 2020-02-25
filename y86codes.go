package y86

/* y86codes.h
 *
 * Contains defintions for registers, instructions, condition codes
 * status flags.
 * */

/* registers */
const EAX = 0
const ECX = 1
const EDX = 2
const EBX = 3
const ESP = 4
const EBP = 5
const ESI = 6
const EDI = 7
const NOREG = 0xF

/* misc */
const PUSHL = 0xA0
const POPL = 0xB0
const RET = 0x90
const CALL = 0x80
const NOP = 0x00
const HALT = 0x10
const OP1 = 0x60

/* io */
const READB = 0xC0
const READL = 0xC1
const WRITEB = 0xD0
const WRITEL = 0xD1

/* operations */
const ADDL = 0x60
const SUBL = 0x61
const ANDL = 0x62
const XORL = 0x63
const MULL = 0x64
const CMPL = 0x65

/* branches */
const JMP = 0x70
const JLE = 0x71
const JL = 0x72
const JE = 0x73
const JNE = 0x74
const JGE = 0x75
const JG = 0x76

/* moves */
const RRMOVL = 0x20
const IRMOVL = 0x30
const RMMOVL = 0x40
const MRMOVL = 0x50
const MOVSBL = 0xE0

/* status */
const STATUS_AOK = 1
const STATUS_HALT = 2
const STATUS_ADR = 3
const STATUS_INS = 4

/*
 * TODO: Why aren't these used?
 * */

/* condition codes
const ZF = 0x00
const OF = 0x01
const SF = 0x02
*/
