# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# $t0 = i, $t1 = 1000, $t2, $t3, $t5 are temp, $t4 = 1, $t6 = j, $t7 = 2, $t8 = 0
main:

    li $t0, 0
    li $t1, 1000
    li $t4, 1
    li $t7, 2
    li $t8, 0

while1:
    bge $t0, $t1, while1_end

    la $t2, prime
    add $t3, $t2, $t0
    sb $t4, ($t3)

    addi $t0, $t0, 1
    b while1

while1_end:

    li $t0, 2

while2:
    bge $t0, $t1, while2_end

    la $t2, prime
    add $t3, $t2, $t0
    lb $t5, ($t3)

    beq $t5, $t4, if_statement
    addi $t0, $t0, 1
    b while2

while2_end:


    li $v0, 0           # return 0
    jr $31

if_statement:

    move $a0, $t0
    li $v0, 1
    syscall

    li $a0, '\n'
    li $v0, 11
    syscall

    mul $t6, $t7, $t0
while3:
    bge $t6, $t1, while3_end

    la $t2, prime
    add $t3, $t2, $t6
    sb $t8, ($t3)

    add $t6, $t6, $t0
    b while3
while3_end:
    addi $t0, $t0, 1
    b while2

.data
prime:
    .space 1000