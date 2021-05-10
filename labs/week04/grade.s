main:
    la $a0, string0     # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", x);
    syscall

    addi $t0, $zero, 50
    addi $t1, $zero, 65
    addi $t2, $zero, 75
    addi $t3, $zero, 85
    addi $t4, $zero, 100

    blt $v0, $t0, fail
    blt $v0, $t1, pass
    blt $v0, $t2, credit
    blt $v0, $t3, distinction
    blt $v0, $t4, hd
    beq $v0, $t4, hd

fail:
    la $a0, string1     # printf("FL\n");
    li $v0, 4
    syscall
    b end

pass:
    la $a0, string2     # printf("PS\n");
    li $v0, 4
    syscall
    b end

credit:
    la $a0, string3     # printf("CR\n");
    li $v0, 4
    syscall
    b end

distinction:
    la $a0, string4     # printf("DN\n");
    li $v0, 4
    syscall
    b end

hd:
    la $a0, string5     # printf("HD\n");
    li $v0, 4
    syscall
    b end

end:

    jr $ra              # return


    .data   
string0:
    .asciiz "Enter a mark: "
string1:
    .asciiz "FL\n"
string2:
    .asciiz "PS\n"
string3:
    .asciiz "CR\n"
string4:
    .asciiz "DN\n"
string5:
    .asciiz "HD\n"