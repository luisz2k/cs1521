#  read numbers until a non-negative number entered
# x in $t0
main:

while1:
    la $a0, str0         # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5            # scanf("%d", &x);
    syscall              #
    move $t0, $v0

    bgez $t0, stop         # if (x >= 0) goto break

    # if (x < 0) 
    la $a0, str2         # printf("Enter a positive number");
    li $v0, 4
    syscall
    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    b while1

while1_end:

    li $v0, 0            # return 0
    jr $31

stop:

    la $a0, str1         # printf("You entered: ");
    li $v0, 4
    syscall
    move $a0, $t0        # printf("%d", x);
    li $v0, 1
    syscall
    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    b while1_end

.data
str0:
    .asciiz "Enter a number: "
str1:
    .asciiz "You entered: "
str2:
    .asciiz "Enter a positive number"