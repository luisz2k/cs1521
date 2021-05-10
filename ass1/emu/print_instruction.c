// If you use C library functions add includes here.

#include "emu.h"
#include "ram.h"
#include "registers.h"

/*
 * print a MIPS instruction (no newline)
 * run reference implementation if unsure what to print
 */
void print_instruction(uint32_t instruction) {

    uint32_t mask = 0x3F;       // 6 bits
    uint32_t mask2 = 0x1F;      // 5 bits
    uint32_t mask3 = 0xFFFF;    // 16 bits

    uint32_t src = (instruction >> 21) & mask2;
    uint32_t t = (instruction >> 16) & mask2;
    uint32_t dest = (instruction >> 11) & mask2;

    int16_t imm = 0;
    uint32_t b = 0;
    uint32_t o = 0;
    uint32_t x = 0;

    if (((instruction >> 26) & mask) == 0) {     
        if ((instruction & mask) == 0x20) {     
            printf("add $%d, $%d, $%d", dest, src, t);
        }
        else if ((instruction & mask) == 0x22) {
            printf("sub $%d, $%d, $%d", dest, src, t);
        }
        else if ((instruction & mask) == 0x24) {
            printf("and $%d, $%d, $%d", dest, src, t);
        }
        else if ((instruction & mask) == 0x25) {
            printf("or $%d, $%d, $%d", dest, src, t);
        }
        else if ((instruction & mask) == 0x26) {
            printf("xor $%d, $%d, $%d", dest, src, t);
        }
        else if ((instruction & mask) == 0x4) {
            printf("sllv $%d, $%d, $%d", dest, t, src);
        }
        else if ((instruction & mask) == 0x6) {
            printf("srlv $%d, $%d, $%d", dest, t, src);
        }
        else if ((instruction & mask) == 0x2A) {
            printf("slt $%d, $%d, $%d", dest, src, t);
        }
        else if ((instruction & mask) == 0) {
            imm = (instruction >> 6) & mask2;
            printf("sll $%d, $%d, %d", dest, t, imm);
        }
        else if ((instruction & mask) == 0x2) {
            imm = (instruction >> 6) & mask2;
            printf("srl $%d, $%d, %d", dest, t, imm);
        }
        else if ((instruction & mask) == 0x8) {
            printf("jr $%d", src);
        }
        else if ((instruction & mask) == 0xC) {
            printf("syscall");
        }
    }

    else if (((instruction >> 26) & mask) == 0x1C) {    // if first bits are 011100
        printf("mul $%d, $%d, $%d", dest, src, t);
    }
    else if (((instruction >> 26) & mask) == 0x8) {    
        imm = instruction & mask3;
        printf("addi $%d, $%d, %d", t, src, imm);
    }
    else if (((instruction >> 26) & mask) == 0xC) {    
        imm = instruction & mask3;
        printf("andi $%d, $%d, %d", t, src, imm);
    }
    else if (((instruction >> 26) & mask) == 0xD) {    
        imm = instruction & mask3;
        printf("ori $%d, $%d, %d", t, src, imm);
    }
    else if (((instruction >> 26) & mask) == 0xE) {    
        imm = instruction & mask3;
        printf("xori $%d, $%d, %d", t, src, imm);
    }
    else if (((instruction >> 26) & mask) == 0xA) {    
        imm = instruction & mask3;
        printf("slti $%d, $%d, %d", t, src, imm);
    }
    else if (((instruction >> 26) & mask) == 0xF) {    
        imm = instruction & mask3;
        printf("lui $%d, %d", t, imm);
    }
    else if (((instruction >> 26) & mask) == 0x20) {    
        imm = instruction & mask3;
        o = imm;
        b = src;
        printf("lb $%d, %d($%d)", t, o, b);
    }
    else if (((instruction >> 26) & mask) == 0x21) {    
        imm = instruction & mask3;
        o = imm;
        b = src;
        printf("lh $%d, %d($%d)", t, o, b);
    }
    else if (((instruction >> 26) & mask) == 0x23) {    
        imm = instruction & mask3;
        o = imm;
        b = src;
        printf("lw $%d, %d($%d)", t, o, b);
    }
    else if (((instruction >> 26) & mask) == 0x28) {    
        imm = instruction & mask3;
        o = imm;
        b = src;
        printf("sb $%d, %d($%d)", t, o, b);
    }
    else if (((instruction >> 26) & mask) == 0x29) {    
        imm = instruction & mask3;
        o = imm;
        b = src;
        printf("sh $%d, %d($%d)", t, o, b);
    }
    else if (((instruction >> 26) & mask) == 0x2B) {    
        imm = instruction & mask3;
        o = imm;
        b = src;
        printf("sw $%d, %d($%d)", t, o, b);
    }
    else if (((instruction >> 26) & mask) == 0x4) {    
        imm = instruction & mask3;
        printf("beq $%d, $%d, %d", src, t, imm);
    }
    else if (((instruction >> 26) & mask) == 0x5) {    
        imm = instruction & mask3;
        printf("bne $%d, $%d, %d", src, t, imm);
    }
    else if (((instruction >> 26) & mask) == 0x6) {    
        imm = instruction & mask3;
        printf("blez $%d, %d", src, imm);
    }
    else if (((instruction >> 26) & mask) == 0x7) {    
        imm = instruction & mask3;
        printf("bgtz $%d, %d", src, imm);
    }
    else if (((instruction >> 26) & mask) == 0x1) {    
        imm = instruction & mask3;
        if (t == 0) {
            printf("bltz $%d, %d", src, imm);
        }
        else if (t == 1) {
            printf("bgez $%d, %d", src, (int16_t)imm);
        }
    }
    else if (((instruction >> 26) & mask) == 0x2) {    
        x = instruction & 0b0000011111111111111111111111111;
        printf("j 0x%x", x);
    }
    else if (((instruction >> 26) & mask) == 0x3) {    
        x = instruction & 0b0000011111111111111111111111111;
        printf("jal 0x%x", x);
    }

}