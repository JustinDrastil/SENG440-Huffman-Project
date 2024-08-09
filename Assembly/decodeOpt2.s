        .arch armv4t
        .fpu softvfp
        .eabi_attribute 20, 1
        .eabi_attribute 21, 1
        .eabi_attribute 23, 3
        .eabi_attribute 24, 1
        .eabi_attribute 25, 1
        .eabi_attribute 26, 2
        .eabi_attribute 30, 2
        .eabi_attribute 18, 4
        .file   "DecodeOpt1.c"
        .text
        .align  2
        .global main
        .type   main, %function
main:
        @ Function supports interworking.
        @ args = 0, pretend = 0, frame = 8
        @ frame_needed = 0, uses_anonymous_args = 0
        stmfd   sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
        cmp     r0, #2
        sub     sp, sp, #12
        beq     .L2
        ldr     r1, [r1, #0]
        ldr     r0, .L28
        bl      printf
        mov     r0, #1
.L3:
        add     sp, sp, #12
        ldmfd   sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
        bx      lr
.L2:
        ldr     r0, [r1, #4]
        ldr     r1, .L28+4
        bl      fopen
        cmp     r0, #0
        str     r0, [sp, #4]
        beq     .L24
        mov     r0, #12
        bl      malloc
        mov     r3, #0
        mov     r2, #42
        strb    r2, [r0, #0]
        str     r3, [r0, #4]
        str     r3, [r0, #8]
        ldr     r9, .L28+8
        mov     sl, r0
        mov     r7, r3
        mov     fp, r2
        mov     r8, r3
.L5:
        ldr     r6, [r9, r7, asl #2]
        mov     r5, sl
        mov     r4, #0
        b       .L12
.L8:
        cmp     r3, #49
        bne     .L10
        ldr     r0, [r5, #8]
        cmp     r0, #0
        beq     .L25
.L9:
        add     r4, r4, #1
        mov     r5, r0
.L12:
        ldrb    r3, [r6, r4]    @ zero_extendqisi2
        cmp     r3, #0
        beq     .L26
        cmp     r3, #48
        bne     .L8
        ldr     r0, [r5, #4]
        cmp     r0, #0
        bne     .L9
        add     r0, r0, #12
        bl      malloc
        str     r8, [r0, #4]
        strb    fp, [r0, #0]
        str     r0, [r5, #4]
        str     r8, [r0, #8]
        b       .L9
.L25:
        add     r0, r0, #12
        bl      malloc
        str     r8, [r0, #8]
        strb    fp, [r0, #0]
        str     r0, [r5, #8]
        str     r8, [r0, #4]
        b       .L9
.L26:
        strb    r7, [r5, #0]
.L7:
        add     r7, r7, #1
        cmp     r7, #128
        bne     .L5
        ldr     r0, .L28+12
        ldr     r1, .L28+16
        bl      fopen
        mov     r4, sl
        mov     r5, r0
        b       .L21
.L22:
        cmp     r0, #49
        bne     .L15
        ldr     r4, [r4, #8]
        ldr     r3, [r4, #4]
        cmp     r3, #0
        beq     .L27
.L21:
        ldr     r0, [sp, #4]
        bl      fgetc
        and     r0, r0, #255
        cmp     r0, #48
        bne     .L22
        ldr     r4, [r4, #4]
        ldr     r3, [r4, #4]
        cmp     r3, #0
        bne     .L21
.L27:
        ldr     r3, [r4, #8]
        cmp     r3, #0
        bne     .L21
        ldrb    r0, [r4, #0]    @ zero_extendqisi2
        mov     r1, r5
        bl      fputc
        mov     r4, sl
        b       .L21
.L10:
        ldr     r0, .L28+20
        bl      puts
        b       .L7
.L15:
        ldr     r0, .L28+20
        bl      puts
        ldr     r0, [sp, #4]
        bl      fclose
        mov     r0, r5
        bl      fclose
        ldr     r0, .L28+24
        bl      puts
        mov     r0, #0
        b       .L3
.L24:
        ldr     r0, .L28+28
        bl      perror
        mov     r0, #1
        b       .L3
.L29:
        .align  2
.L28:
        .word   .LC0
        .word   .LC1
        .word   .LANCHOR0
        .word   .LC4
        .word   .LC5
        .word   .LC3
        .word   .LC6
        .word   .LC2
        .size   main, .-main
        .section        .rodata
        .align  2
.LANCHOR0 = . + 0
        .type   lookup, %object
        .size   lookup, 512
lookup:
        .space  128
        .word   .LC7
        .space  4
        .word   .LC8
        .space  16
        .word   .LC9
        .space  16
        .word   .LC10
        .space  4
        .word   .LC11
        .space  72
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
        .word   .LC31
        .word   .LC32
        .word   .LC33
        .word   .LC34
        .word   .LC35
        .word   .LC36
        .word   .LC37
        .space  24
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
        .word   .LC57
        .word   .LC58
        .word   .LC59
        .word   .LC60
        .word   .LC61
        .word   .LC62
        .word   .LC63
        .space  20
        .section        .rodata.str1.4,"aMS",%progbits,1
        .align  2
.LC0:
        .ascii  "Usage: %s <file>\012\000"
        .space  2
.LC1:
        .ascii  "r\000"
        .space  2
.LC2:
        .ascii  "Error opening file\000"
        .space  1
.LC3:
        .ascii  "Error: Invalid Character in Encoded File (not 0 or "
        .ascii  "1)\000"
        .space  2
.LC4:
        .ascii  "decoded.txt\000"
.LC5:
        .ascii  "w\000"
        .space  2
.LC6:
        .ascii  "Decoding completed. Check 'decoded.txt'.\000"
        .space  3
.LC7:
        .ascii  "100\000"
.LC8:
        .ascii  "00111111\000"
        .space  3
.LC9:
        .ascii  "11011001\000"
        .space  3
.LC10:
        .ascii  "001110\000"
        .space  1
.LC11:
        .ascii  "101000\000"
        .space  1
.LC12:
        .ascii  "110110000\000"
        .space  2
.LC13:
        .ascii  "001100010\000"
        .space  2
.LC14:
        .ascii  "001100011\000"
        .space  2
.LC15:
        .ascii  "0011001001\000"
        .space  1
.LC16:
        .ascii  "1101100011\000"
        .space  1
.LC17:
        .ascii  "0011001010\000"
        .space  1
.LC18:
        .ascii  "0011001101\000"
        .space  1
.LC19:
        .ascii  "1101001100\000"
        .space  1
.LC20:
        .ascii  "110100100\000"
        .space  2
.LC21:
        .ascii  "0011000010\000"
        .space  1
.LC22:
        .ascii  "00110000000\000"
.LC23:
        .ascii  "0011000011\000"
        .space  1
.LC24:
        .ascii  "110100111\000"
        .space  2
.LC25:
        .ascii  "001100111\000"
        .space  2
.LC26:
        .ascii  "0011001000\000"
        .space  1
.LC27:
        .ascii  "1101001101\000"
        .space  1
.LC28:
        .ascii  "1101100010011\000"
        .space  2
.LC29:
        .ascii  "1101001010\000"
        .space  1
.LC30:
        .ascii  "110111100\000"
        .space  2
.LC31:
        .ascii  "110111101\000"
        .space  2
.LC32:
        .ascii  "00110010110\000"
.LC33:
        .ascii  "110110001000\000"
        .space  3
.LC34:
        .ascii  "0011001100\000"
        .space  1
.LC35:
        .ascii  "11011000100101\000"
        .space  1
.LC36:
        .ascii  "0011000001\000"
        .space  1
.LC37:
        .ascii  "11011000100100\000"
        .space  1
.LC38:
        .ascii  "1011\000"
        .space  3
.LC39:
        .ascii  "0011110\000"
.LC40:
        .ascii  "101001\000"
        .space  1
.LC41:
        .ascii  "10101\000"
        .space  2
.LC42:
        .ascii  "010\000"
.LC43:
        .ascii  "000110\000"
        .space  1
.LC44:
        .ascii  "001101\000"
        .space  1
.LC45:
        .ascii  "1100\000"
        .space  3
.LC46:
        .ascii  "0111\000"
        .space  3
.LC47:
        .ascii  "00110010111\000"
.LC48:
        .ascii  "00111110\000"
        .space  3
.LC49:
        .ascii  "00010\000"
        .space  2
.LC50:
        .ascii  "000111\000"
        .space  1
.LC51:
        .ascii  "1111\000"
        .space  3
.LC52:
        .ascii  "0110\000"
        .space  3
.LC53:
        .ascii  "1101110\000"
.LC54:
        .ascii  "00110000001\000"
.LC55:
        .ascii  "0010\000"
        .space  3
.LC56:
        .ascii  "0000\000"
        .space  3
.LC57:
        .ascii  "1110\000"
        .space  3
.LC58:
        .ascii  "110101\000"
        .space  1
.LC59:
        .ascii  "11011111\000"
        .space  3
.LC60:
        .ascii  "1101000\000"
.LC61:
        .ascii  "1101001011\000"
        .space  1
.LC62:
        .ascii  "1101101\000"
.LC63:
        .ascii  "11011000101\000"
        .ident  "GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
        .section        .note.GNU-stack,"",%progbits