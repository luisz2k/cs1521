# print the integers between x and y except 13
#
# $t0 = x
# $t1 = y
# $t2 = i

main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    addi $t2, $t0, 1    # int i = x + 1;

while:
    bge $t2, $t1, end     # while (i < y) {
    bne $t2, 13, print          #     if (i != 13) goto print
    addi $t2, $t2, 1            #     i = i + 1;
    b while  

end:

    li $v0, 0           # return 0
    jr $31

print: 

    move $a0, $t2          #   printf("%d\n", i);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t2, $t2, 1            #     i = i + 1;
    b while