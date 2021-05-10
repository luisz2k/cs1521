# $t0 = i
# $t1 = number
# $t2 = 7
# $t3 = 11

main:

    la $a0, string         # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5               # scanf("%d", number);
    syscall

    li    $t0, 1            # i = 1;
    move  $t1, $v0          
    li    $t2, 7
    li    $t3, 11

loop:    

    bge $t0, $t1, end       # while (i < number) {

    rem $t4, $t0, $t2        # if (i % 7 == 0 || i % 11 == 0) {
    beq $t4, $zero, print

    rem $t4, $t0, $t3
    beq $t4, $zero, print

    add $t0, $t0, 1         # i++;

    b   loop                # goto loop

print:
    move $a0, $t0           # printf("%d", i);
    li $v0, 1
    syscall

    li   $a0, '\n'          # printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1         # i++;

    b loop

end:
    jr		$ra			    # return
      
.data   
    string:
    .asciiz "Enter a number: "

