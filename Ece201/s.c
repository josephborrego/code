// ECE 201 MP4
// Stage 2
// Need to be translated to MIPS assembly language and run on SPIM
#include <stdio.h>
#include <stdlib.h>
// variables in the simulator program that simulate features of the
// MIPS architecture. Here, r[] and m[] are just arrays in the memory
long r[32];
long ir,pc,a,b,aluout,mdr;
 // The machine code in simulated memory is
 // for childish division using only the instructions
 // implemented in Ch 5 of P&H. Uses lw of constants
 // provided in memory, and a sw at the end:
 // lw $a0, x($zero)
 // lw $a1, y($zero)
 // lw $t3, one($zero)
 // add $t1, $zero, $a0
 // add $t2, $zero, $zero
 //L1: slt $t4, $t1, $a1
 // beq $t4, $t3, L2
 // sub $t1, $t1, $a1
 // add $t2, $t2, $t3
 // j L1
 //L2: add $v0, $t2, $zero
 // j L3
 //x: .word 14
 //y: .word 7
 //one:.word 1
 //z: .word 0
 //L3: sw $t2, z($zero)
 // lw $s1, z($zero)
 //self:beq $zero, $zero, self
 // Can change m[12] and m[13] to see different quotients computed
#define MAXMEM 19
long m[MAXMEM] = {0x8c040030,
 0x8c050034,
 0x8c0b0038,
 0x00044820,
 0x00005020,
 0x0125602a,
 0x118b0003,
 0x01254822,
 0x014b5020,
 0x08000005,
 0x01401020,
 0x08000010,
 0x0000000e,
 0x00000007,
 0x00000001,
 0x00000000,
 0xac0a003c,
 0x8c11003c,
 0x1000ffff};
// This function uses the built-in casting of C to do sign extension
// if x is 0xxx xxxx xxxx xxxx,
// the result will be:
// 0000 0000 0000 0000 0xxx xxxx xxxx xxxx
// if x is 1xxx xxxx xxxx xxxx,
// the result will be:
// 1111 1111 1111 1111 1xxx xxxx xxxx xxxx
long signext(short x)
{
 return(x); //need more than this in SPIM
}
// Prevent access of memory outside bounds of m[] array
// print error and halt if outside

// ECE 201 MP4
// Stage 1
// Need to be translated to MIPS assembly language and run on SPIM
#include <stdio.h>
#include <stdlib.h>
//#define MAXMEM 13
// variables in the simulator program that simulate features of the
// MIPS architecture. Here, r[] and m[] are just arrays in the memory
//long r[32];
//long ir,pc,a,b,aluout;
//long m[MAXMEM] = { ...Babbage machine language from previous problems ... };
// This function simulates the subset of R-type instructions
// all other possible MIPS func codes return 0, rather than
// the correct result
long alufunc(long a, long b, int func)
{
 long ia,ib;
 if (func == 32) //add
return (a + b);
 else if (func == 34) //sub
return (a - b);
 else if (func == 36) //and
return (a & b);
 else if (func == 37) //or
return (a | b);
 else if (func == 39) //nor
 return (~(a|b));
 else if (func == 42) //slt
return ((a<b) ? 1 : 0);
 else
return(0);
}
// This function extracts a subset of bits from the middle of a
// 32-bit word. It is assumed 31 >= left >= right >= 0
// For example, extract(0x12345678,23,16) returns 0x34
long extract(long x, int left, int right)
{
 unsigned long mask,result;
 mask = 1;
if (left==31)
 mask = 0xFFFFFFFF;
 else
 mask = (mask << (left+1)) - 1;
 result = (x&mask);
 if (right!=0)
 result = result >> right;
 return (result);
}
//Print one hexadecimal char '0' .. '9' or 'A' .. 'F'
void hexdig(long dig)
{
 if (dig < 10)
 printf("%c",dig+'0');
 else
 printf("%c",dig+'A'-10);
}
// Print 32-bit value as hexadecimal
// There is quite a bit that has to be done here to
// translate to MIPS assembly language. The value needs to
// be broken into 8 ASCII chars by calls to extract and hexdig
void printhex(long x)
{
 hexdig(extract(x,31,28));
 hexdig(extract(x,27,24));
 hexdig(extract(x,23,20));
 hexdig(extract(x,19,16));
 hexdig(extract(x,15,12));
 hexdig(extract(x,11,8));
 hexdig(extract(x,7,4));
 hexdig(extract(x,3,0));
}
void address_check(unsigned long addr)
{
 if (addr >= (MAXMEM<<2))
 {
 printf("memory out of bounds");
 printhex(addr);
 printf("\n");
 exit(1); //C function that stops this simulation program, i.e. syscall 10
 }
}
// Print error message if instruction is not among those in the P&H subset
void unimplemented()
{
 printf("unimplemented instruction");
 printhex(ir);
 printf("\n");
 exit(1);
}

void traceout()
{
printf("pc="); //print a string in memory, e.g. syscall 4
printhex(pc);
printf(" ir=");
printhex(ir);
printf(" a=");
printhex(a);
printf(" b=");
printhex(b);
printf(" aluout=");
printhex(aluout);
printf("\n");
printf(" v0=");
printhex(r[2]);
printf(" a0=");
printhex(r[4]);
printf(" a1=");
printhex(r[5]);
printf(" t1=");
printhex(r[9]);
printf(" t2=");
printhex(r[10]);
printf(" t4=");
printhex(r[12]);
printf("\n");
printf(" s1=");
printhex(r[17]);
printf(" s2=");
printhex(r[18]);
printf(" s3=");
printhex(r[19]);
printf(" s4=");
printhex(r[20]);
printf(" s5=");
printhex(r[21]);
printf("\n");
printf("\n");
// getchar();
}
int main(void)
{
 int opcode; //not allowed in hardware, substitute ir[31:26] instead
 pc = 0;
 ir = 0;
 mdr = 0;
 while(ir != 0x1000ffff) //would be infinite loop in hardware
 {
address_check(pc);
ir = m[pc>>2];
pc = pc + 4;
a = r[extract(ir,25,21)];
b = r[extract(ir,20,16)];
aluout = pc + (signext(extract(ir,15,0))<<2);
traceout();
opcode = extract(ir,31,26);
if (opcode==0)
 { //r-type
aluout = alufunc(a,b,extract(ir,10,0));
if (extract(ir,15,11) != 0) //not in hardware--prevent losing 0 in R0
 {
 r[extract(ir,15,11)] = aluout;
 }
 }
else if (opcode==2)
 { // j
pc = (extract(pc,31,28)<<28) | (extract(ir,25,0)<<2);
 }
else if (opcode==4)
 { // beq
pc = ((a==b)? aluout : pc);
 }
else if ((extract(ir,31,30)==2)&&(extract(ir,28,26)==3))
 { //lw,sw: 35 or 43, in binary: 10x011
aluout = a + signext(extract(ir,15,0));
address_check(aluout);
if (extract(ir,29,29))
 m[aluout>>2] = b;
else
 {
 mdr = m[aluout>>2];
 if (extract(ir,20,16) != 0) //not in hardware--prevent losing 0 in R0
{
 r[extract(ir,20,16)] = mdr;
}
 }
 }
else
 unimplemented();
 }
return 0;
 }
