.arch armv4t
.fpu softvfp
.eabi_attribute 20, 1
.eabi_attribute 21, 1
.eabi_attribute 23, 3
.eabi_attribute 24, 1
.eabi_attribute 25, 1
.eabi_attribute 26, 2
.eabi_attribute 30, 6
.eabi_attribute 18, 4
.file "Encode.c"
.section .rodata
.align 2
.LC0: .ascii "100\000"
.LC1: .ascii "00111111\000"
.LC2: .ascii "11011001\000"
.LC3: .ascii "001110\000"
.LC4: .ascii "101000\000"
.LC5: .ascii "110110000\000"
.LC6: .ascii "001100010\000"
.LC7: .ascii "001100011\000"
.LC8: .ascii "0011001001\000"
.LC9: .ascii "1101100011\000"
.LC10: .ascii "0011001010\000"
.LC11: .ascii "0011001101\000"
.LC12: .ascii "1101001100\000"
.LC13: .ascii "110100100\000"
.LC14: .ascii "0011000010\000"
.LC15: .ascii "00110000000\000"
.LC16: .ascii "0011000011\000"
.LC17: .ascii "110100111\000"
.LC18: .ascii "001100111\000"
.LC19: .ascii "0011001000\000"
.LC20: .ascii "1101001101\000"
.LC21: .ascii "1101100010011\000"
.LC22: .ascii "1101001010\000"
.LC23: .ascii "110111100\000"
.LC24: .ascii "110111101\000"
.LC25: .ascii "00110010110\000"
.LC26: .ascii "110110001000\000"
.LC27: .ascii "0011001100\000"
.LC28: .ascii "11011000100101\000"
.LC29: .ascii "0011000001\000"
.LC30: .ascii "11011000100100\000"
.LC31: .ascii "1011\000"
.LC32: .ascii "0011110\000"
.LC33: .ascii "101001\000"
.LC34: .ascii "10101\000"
.LC35: .ascii "010\000"
.LC36: .ascii "000110\000"
.LC37: .ascii "001101\000"
.LC38: .ascii "1100\000"
.LC39: .ascii "0111\000"
.LC40: .ascii "00110010111\000"
.LC41: .ascii "00111110\000"
.LC42: .ascii "00010\000"
.LC43: .ascii "000111\000"
.LC44: .ascii "1111\000"
.LC45: .ascii "0110\000"
.LC46: .ascii "1101110\000"
.LC47: .ascii "00110000001\000"
.LC48: .ascii "0010\000"
.LC49: .ascii "0000\000"
.LC50: .ascii "1110\000"
.LC51: .ascii "110101\000"
.LC52: .ascii "11011111\000"
.LC53: .ascii "1101000\000"
.LC54: .ascii "1101001011\000"
.LC55: .ascii "1101101\000"
.LC56: .ascii "11011000101\000"
.data
.align 2
.type lookup, %object
.size lookup, 512
lookup:
	.word .LC0
	.word .LC1
	.word .LC2
	.word .LC3
	.word .LC4
	.word .LC5
	.word .LC6
	.word .LC7
	.word .LC8
	.word .LC9
	.word .LC10
	.word .LC11
	.word .LC12
	.word .LC13
	.word .LC14
	.word .LC15
	.word .LC16
	.word .LC17
	.word .LC18
	.word .LC19
	.word .LC20
	.word .LC21
	.word .LC22
	.word .LC23
	.word .LC24
	.word .LC25
	.word .LC26
	.word .LC27
	.word .LC28
	.word .LC29
	.word .LC30
	.word .LC31
	.word .LC32
	.word .LC33
	.word .LC34
	.word .LC35
	.word .LC36
	.word .LC37
	.word .LC38
	.word .LC39
	.word .LC40
	.word .LC41
	.word .LC42
	.word .LC43
	.word .LC44
	.word .LC45
	.word .LC46
	.word .LC47
	.word .LC48
	.word .LC49
	.word .LC50
	.word .LC51
	.word .LC52
	.word .LC53
	.word .LC54
	.word .LC55
	.word .LC56
.text
.align 2
.global encode
.type encode, %function
encode:
	stmfd sp!, {fp, lr}
	add fp, sp, #4
	sub sp, sp, #16
	str r0, [fp, #-16]  @ file descriptor
	str r1, [fp, #-20]  @ lookup table pointer

	b .L2
.L3:
	ldr r0, [fp, #-16]
	bl fgetc
	mov r3, r0
	cmp r3, #0
	beq .L4
	ldr r1, [fp, #-20]
	ldr r2, [r1, r3, lsl #2]
	bl fputs
	b .L2
.L4:
	ldmfd sp!, {fp, lr}
	bx lr
	.size encode, .-encode
.text
.align 2
.global main
.type main, %function
main:
	stmfd sp!, {fp, lr}
	add fp, sp, #4
	sub sp, sp, #24
	str r0, [fp, #-16]  @ argc
	str r1, [fp, #-20]  @ argv

	ldr r3, [fp, #-16]
	cmp r3, #2
	bne .L9
	ldr r0, [fp, #-20]
	add r0, r0, #4
	ldr r0, [r0]
	bl fopen
	cmp r0, #0
	beq .L10
	ldr r0, .L13+4
	bl perror
	mov r0, #1
	b .L9
.L10:
	ldr r1, [fp, #-20]
	add r1, r1, #8
	ldr r1, [r1]
	bl fopen
	cmp r0, #0
	beq .L11
	ldr r0, .L13+8
	bl perror
	mov r0, #1
	b .L9
.L11:
	ldr r0, [fp, #-12]
	ldr r1, [fp, #-8]
	bl encode
	ldr r0, [fp, #-12]
	bl fclose
	ldr r0, [fp, #-8]
	bl fclose
	mov r0, #0
.L9:
	ldmfd sp!, {fp, lr}
	bx lr
	.size main, .-main
	.ident "GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section .note.GNU-stack,"",%progbits
