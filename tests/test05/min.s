#  print the minimum of two integers
#
# $t0 = x
# $t1 = y

main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    blt $t0, $t1, print_x   # if (x < y) goto print_x
    #bge $t0, $t1, print_y   # else goto print_y

    move $a0, $t1          #   printf("%d\n", y);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

end:

    li $v0, 0           # return 0
    jr $31

print_x:

    move $a0, $t0          #   printf("%d\n", x);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    b end