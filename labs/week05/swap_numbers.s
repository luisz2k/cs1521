# read 10 numbers into an array
# swap any pairs of of number which are out of order
# then print the 10 numbers

# i in register $t0,
# registers $t1 - $t3 used to hold temporary results
#
# $t4 = y = numbers[i-1]
# $t5 = x = numbers[i]

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:
    
    li $t0, 1           # i = 1
    
while1: # swapping numbers in the array if needed
    bge $t0, 10, while1_end   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #

    lw $t5, ($t3)       # x = numbers[i]

    addi $t6, $t3, -4   # y = numbers[i-1]
    lw $t4, ($t6)

    blt $t5, $t4, swap  # if (x < y) goto swap

    add $t0, $t0, 1     #   i++
    b while1             # }    

while1_end:
    li $t0, 0           # i = 0

loop1:
    bge $t0, 10, end1   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    lw $a0, ($t3)       #   load numbers[i] into $a0
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1     #   i++
    b loop1             # }
end1:

    jr $31              # return

swap:
    sw $t4, ($t3)       # numbers[i] = y
    addi $t6, $t3, -4
    sw $t5, ($t6)       # numbers[i-1] = x

    add $t0, $t0, 1     #   i++
    b while1             # }

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

