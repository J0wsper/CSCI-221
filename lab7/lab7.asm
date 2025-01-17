.globl main
.text

main:
    addi $a0, $zero, 0
    addi $a1, $zero, 1
    addi $a2, $zero, 2
    addi $v0, $zero, 3
    addi $t1, $zero, 4

    #   COMPUTATION
    addi $t1, $t0, 128
    sub $v0, $s0, $t0
    addi $a2, $a2, 42
    add $a1, $a1, $a2
    sub $a0, $a0, $a1

    #   DATA MOVEMENT
    li $t0, 10
    lw $v0, 4($a0) #This causes an exception for some reason
    sw $t0, 8($a0)
    
    #   CONTROL
    j L1
    bltz $a0, L1
    sub $t2, $s0, $s1
    bgez $t2, L1
    bltz $v0, L2
    li $t0, 0
    li $t3, 221
loop:  
    slt $t1, $t0, $a1
    bne $t1, $zero, end_loop
    sll $t2, $t0, 2
    sw $t3, 0($t2)
    addi $t0, $t0, 1
end_loop:
    jr $ra

L2:
    li $v0, 0
    j loop