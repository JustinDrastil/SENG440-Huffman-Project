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
        .file   "DecodeOpt1.c"
        .section        .rodata
        .align  2
.LC0:
        .ascii  "100\000"
        .align  2
.LC1:
        .ascii  "00111111\000"
        .align  2
.LC2:
        .ascii  "11011001\000"
        .align  2
.LC3:
        .ascii  "001110\000"
        .align  2
.LC4:
        .ascii  "101000\000"
        .align  2
.LC5:
        .ascii  "110110000\000"
        .align  2
.LC6:
        .ascii  "001100010\000"
        .align  2
.LC7:
        .ascii  "001100011\000"
        .align  2
.LC8:
        .ascii  "0011001001\000"
        .align  2
.LC9:
        .ascii  "1101100011\000"
        .align  2
.LC10:
        .ascii  "0011001010\000"
        .align  2
.LC11:
        .ascii  "0011001101\000"
        .align  2
.LC12:
        .ascii  "1101001100\000"
        .align  2
.LC13:
        .ascii  "110100100\000"
        .align  2
.LC14:
        .ascii  "0011000010\000"
        .align  2
.LC15:
        .ascii  "00110000000\000"
        .align  2
.LC16:
        .ascii  "0011000011\000"
        .align  2
.LC17:
        .ascii  "110100111\000"
        .align  2
.LC18:
        .ascii  "001100111\000"
        .align  2
.LC19:
        .ascii  "0011001000\000"
        .align  2
.LC20:
        .ascii  "1101001101\000"
        .align  2
.LC21:
        .ascii  "1101100010011\000"
        .align  2
.LC22:
        .ascii  "1101001010\000"
        .align  2
.LC23:
        .ascii  "110111100\000"
        .align  2
.LC24:
        .ascii  "110111101\000"
        .align  2
.LC25:
        .ascii  "00110010110\000"
        .align  2
.LC26:
        .ascii  "110110001000\000"
        .align  2
.LC27:
        .ascii  "0011001100\000"
        .align  2
.LC28:
        .ascii  "11011000100101\000"
        .align  2
.LC29:
        .ascii  "0011000001\000"
        .align  2
.LC30:
        .ascii  "11011000100100\000"
        .align  2
.LC31:
        .ascii  "1011\000"
        .align  2
.LC32:
        .ascii  "0011110\000"
        .align  2
.LC33:
        .ascii  "101001\000"
        .align  2
.LC34:
        .ascii  "10101\000"
        .align  2
.LC35:
        .ascii  "010\000"
        .align  2
.LC36:
        .ascii  "000110\000"
        .align  2
.LC37:
        .ascii  "001101\000"
        .align  2
.LC38:
        .ascii  "1100\000"
        .align  2
.LC39:
        .ascii  "0111\000"
        .align  2
.LC40:
        .ascii  "00110010111\000"
        .align  2
.LC41:
        .ascii  "00111110\000"
        .align  2
.LC42:
        .ascii  "00010\000"
        .align  2
.LC43:
        .ascii  "000111\000"
        .align  2
.LC44:
        .ascii  "1111\000"
        .align  2
.LC45:
        .ascii  "0110\000"
        .align  2
.LC46:
        .ascii  "1101110\000"
        .align  2
.LC47:
        .ascii  "00110000001\000"
        .align  2
.LC48:
        .ascii  "0010\000"
        .align  2
.LC49:
        .ascii  "0000\000"
        .align  2
.LC50:
        .ascii  "1110\000"
        .align  2
.LC51:
        .ascii  "110101\000"
        .align  2
.LC52:
        .ascii  "11011111\000"
        .align  2
.LC53:
        .ascii  "1101000\000"
        .align  2
.LC54:
        .ascii  "1101001011\000"
        .align  2
.LC55:
        .ascii  "1101101\000"
        .align  2
.LC56:
        .ascii  "11011000101\000"
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
        .space  20
        .text
        .align  2
        .type   createNode, %function
