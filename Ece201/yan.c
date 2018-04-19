// ECE 201 MP4
// Stage 1
// Need to be translated to MIPS assembly language and run on SPIM
#include <stdio.h>
#include <stdlib.h>
#define MAXMEM 13
// variables in the simulator program that simulate features of the
// MIPS architecture. Here, r[] and m[] are just arrays in the memory
long r[32];
long ir,pc,a,b,aluout;
long m[MAXMEM] = { 0x01284820, 0x01495020, 0x022a9020, 0x01284820, 0x01495020, 0x024a9820, 0x01284820, 0x01495020, 0x026aa020, 0x01284820, 0x01495020, 0x028aa820,0x1000ffff };
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

long signext(short x)
{
 return(x); //need more than this in SPIM
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

void unimplemented()
{
 printf("unimplemented instruction");
 printhex(ir);
 printf("\n");
 exit(1);
}


// This function extracts a subset of bits from the middle of a
// 32-bit word. It is assumed 31 >= left >= right >= 0
// For example, extract(0x12345678,23,16) returns 0x34
long extract(long x, int left, int right)
{
 unsigned long mask,result;
 mask = 1;
if (left==31)
 mask = 0xFFFFFFFF
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
// Print registers of interest in childish division program
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
// getchar();
}
void main()
{
 int opcode; //convenient to use local since compared multiple times
 r[8] = 6; //t0 = 6 as needed by Babbage
 r[10] = 1; //t2 = 1 as needed by Babbage
 r[17] = 1; //s1 = 1 as needed by Babbage
 pc = 0;
 ir = 0;
 while(ir != 0x1000ffff) //would be infinite loop in hardware
 {
ir = m[pc>>2];
pc = pc + 4;
a = r[extract(ir,25,21)];
b = r[extract(ir,20,16)];
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
 }
 }
