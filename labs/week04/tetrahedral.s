# $t0 = i
# $t1 = j
# $t2 = n
# $t3 = total
# $t4 = how_many

main:

    la $a0, string         # printf("Enter how many: ");
    li $v0, 4
    syscall

    li $v0, 5               # scanf("%d", &how_many);
    syscall

    move $t4, $v0           
    li $t2, 1               # n = 1;

loop1:
    bgt $t2, $t4, end       # if n > how_many, goto end 

    li $t3, 0               # total = 0;
    li $t1, 1               # j = 1;

loop2:
    bgt $t1, $t2, loop1end     # if j > n, goto loop
    li $t0, 1               # i = 1;

loop3:
    bgt $t0, $t1, loop2end     # if i > j, goto ?

    add $t3, $t3, $t0         # total++;
    add $t0, $t0, 1         # i++;

    b loop3

loop2end:

    add $t1, $t1, 1         # j++;
    b loop2

loop1end:

    move $a0, $t3           # printf("%d", total);
    li $v0, 1
    syscall
    li   $a0, '\n'          # printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t2, $t2, 1         # n++;
    b loop1

end:
    jr		$ra			    # return

.data

string: .asciiz "Enter how many: "