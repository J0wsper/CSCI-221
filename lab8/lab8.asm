.data

xs: .word 1, 2, 3, 4, 5
ys: .word 5, 3, 2, 1, 4

.globl main
.text

#Here, I am letting $a0 be the pointer to the start of the struct and $a1 be length
main:
    #int32_t max_squared_distance = 0
    addi $t0, $zero, 0

    #uint8_t max_distance_color = 0
    addi $t1, $zero, 0

    #Initializing another temporary variable that will be our counter.
    addi $t2, $zero, 0

    #Finally, getting another variable that will point to the memory address we're looking for
    addi $t3, $zero, 0
brightness_loop:
    #while i < len
    beq $t2, $a1, brightness_func_end

    #storing x
    lw $t4, 4($t3)

    #storing y
    lw $t5, 8($t3)

    #x*x, y*y
    mul $t4, $t4, $t4
    mul $t5, $t5, $t5

    #squared_distance = x*x + y*y
    add $t6, $t4, $t5

    slti $t7, $t0, $t6
    bne $t7, set_new_color
    j brightness_loop_end
set_new_color:

    #max_squared_distance = squared_distance
    addi $t0, $t6, 0

    #loading r, g and b. Overwriting old registers.
    lb $t4, 0($t3)
    lb $t5, 1($t3)
    lb $t6 2($t3)

    #$t1 = r+g+b
    add $t1, $t4, $t5
    add $t1, $t7, $t6

    #take the average
    addi $t8, $zero, 3
    div $t1, $t8
    mfhi $t1

brightness_loop_end:
    #i++
    addi $t2, $t2, 1

    #incrementing our pointer
    addi $t3, $t3, 12
    j brightness_loop

brightness_func_end:
    addi $v0, $t1, 0
    jr $ra

stack:
    addi $sp, $sp, -24
    sw $ra, 0($sp)
    sw $t0, 4($sp)
    sw $t1, 8($sp)
    sw $t2, 12($sp)
    sw $s0, 16($sp)
    sw $s1, 20($sp)
    jal foo
    lw $ra, 0($sp)
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    lw $t2, 12($sp)
    lw $s0, 16($sp)
    lw $s1, 20($sp)
    addi $sp, $sp, 24
foo:
    nop
    jr $ra

#assuming that $a0 stores n and $a1 stores k
binomial:
    #if k == 0 || k == n
    beq $a1, $zero, case1
    beq $a1, $a0, case1
    j recurse
case1:
    #effectively returning 1
    addi $v0, $v0, 1
    jr $ra
recurse:
    #messing with the stack
    addi $sp, $sp, -12
    sw $ra, 0($sp)
    sw $a0, 4($sp)
    sw $a1, 8($sp)

    #binomial(n-1, k)
    addi $a0, $a0, -1
    jal binomial

    #binomial(n-1, k-1)
    lw $a0, 4($sp)
    lw $a1, 8($sp)
    addi $a0, $a0, -1
    addi $a1, $a1, -1
    jal binomial
    lw $ra, 0($sp)
    addi $sp, $sp, 8
    jr $ra

floats:

    #f0 = 10
    addi $t0, $zero, 10
    mtc1 $t0, $f0

    #f0 = 10.0
    cvt.s.w $f0, $f0
    addi $t1, $zero, 1
    addi $t2, $zero, 2
    mtc1 $t1, $f1
    mtc1 $t2, $f2

    #f1 = 1.0
    #f2 = 2.0
    cvt.s.w $f1, $f1
    cvt.s.w $f2, $f2

    #f1 = f1/f2 = 0.5
    div.s $f1, $f1, $f2

    #f0 = f0 + f1 = 10.0 + 0.5 = 10.5
    add.s $f0, $f0, $f1

    #second part of the floats below
    #x^2
    mul.s $f4, $f3, $f3

    #a*x^2
    mul.s $f5, $f0, $f4

    #b*x
    mul.s $f6, $f1, $f3

    #a*x^2+b*x
    add.s $f5, $f5, $f6

    #a*x^2+b*x+c
    add.s $f5, $f5, $f2

    li $v0, 10
    syscall
    .end main