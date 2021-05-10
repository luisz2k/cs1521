# print a square of asterisks
#
# $t0 = x
# $t1 = i
# $t2 = j

main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $t1, 0           # int i = 0;

while1:
    bge $t1, $t0, end   # while (i < x) {

    li $t2, 0           # int j = 0;

while2:            
    bge $t2, $t0, while2_end    # while (j < x) {

    li $a0, '*'          #   printf("*");
    li $v0, 11
    syscall

    addi $t2, $t2, 1    # j = j + 1;

    b while2

while2_end:

    addi $t1, $t1, 1    # i = i + 1;
    li   $a0, '\n'      #   printf("\n");
    li   $v0, 11
    syscall

    b while1

end:

    li $v0, 0           # return 0
    jr $31
