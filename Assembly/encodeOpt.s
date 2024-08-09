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
    .file   "encodeOpt.s"

    .section .rodata
    .align  2
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
    .align  2
    .type   lookup, %object
    .size   lookup, 512
lookup:
    .space  128
    .word   .LC0
    .space  4
    .word   .LC1
    .space  16
    .word   .LC2
    .space  16
    .word   .LC3
    .space  4
    .word   .LC4
    .space  72
    .word   .LC5
    .word   .LC6
    .word   .LC7
    .word   .LC8
    .word   .LC9
    .word   .LC10
    .word   .LC11
    .word   .LC12
    .word   .LC13
    .word   .LC14
    .word   .LC15
    .word   .LC16
    .word   .LC17
    .word   .LC18
    .word   .LC19
    .word   .LC20
    .word   .LC21
    .word   .LC22
    .word   .LC23
    .word   .LC24
    .word   .LC25
    .word   .LC26
    .word   .LC27
    .word   .LC28
    .word   .LC29
    .word   .LC30
    .space  24
    .word   .LC31
    .word   .LC32
    .word   .LC33
    .word   .LC34
    .word   .LC35
    .word   .LC36
    .word   .LC37
    .word   .LC38
    .word   .LC39
    .word   .LC40
    .word   .LC41
    .word   .LC42
    .word   .LC43
    .word   .LC44
    .word   .LC45
    .word   .LC46
    .word   .LC47
    .word   .LC48
    .word   .LC49
    .word   .LC50
    .word   .LC51
    .word   .LC52
    .word   .LC53
    .word   .LC54
    .word   .LC55
    .word   .LC56

    .align  2
input_fp:  .word 0x00000000   @ Placeholder for input file pointer
output_fp: .word 0x00000000   @ Placeholder for output file pointer

    .text
    .align 2
    .global main
    .type   main, %function
main:
    ldr r0, =input_fp     @ Load the address of the input file pointer
    ldr r1, =output_fp    @ Load the address of the output file pointer
    bl encode             @ Call the encode function
    mov r0, #0            @ Return code 0
    bx lr                 @ Return from function

    .global encode
    .type   encode, %function
encode:
    stmfd   sp!, {fp, lr}       @ Save frame pointer and link register
    add     fp, sp, #4          @ Set up frame pointer
    sub     sp, sp, #32         @ Allocate stack space for local variables
    str     r0, [fp, #-16]      @ Save input file pointer (r0) at [fp, #-16]
    str     r1, [fp, #-20]      @ Save output file pointer (r1) at [fp, #-20]
    mov     r2, #0              @ Initialize buffer index (r2) to 0
    mov     r4, #0              @ Initialize buffer for output (r4) to 0

read_loop:
    ldr     r3, [fp, #-16]      @ Load input file pointer from stack
    bl      fgetc               @ Read a character from the input file
    cmp     r0, #0              @ Check if end of file (EOF) is reached
    beq     end_loop            @ If EOF, exit the loop

    cmp     r0, #32             @ Compare character to ASCII space (' ')
    blo     invalid_char        @ If character is less than space, it's invalid
    cmp     r0, #122            @ Compare character to ASCII 'z'
    bhi     invalid_char        @ If character is greater than 'z', it's invalid

    ldr     r2, =lookup         @ Load address of the lookup table
    ldr     r3, [r2, r0, lsl #2]@ Load encoded string address from lookup table
    cmp     r3, #0              @ Check if the lookup returned a valid string
    beq     invalid_char        @ If no valid string, treat character as invalid

    ldr     r4, [fp, #-20]      @ Load output file pointer from stack
    bl      fputs               @ Write the encoded string to the output file
    b       read_loop           @ Continue with the next character

invalid_char:
    ldr     r2, =invalid_char_str  @ Load the address of the invalid character string
    ldr     r3, [fp, #-20]      @ Load output file pointer from stack
    bl      fputs               @ Write the invalid character message to output
    b       read_loop           @ Continue with the next character

end_loop:
    ldmfd   sp!, {fp, lr}       @ Restore frame pointer and link register
    mov     sp, fp              @ Restore stack pointer
    bx      lr                  @ Return from function

    .size   main, .-main
    .size   encode, .-encode
    .ident  "GCC: (GNU) 4.9.2"
