// If you use C library functions add includes here.

#include "emu.h"
#include "ram.h"
#include "registers.h"

/**
 * execute a MIPS instruction
 *
 * This function should:
 *
 * get register values by calling `get_register(register_type register_number)`
 * change registers by calling `set_register(register_type register_number, uint32_t value)`
 *
 * get memory values by `calling get_byte(uint32_t address)`
 * changes memory by `set_byte(uint32_t address, uint8_t value)`
 *
 * updates program_counter to address of next instruction
 *
 * returns 1 if an exit syscall is executed, 0 otherwise
 */
int execute_instruction(uint32_t instruction, uint32_t *program_counter) {

    uint32_t result = 0;

    uint32_t mask = 0x3F;     // mask 6 bits
    uint32_t mask2 = 0x1F;    // mask 5 bits
    uint32_t mask3 = 0xFFFF;    // mask 16 bits

    uint32_t src = (instruction >> 21) & mask2;
    uint32_t t = (instruction >> 16) & mask2;
    uint32_t dest = (instruction >> 11) & mask2;

    int16_t imm = 0;
    uint32_t b = 0;
    uint32_t o = 0;
    uint32_t x = 0;

    if (((instruction >> 26) & mask) == 0) {                    // instructions starting with 000000
        if ((instruction & mask) == 0x20) {                 // add
            result = get_register(src) + get_register(t);
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0x22) {            // sub
            result = get_register(src) - get_register(t);
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0x24) {            // and
            result = get_register(src) & get_register(t);
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0x25) {            // or
            result = get_register(src) | get_register(t);
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0x26) {            // xor
            result = get_register(src) ^ get_register(t);
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0x4) {            // sllv
            result = get_register(t) << get_register(src);
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0x6) {            // srlv
            result = get_register(t) >> get_register(src);
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0x2A) {            // slt
            result = get_register(src) < get_register(t);
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0) {                   // sll
            imm = (instruction >> 6) & mask2;
            result = get_register(t) << imm;
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0x2) {            // srl
            imm = (instruction >> 6) & mask2;
            result = get_register(t) >> imm;
            set_register(dest, result);
        }
        else if ((instruction & mask) == 0x8) {            // jr
            (*program_counter) = src;
        }
        else if ((instruction & mask) == 0xC) {    // SYSCALL
            if (get_register(2) == 1) {                 // print integer
                printf("%d", get_register(4));
            } 
            else if (get_register(2) == 4) {            // print string
                printf("%s", get_register(4));
            }
            else if (get_register(2) == 5) {            // read integer
                scanf("%d", &result);
                set_register(2, result);
            }
            else if (get_register(2) == 8) {            // read string
                int count = 0;
                while (count < get_register(5)) {
                    scanf("%s", &result);
                    set_register(2, result);
                    count++;
                }
            }
            else if (get_register(2) == 11) {            // print character
                printf("%c", get_register(4));
            }
        }
    }
    
    else if (((instruction >> 26) & mask) == 0x1C) {    // mul
        result = get_register(src) * get_register(t);
        set_register(dest, result);
    }
    else if (((instruction >> 26) & mask) == 0x8) {    // addi    
        imm = instruction & mask3;
        result = get_register(src) + imm;
        set_register(t, result);
    }
    else if (((instruction >> 26) & mask) == 0xC) {    // andi
        imm = instruction & mask3;
        result = get_register(src) & imm;
        set_register(t, result);
    }
    else if (((instruction >> 26) & mask) == 0xD) {    // ori
        imm = instruction & mask3;
        result = get_register(src) | imm;
        set_register(t, result);
    }
    else if (((instruction >> 26) & mask) == 0xE) {    // xori
        imm = instruction & mask3;
        result = get_register(src) ^ imm;
        set_register(t, result);
    }
    else if (((instruction >> 26) & mask) == 0xA) {    // slti
        imm = instruction & mask3;
        result = get_register(src) < imm;
        set_register(t, result);
    }
    else if (((instruction >> 26) & mask) == 0xF) {    // lui
        imm = instruction & mask3;
        result = imm << 16;
        set_register(t, result);
    }
    else if (((instruction >> 26) & mask) == 0x20) {    // lb
        imm = instruction & mask3;
        o = imm;
        b = src;
        result = *(int8_t*)(b + o);
        set_register(t, result);
    }
    else if (((instruction >> 26) & mask) == 0x21) {    // lh
        imm = instruction & mask3;
        o = imm;
        b = src;
        result = *(int16_t*)(b + o);
        set_register(t, result);
    }
    else if (((instruction >> 26) & mask) == 0x23) {    // lw
        imm = instruction & mask3;
        o = imm;
        b = src;
        result = *(int32_t*)(b + o);
        set_register(t, result);
    }
    
    /* 
    sb, sh, sw
    */

    else if (((instruction >> 26) & mask) == 0x4) {    // beq
        imm = instruction & mask3;
        if (src == t) {
            (*program_counter) += (imm << 2);
        } else {
            (*program_counter) += 4;
        }
    }
    else if (((instruction >> 26) & mask) == 0x5) {    // bne
        imm = instruction & mask3;
        if (src != t) {
            (*program_counter) += (imm << 2);
        } else {
            (*program_counter) += 4;
        }
    }
    else if (((instruction >> 26) & mask) == 0x6) {    // blez
        imm = instruction & mask3;
        if (src <= 0) {
            (*program_counter) += (imm << 2);
        } else {
            (*program_counter) += 4;
        }
    }
    else if (((instruction >> 26) & mask) == 0x7) {    // bgtz
        imm = instruction & mask3;
        if (src > 0) {
           (*program_counter) += (imm << 2);
        } 
        else {
           (*program_counter) += 4;
        }
    }
    else if (((instruction >> 26) & mask) == 0x1) {    
        imm = instruction & mask3;
        if (t == 0) {                                       // bltz
            if (src < 0) {
                (*program_counter) += (imm << 2);
            } else {                                        
                (*program_counter) += 4;
            }
        }
        else if (t == 1) {                                  // bgez
            if (src >= 0) {                                 
                (*program_counter) += ((int16_t)imm << 2);
            } else {
                (*program_counter) += 4;
            }
        }
    }
    else if (((instruction >> 26) & mask) == 0x2) {                        // j
        x = instruction & 0b0000011111111111111111111111111;
        (*program_counter) = ((*program_counter) & 0xF0000000) | (x << 2);
    }
    else if (((instruction >> 26) & mask) == 0x3) {                        // jal
        x = instruction & 0b0000011111111111111111111111111;
        set_register(31, (*program_counter) + 4);
        (*program_counter) = ((*program_counter) & 0xF0000000) | (x << 2);
    }

    // Update program_counter to address of next instructions
    // Most instructions will simply do the following:
    (*program_counter) += 4;
    // Jump & Branch instructions will do something different    

    // 0 should be returned, unless an exit syscall is executed
    return 0;
}