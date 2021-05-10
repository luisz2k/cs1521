# t0 = i
# t1 = number

main:
    la $a0, string0         # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5               # scanf("%d", number);
    syscall

    li    $t0, 1            # i = 1;
    move  $t1, $v0

loop:                       # loop
    bgt $t0, $t1, end       # if (i > number) goto end;

    move $a0, $t0           # printf("%d", i);
    li $v0, 1
    syscall

    li   $a0, '\n'          # printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1         # i++;

    b   loop                # goto loop

end:
    jr		$ra			    # return
    
    .data   

string0:
    .asciiz "Enter a number: "