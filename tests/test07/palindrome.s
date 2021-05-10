# read a line and print whether it is a palindrom

# $t0 = i
# $t2, $t3, $t4 for temporary results
# $t1 = j
# $t5 = k

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    li $t0, 0           # int i = 0;
    li $t7, 1
while:
    #mul $t1, $t0, 4     # calculate &line[i]
    la $t2, line         
    add $t3, $t0, $t2
    lb $t4, ($t3)       # $t4 = line[i]

    beq $t4, $0, while_end  # while (line[i] != 0)
    addi $t0, $t0, 1        # i++;
    b while

while_end:
    li $t1, 0               # int j = 0;
    addi $t5, $t0, -2        # int k = i - 2;

while2:
    bge $t1, $t5, while2_end    # while (j < k) {

    la $t2, line         # calculate &line[j]
    add $t3, $t1, $t2
    lb $t4, ($t3)       # $t4 = line[j]

    la $t2, line         # calculate &line[k]
    add $t3, $t5, $t2
    lb $t6, ($t3)       # $t6 = line[k]

    bne $t4, $t6, if_statement  # if (line[j] != line[k])
    addi $t1, $t1, 1    # j++;
    addi $t5, $t5, -1    # k--;
    b while2

while2_end:
    
    la   $a0, palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $31

if_statement:
    la   $a0, not_palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