createNode:
        @ Function supports interworking.
        @ args = 0, pretend = 0, frame = 16
        @ frame_needed = 1, uses_anonymous_args = 0
        stmfd   sp!, {fp, lr}
        add     fp, sp, #4
        sub     sp, sp, #16
        mov     r3, r0
        strb    r3, [fp, #-13]
        mov     r0, #12
        bl      malloc
        mov     r3, r0
        str     r3, [fp, #-8]
        ldr     r2, [fp, #-8]
        ldrb    r3, [fp, #-13]
        strb    r3, [r2, #0]
        ldr     r2, [fp, #-8]
        mov     r3, #0
        str     r3, [r2, #4]
        ldr     r2, [fp, #-8]
        mov     r3, #0
        str     r3, [r2, #8]
        ldr     r3, [fp, #-8]
        mov     r0, r3
        sub     sp, fp, #4
        ldmfd   sp!, {fp, lr}
        bx      lr
        .size   createNode, .-createNode
        .section        .rodata
        .align  2
.LC57:
        .ascii  "Error: Invalid Character in Encoded File (not 0 or "
        .ascii  "1)\000"
        .text
        .align  2
        .type   buildPath, %function
buildPath:
        @ Function supports interworking.
        @ args = 0, pretend = 0, frame = 24
        @ frame_needed = 1, uses_anonymous_args = 0
        stmfd   sp!, {fp, lr}
        add     fp, sp, #4
        sub     sp, sp, #24
        str     r0, [fp, #-16]
        str     r1, [fp, #-20]
        str     r2, [fp, #-24]
        ldr     r2, [fp, #-20]
        ldr     r3, .L13
        ldr     r2, [r3, r2, asl #2]
        ldr     r3, [fp, #-24]
        add     r3, r2, r3
        ldrb    r3, [r3, #0]
        strb    r3, [fp, #-5]
        ldrb    r3, [fp, #-5]   @ zero_extendqisi2
        cmp     r3, #0
        bne     .L4
        ldr     r3, [fp, #-20]
        and     r3, r3, #255
        ldr     r2, [fp, #-16]
        strb    r3, [r2, #0]
        b       .L12
.L4:
        ldrb    r3, [fp, #-5]   @ zero_extendqisi2
        cmp     r3, #48
        bne     .L6
        ldr     r3, [fp, #-16]
        ldr     r3, [r3, #4]
        cmp     r3, #0
        beq     .L7
        ldr     r3, [fp, #-16]
        ldr     r2, [r3, #4]
        ldr     r3, [fp, #-24]
        add     r3, r3, #1
        mov     r0, r2
        ldr     r1, [fp, #-20]
        mov     r2, r3
        bl      buildPath
        b       .L12
.L7:
        mov     r0, #42
        bl      createNode
        mov     r2, r0
        ldr     r3, [fp, #-16]
        str     r2, [r3, #4]
        ldr     r3, [fp, #-16]
        ldr     r2, [r3, #4]
        ldr     r3, [fp, #-24]
        add     r3, r3, #1
        mov     r0, r2
        ldr     r1, [fp, #-20]
        mov     r2, r3
        bl      buildPath
        b       .L12
.L6:
        ldrb    r3, [fp, #-5]   @ zero_extendqisi2
        cmp     r3, #49
        bne     .L9
        ldr     r3, [fp, #-16]
        ldr     r3, [r3, #8]
        cmp     r3, #0
        beq     .L10
        ldr     r3, [fp, #-16]
        ldr     r2, [r3, #8]
        ldr     r3, [fp, #-24]
        add     r3, r3, #1
        mov     r0, r2
        ldr     r1, [fp, #-20]
        mov     r2, r3
        bl      buildPath
        b       .L12
.L10:
        mov     r0, #42
        bl      createNode
        mov     r2, r0
        ldr     r3, [fp, #-16]
        str     r2, [r3, #8]
        ldr     r3, [fp, #-16]
        ldr     r2, [r3, #8]
        ldr     r3, [fp, #-24]
        add     r3, r3, #1
        mov     r0, r2
        ldr     r1, [fp, #-20]
        mov     r2, r3
        bl      buildPath
        b       .L12
.L9:
        ldr     r0, .L13+4
        bl      puts
.L12:
        sub     sp, fp, #4
        ldmfd   sp!, {fp, lr}
        bx      lr
.L14:
        .align  2
.L13:
        .word   lookup
        .word   .LC57
        .size   buildPath, .-buildPath
        .align  2
        .type   buildHuffmanTree, %function
buildHuffmanTree:
        @ Function supports interworking.
        @ args = 0, pretend = 0, frame = 8
        @ frame_needed = 1, uses_anonymous_args = 0
        stmfd   sp!, {fp, lr}
        add     fp, sp, #4
        sub     sp, sp, #8
        mov     r0, #42
        bl      createNode
        mov     r3, r0
        str     r3, [fp, #-12]
        mov     r3, #0
        str     r3, [fp, #-8]
        b       .L16
.L17:
        ldr     r0, [fp, #-12]
        ldr     r1, [fp, #-8]
        mov     r2, #0
        bl      buildPath
        ldr     r3, [fp, #-8]
        add     r3, r3, #1
        str     r3, [fp, #-8]
.L16:
        ldr     r3, [fp, #-8]
        cmp     r3, #127
        ble     .L17
        ldr     r3, [fp, #-12]
        mov     r0, r3
        sub     sp, fp, #4
        ldmfd   sp!, {fp, lr}
        bx      lr
        .size   buildHuffmanTree, .-buildHuffmanTree
        .align  2
        .type   decode, %function
decode:
        @ Function supports interworking.
        @ args = 0, pretend = 0, frame = 24
        @ frame_needed = 1, uses_anonymous_args = 0
        stmfd   sp!, {fp, lr}
        add     fp, sp, #4
        sub     sp, sp, #24
        str     r0, [fp, #-16]
        str     r1, [fp, #-20]
        str     r2, [fp, #-24]
        ldr     r3, [fp, #-24]
        str     r3, [fp, #-12]
        b       .L20
.L23:
        ldr     r3, [fp, #-12]
        ldr     r3, [r3, #4]
        str     r3, [fp, #-12]
        b       .L21
.L26:
        ldrb    r3, [fp, #-5]   @ zero_extendqisi2
        cmp     r3, #49
        bne     .L22
        ldr     r3, [fp, #-12]
        ldr     r3, [r3, #8]
        str     r3, [fp, #-12]
        b       .L21
.L22:
        ldr     r0, .L27
        bl      puts
        sub     sp, fp, #4
        ldmfd   sp!, {fp, lr}
        bx      lr
.L21:
        ldr     r3, [fp, #-12]
        ldr     r3, [r3, #4]
        cmp     r3, #0
        bne     .L20
        ldr     r3, [fp, #-12]
        ldr     r3, [r3, #8]
        cmp     r3, #0
        bne     .L20
        ldr     r3, [fp, #-12]
        ldrb    r3, [r3, #0]    @ zero_extendqisi2
        mov     r0, r3
        ldr     r1, [fp, #-20]
        bl      fputc
        ldr     r3, [fp, #-24]
        str     r3, [fp, #-12]
.L20:
        ldr     r0, [fp, #-16]
        bl      fgetc
        mov     r3, r0
        strb    r3, [fp, #-5]
        ldrb    r3, [fp, #-5]   @ zero_extendqisi2
        cmp     r3, #48
        beq     .L23
        b       .L26
.L28:
        .align  2
.L27:
        .word   .LC57
        .size   decode, .-decode
        .section        .rodata
        .align  2
.LC58:
        .ascii  "Usage: %s <file>\012\000"
        .align  2
.LC59:
        .ascii  "r\000"
        .align  2
.LC60:
        .ascii  "Error opening file\000"
        .align  2
.LC61:
        .ascii  "decoded.txt\000"
        .align  2
.LC62:
        .ascii  "w\000"
        .align  2
.LC63:
        .ascii  "Decoding completed. Check 'decoded.txt'.\000"
        .text
        .align  2
        .global main
        .type   main, %function
main:
        @ Function supports interworking.
        @ args = 0, pretend = 0, frame = 32
        @ frame_needed = 1, uses_anonymous_args = 0
        stmfd   sp!, {fp, lr}
        add     fp, sp, #4
        sub     sp, sp, #32
        str     r0, [fp, #-24]
        str     r1, [fp, #-28]
        ldr     r3, [fp, #-24]
        cmp     r3, #2
        beq     .L30
        ldr     r3, [fp, #-28]
        ldr     r3, [r3, #0]
        ldr     r0, .L34
        mov     r1, r3
        bl      printf
        mov     r3, #1
        str     r3, [fp, #-32]
        b       .L31
.L30:
        ldr     r3, [fp, #-28]
        add     r3, r3, #4
        ldr     r3, [r3, #0]
        mov     r0, r3
        ldr     r1, .L34+4
        bl      fopen
        mov     r3, r0
        str     r3, [fp, #-16]
        ldr     r3, [fp, #-16]
        cmp     r3, #0
        bne     .L32
        ldr     r0, .L34+8
        bl      perror
        mov     r3, #1
        str     r3, [fp, #-32]
        b       .L31
.L32:
        bl      buildHuffmanTree
        mov     r3, r0
        str     r3, [fp, #-12]
        ldr     r0, .L34+12
        ldr     r1, .L34+16
        bl      fopen
        mov     r3, r0
        str     r3, [fp, #-8]
        ldr     r0, [fp, #-16]
        ldr     r1, [fp, #-8]
        ldr     r2, [fp, #-12]
        bl      decode
        ldr     r0, [fp, #-16]
        bl      fclose
        ldr     r0, [fp, #-8]
        bl      fclose
        ldr     r0, .L34+20
        bl      puts
        mov     r3, #0
        str     r3, [fp, #-32]
.L31:
        ldr     r3, [fp, #-32]
        mov     r0, r3
        sub     sp, fp, #4
        ldmfd   sp!, {fp, lr}
        bx      lr
.L35:
        .align  2
.L34:
        .word   .LC58
        .word   .LC59
        .word   .LC60
        .word   .LC61
        .word   .LC62
        .word   .LC63
        .size   main, .-main
        .ident  "GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
        .section        .note.GNU-stack,"",%progbits