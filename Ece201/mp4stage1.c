#this is a program in mips assembly

		.data

#Stores all strings the program needs to print out
space: .asciiz " "
str1: .asciiz "done"
nl: .asciiz "\n"
pc: .asciiz "pc = "
ir: .asciiz "ir = "
a: .asciiz "a = "
B: .asciiz "b = "
aluout: .asciiz "aluout = "
v0: .asciiz "v0 = "
a0: .asciiz "a0 = "
a1: .asciiz "a1 = "
t1: .asciiz "t1 = "
t2: .asciiz "t2 = "
t4: .asciiz "t4 = "
s1: .asciiz "s1 = "
s2: .asciiz "s2 = "
s3: .asciiz "s3 = "
s4: .asciiz "s4 = "
s5: .asciiz "s5 = "

#Array that represents the values of all 32 MIPS registers
#r[8] (t0) is initially 6, r[10] (t2) is initially 1, and r[17] (s1) is initially 1 
r:		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000006   	#r[8] aka $t0
		.word 0x00000000
		.word 0x00000001	#r[10] aka $t2	
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000001	#r[17] aka $s1
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000
		.word 0x00000000


#Array that stores the Babbage program instructions as words
m: .word 0x01284820, 0x01495020, 0x022a9020, 0x01284820, 0x01495020, 0x024a9820, 0x01284820, 0x01495020, 0x026aa020, 0x01284820, 0x01495020, 0x028aa820,0x1000ffff

#Labeled the last instruction to reference in the main method (used to kill the while loop)
last: .word 0x1000ffff


		.text
		.globl main

#Main method
		
main:		#load address of memory array into $s0
		la $s0, m


loadinst:	#load word address of memory into $s1 and operate
		lw $s1, 0($s0)	
		jal extract

		
		#load last address signifying end of while loop
		la $t9, last

		#if current address is the last address, then quit the program	(don't enter loop)
		beq $t9, $s0, quit

		#save result from alufunc
		jal alufunc
		sw $t1, 0($s4)
		addi $t9, $t1, 0

		#do traceout to print all the values that we need
		jal traceout


		#add to the program counter and load the next instruction
		addi $s0, $s0, 4
		j loadinst

quit:		#quit program if it is the last word address
		li $v0, 10
		syscall







#simulates the operation of the actual r-type instruction
alufunc:
		#add all values to compare against in temporary registers
		addi $t0, $zero, 32
		addi $t1, $zero, 34
		addi $t2, $zero, 36
		addi $t3, $zero, 37
		addi $t4, $zero, 39
		addi $t5, $zero, 42
	
		#do the comparisons and jump to the correct operation
		beq $t0, $s6, plus
		beq $t1, $s6, minus
		beq $t2, $s6, andd
		beq $t3, $s6, orr
		beq $t4, $s6, norr
		beq $t5, $s6, sltt


plus:		#do the addition if it is an add and clear the temp register
		add $t1, $s7, $s6
		sub $t0, $t0, $t0
		jr $ra
	
minus:		#do the subtraction if it is a subtraction and clear the temp register
		sub $t1, $s7, $s6
		sub $t1, $t1, $t7
		jr $ra

andd:		#do the and if it is an and and clear the temp register
		and $t1, $s7, $s6
		sub $t2, $t2, $t2
		jr $ra

orr:		#do the or if it is an or and clear the temp register
		or $t1, $s7, $s6
		sub $t3, $t3, $t3
		jr $ra
		
norr:		#do the nor if it is a nor and clear the temp register
		nor $t1, $s7, $s6
		sub $t4, $t4, $t4
		jr $ra

sltt:		#do the slt if it is an slt and clear the temp register
		slt $t1, $s7, $s6
		sub $t5, $t5, $t5
		jr $ra


#extracts the bits out of a word to the correct locations (registers) so we can read and print correctly
extract:	
		#get func code in correct spot
		srl $s5, $s1, 26
		sll $s6, $s1, 26
		srl $s6, $s6, 26

		#get rs in the correct spot
		sll $s2, $s1, 6
		srl $s2, $s2, 27
		#Mult by 4
		sll $s2, $s2, 2

		#get rt in the correct spot		
		sll $s3, $s1, 11
		srl $s3, $s3, 27
		#Mult by 4
		sll $s3, $s3, 2

		#get rd in correct spot	and address of rd
		sll $s4, $s1, 16
		srl $s4, $s4, 27
		#mult by 4
		sll $s4, $s4, 2

		#Get address of rd to store aluout at
		la $t8, r
		add $s4, $t8, $s4

		#get value of rs into register to print 
		add $s7, $t8, $s2
		lw $s7, 0($s7)

		#get address of rt into register to print
		add $s6, $t8, $s3
		lw $s6, 0($s6)

		#return
		jr $ra

