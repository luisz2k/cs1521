# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0
# $t4 = numbers[i]
# $t? = swapped

main:

    li $t0, 0           # i = 0

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    move $t4, $v0       # own line (store current value of array in $t4)

    add $t0, $t0, 1     #   i++;

loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    blt $v0, $t4, end1  # if (numbers[i] >= numbers[i-1] goto end1   
    move $t4, $v0       # own line (store current value of array in $t4)                 

    add $t0, $t0, 1     #   i++;
    b loop0             # }

end0:   # not ascending order

    li $a0, 0         # printf("%d", 1)
    li $v0, 1           #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr $31

end1:   # in ascending order

    li $a0, 1         # printf("%d", 0)
    li $v0, 1           #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr $31

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

