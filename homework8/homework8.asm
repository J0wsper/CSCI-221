.data

xs: .half 1, 2, 3, 4, 5
length: .word 5
decay_test: .word 2

.globl main
.text

zip_with:
    #suppose that $a0 points to the first entry of array1, $a1 points to the head of array2, $a2
    #stores the head of result_array and $a3 stores the length

    #incrementer variable for the array pointers
    addi $t0, $a0, 0
    addi $t1, $a1, 0
    addi $t2, $a2, 0

    #incrementer variable
    addi $t3, $a3, 0
zip_with_loop:
    beq $t0, $zero, zip_with_end

    #storing the temporary variables so they aren't shlorped by foo
    addi $sp, $sp, -28
    sw $t0, 0($sp)
    sw $t1, 4($sp)
    sw $a0, 8($sp)
    sw $a1, 12($sp)
    sw $a2, 16($sp)
    sw $a3, 20($sp)
    sw $ra 24($sp)

    #preparing variables that are passed to foo
    lw $a0, 0($t0)
    lw $a1, 0($t1)

    #assuming that $v0 stores the result of foo(array1[i], array2[i])
    jal foo
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    lw $a0, 8($sp)
    lw $a1, 12($sp)
    lw $a2, 16($sp)
    lw $a3, 20($sp)
    lw $ra, 24($sp)

    #result_array[i] = foo(array1[i], array2[i])
    sw $v0, 0($t1)

    #incrementing the pointers
    addi $t0, $t0, 4
    addi $t1, $t1, 4
    addi $t2, $t2, 4

    #incrementing the loop counter
    addi $t3, $t3, -1

    #fixing the stack
    addi $sp, $sp, 28
    j zip_with_loop
zip_with_end:
    jr $ra


# The requested C code is the below:

# uint32_t decaying_sum(uint16_t* values, uint16_t length, uint16_t decay) {
#     return decaying_sum_helper(values, length, decay, 0);
# }

# uint32_t decaying_sum_helper(uint16_t* values, uint16_t length, uint16_t decay, uint32_t acc) {
#     if (length <= 1) {
#         return values[0]+acc;
#     }
#     acc += values[length-1];
#     acc /= decay;
#     return decaying_sum_helper(values, length-1, decay, acc);
# }

#For this, I am assuming that $a0 stores the head of values, $a1 stores length and $a2 stores decay. $v0 will store the return.
decaying_sum:
    addi $a3, $zero, 0
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal decaying_sum_helper
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra
decaying_sum_helper:

    #Storing the arguments in temporary variables.
    addi $t0, $a0, 0
    addi $t1, $a1, 0
    addi $t2, $a2, 0
    addi $t3, $a3, 0
    addi $v0, $zero, 0

    addi $t4, $zero, 1
    beq $t1, $t4, non_recurse
    j recurse
non_recurse:

    #Non-recursive case: $t5 = values[0], $v0 = values[0]+acc
    lh $t5, 0($t0)
    add $v0, $t5, $a3
    jr $ra

recurse:

    #getting length-1, storing it in $t7
    addi $t5, $zero, 2

    #multiplying length by 2 because the values are each 2 bytes
    mul $t6, $t1, $t5

    #subtracting -2 from length so you don't try to get values outside of range
    addi $t6, $t6, -2

    #adding the length to the pointer of the head of the array
    add $t7, $t0, $t6

    #acc += values[length-1]
    lh $t8, 0($t7)
    add $t3, $t3, $t8

    #acc /= decay
    div $t3, $t2
    mflo $t3
    
    #manipulating the stack
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    #decrementing the length
    addi $a1, $t1, -1

    #putting acc back into $a3
    addi $a3, $t3, 0

    #doing the recursive call
    jal decaying_sum_helper

    #resetting the stack
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

#assuming that $a0 stores the pointer to the head of the list
sum_exponent:

    #copying the length
    addi $t0, $a0, 0

    #$f1 = 0.0
    addi $t1, $zero, 0
    mtc1 $t1, $f0
    cvt.d.w $f0, $f0

sum_exponent_loop:

    #while (head != NULL)
    lw $t2, 8($t0)
    beq $t2, $zero, return_value

    #sum += head->value
    l.d $f2, 0($t0)
    add.d $f0, $f0, $f2

    #head = head->next
    addi $t0, $t0, 12

    j sum_exponent_loop
return_value:

    mfc1 $t3, $f0

    #removing the signed bit
    sll $t3, $t3, 1

    #shifting it so the exponent occupies the 11 least significant bits of $f0
    srl $t3, $t3, 21

    #taking those exponent bits and putting them as our output.
    addi $v0, $t3, 0
    jr $ra

main:
    la $a0, xs
    addi $a1, $zero, 5
    addi $a2, $zero, 2
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    jal decaying_sum
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    li $v0, 10
    syscall
    .end main