#prints the hex value of the register
hexdig:
		#if it is a number less than 10 then print the number
		slti $t7, $a0, 10
		beq $t7, $zero, char
		li $v0, 1
		syscall
		jr $ra


		
		#if it isn't then add 55 to make it an ascii letter (Ascii value of 'A' - 10) and print
char:		addi $a0, $a0, 65
		addi $a0, $a0, -10
		li $v0, 11
		syscall
		jr $ra


#prints entire register value as a hex value
printhex:
		#save return address
		addi $t5, $ra, 0
		
		#print first four bits in hex
		add $t0, $a0, $zero
		srl $a0, $a0, 28
		jal hexdig

		#print next four as one hex value
		sll $a0, $t0, 4
		srl $a0, $a0, 28
		jal hexdig
				
		#print next four as one hex value
		sll $a0, $t0, 8
		srl $a0, $a0, 28
		jal hexdig

		#print next four as one hex value
		sll $a0, $t0, 12
		srl $a0, $a0, 28
		jal hexdig

		#print next four as one hex value
		sll $a0, $t0, 16
		srl $a0, $a0, 28
		jal hexdig

		#print next four as one hex value
		sll $a0, $t0, 20
		srl $a0, $a0, 28
		jal hexdig

		#print next four as one hex value
		sll $a0, $t0, 24
		srl $a0, $a0, 28
		jal hexdig

		#print next four as one hex value
		sll $a0, $t0, 28
		srl $a0, $a0, 28
		jal hexdig

		#return
		jr $t5

#prints everything the assignment specifies that we need to print out
traceout:	
		#save return address
		addi $t4, $ra, 0

		#print pc value
		li $v0, 4
		la $a0, pc
		syscall
		la $t3, m
		sub $a0, $s0, $t3
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print ir value
		li $v0, 4
		la $a0, ir
		syscall
		add $a0, $s1, $zero
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall
		
		#print a value
		li $v0, 4
		la $a0, a
		syscall
		move $a0, $s7
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall
	
		#print b value
		li $v0, 4
		la $a0, B
		syscall
		move $a0, $s6
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall
		
		#print aluout value
		li $v0, 4
		la $a0, aluout
		syscall
		addi $a0, $t9, 0
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print new line			
		li $v0, 4
		la $a0, nl
		syscall

		#print v0 value
		li $v0, 4
		la $a0, v0
		syscall
		la $a0, r
		lw $a0, 8($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print a0 value
		li $v0, 4
		la $a0, a0
		syscall
		la $a0, r
		lw $a0, 16($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall
		 
		#print a1 value
		li $v0, 4
		la $a0, a1
		syscall
		la $a0, r
		lw $a0, 20($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print t1 value
		li $v0, 4
		la $a0, t1
		syscall
		la $a0, r
		lw $a0, 36($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print t2 value
		li $v0, 4
		la $a0, t2
		syscall
		la $a0, r
		lw $a0, 40($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print t4 value
		li $v0, 4
		la $a0, t4
		syscall
		la $a0, r
		lw $a0, 48($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print new line
		li $v0, 4
		la $a0, nl
		syscall

		#print s1 value
		li $v0, 4
		la $a0, s1
		syscall
		la $a0, r
		lw $a0, 68($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print s2 value
		li $v0, 4
		la $a0, s2
		syscall
		la $a0, r
		lw $a0, 72($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print s3 value
		li $v0, 4
		la $a0, s3
		syscall
		la $a0, r
		lw $a0, 76($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print s4 value
		li $v0, 4
		la $a0, s4
		syscall
		la $a0, r
		lw $a0, 80($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print s5 value
		li $v0, 4
		la $a0, s5
		syscall
		la $a0, r
		lw $a0, 84($a0)
		jal printhex

		#print space
		li $v0, 4
		la $a0, space
		syscall

		#print new line
		li $v0, 4
		la $a0, nl
		syscall

		#print another new line
		li $v0, 4
		la $a0, nl
		syscall		
	
		#return
		jr $t4
		
	



 

