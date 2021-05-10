# COMP1521 18s1 Exam Q1
# int isIdent(int matrix[N][N], int N)

   .text
   .globl isIdent

# params: matrix=$a0, N=$a1
isIdent:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   addi $sp, $sp, -4
   sw   $s3, ($sp)
   # if you need to save more than four $s? registers
   # add extra code here to save them on the stack

# ... your code for the body of isIdent(m,N) goes here ...
# $s0 = matrix, $s1 = N, $t0 = i, $t1 = j, $t2, $t3 is temp, $t4 = matrix[i][j], $t8 = 4

   #move $s0, $a0
   #move $s1, $a1
   li $t0, 0
while1:
   bge $t0, $a1, while1_end
   li $t1, 0

while2:
   bge $t0, $a1, while2_end   
   # addr = baseAddr + (rowIndex * colSize + colIndex) * dataSize
   # addr = baseAddr + ($t0 * $a1 + $t1) * 4
   mul $t2, $t0, $a1
   add $t2, $t2, $t1
   mul $t2, $t2, $t8

   la $t3, $a0          # get &matrix[i][j]
   add $t3, $t3, $t2    
   lw $t4, ($t3)        # $t4 = matrix[i][j]

   bne $t0, $t1, cond2     # if i != j, goto cond2

   # i == j  ==>  matrix[i][j] == 1
   li $t5, 1   
   beq $t4, $t5, cond2     # if matrix[i][j] = 1, goto cond2
   li $v0, 0
   j return

cond2:
   beq $t4, $t5, skip      # m[i][j] != 1, goto skip
   beq $t4, skip           # m[i][j] != 0, goto skip
   li $v0, 0
   j return

skip:
   addi $t0, $t0, 1
   j while2
while2_end:
   addi $t0, $t0, 1
   j while1
while1_end:
   li $v0, 1

return:
# epilogue
   # if you saved more than six $s? registers
   # add extra code here to restore them
   lw   $s3, ($sp)
   addi $sp, $sp, 4
   lw   $s2, ($sp)
   addi $sp, $sp, 4
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

