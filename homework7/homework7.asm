.data

xs: .word 3, 4, 7, 10, 12
ys: .word 1, 2, 4, 5, 3
test1: .word 4
test2: .word 5

.globl main
.text

minimum:
    lw $t0, 0($a0)
    lw $t1 0($a1)
    sub $t2, $t1, $t0
    bltz $t2, T0
    addi $a2, $t0, 0
    j minimum_end
T0: 
    addi $a2, $t1, 0
minimum_end:
    j $ra

parity:
    #This will be compared against with AND later
    addi $t0, $zero, 1
    addi $t3, $zero, 0

    #This is the counter that will hold the length
    addi $t1, $zero, 32
parity_loop:
    #branch if we've reached every bit
    blez $t1, parity_loop_end

    #Checks the least significant bit
    and $t2, $a0, $t0

    #Adds the result to the return value
    add $t3, $t3, $t2

    #Shifts a0 right by 1
    srl $a0, $a0, 1
    addi $t1, $t1, -1
    j parity_loop
parity_loop_end:
    addi $t4, $zero, 2
    div $t3, $t4
    mfhi $v0
    j $ra

array_maximum:
    addi $v0, $zero, 0
    addi $t2, $a1, 0
array_loop:
    blez $t2, array_end
    lw $t0, 0($a0)
    sub $t1, $t0, $v0
    bgtz $t1, update
    addi $a0, $a0, 4
    addi $t2, $t2, -1
    j array_loop
update:
    addi $v0, $t0, 0
    addi $a0, $a0, 4
    addi $t2, $t2, -1
    j array_loop
array_end:
    j $ra

permutation:

    #t0 is basically the i in array[i]
    #t1 is the i in permutation[i]
    #t2 is a counter
    addi $t2, $zero, 0
    addi $t0, $a0, 0
    addi $t1, $a1, 0
permutation_loop:
    bge $t2, $a2, permutation_end

    #Temp = Array[i]
    lw $t3, 0($t0)

    #Permutation[i]
    lw $t4, 0($t1)

    #Turning permutation[i] into a memory address
    mul $t4, $t4, 4
    add $t4, $t4, $t0

    #Array[permutation[i]]
    lw $t5, 0($t4)

    #Array[i] = Array[Permutation[i]]
    sw $t5, 0($t0)

    #Array[Permutation[i]] = temp
    sw $t3, 0($t4)

    #Incrementing everything
    addi $t0, $t0, 4
    addi $t1, $t1, 4
    addi $t2, $t2, 1
permutation_end:
    j $ra

main:
    # la $a0, xs
    # la $a1, ys
    # addi $a2, $zero, 5
    # jal permutation
    la $a0, test1
    la $a1, test2
    jal minimum
    li $v0, 10
    syscall
    .end main