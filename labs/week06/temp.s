# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
#
# $t0 = i
# registers $t1, $t2 & $t3 used to hold temporary results
# $t4 also temp
# $t5 = j
# $t6 = 1
# $t7 = 2

main:

    li $t0, 0           # int i = 0;
    li $t6, 1
    li $t7, 2

while1:

    bge $t0, 1000, while1_end       # while (i < 1000) 


   # mul $t1, $t0, 4     #   calculate &prime[i]
    la $t2, prime       #
    add $t3, $t0, $t2   #
    sb $t6, ($t3)         #   prime[i] = 1;

    add $t0, $t0, 1     #   i++;
    b while1            # }

while1_end:

    li $t0, 2           # i = 2

while2: 

    bge $t0, 1000, while2_end       # while (i < 1000)

    #mul $t1, $t0, 4     #   calculate &prime[i]
    la $t2, prime       #
    add $t3, $t0, $t2   #
    lb $t4, ($t3)     # store prime[i] in $t4
    
    beq $t4, $t6, if     # if prime[i] = 1 goto print
    add $t0, $t0, 1     #   i++;
    b while2

while2_end:

    li $v0, 0           # return 0
    jr $31

if:

    move   $a0, $t0      # printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    mul $t5, $t7, $t0     # j = 2 * i;

while3:
    bge $t5, 1000, while3_end       # while (j < 1000)

    #mul $t1, $t5, 4     #   calculate &prime[j]
    la $t2, prime       #
    add $t3, $t5, $t2   #
    sb $0, ($t3)         #   prime[j] = 0;

    add $t5, $t5, $t0     #   j++;

    b while3

while3_end:

    add $t0, $t0, 1     #   i++;
    b while2

.data
prime:
    .space 1000