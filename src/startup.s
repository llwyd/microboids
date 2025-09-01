    .text
    .syntax unified
    .cpu cortex-m0plus
    .thumb


.globl _reset
.thumb_func
_reset:
    /* Copy Data values from ROM -> SRAM */
    ldr r0, = _etext 

    ldr r1, = _sdata
    ldr r2, = _edata
    cmp r1, r2
    beq copiedtoram
    bl copytoram

copiedtoram:
    /* Clear BSS Region */
    ldr r1, = _sbss
    movs r4, #4
clearbss:
    ldr r2, = _ebss
    
    cmp r1, r2
    beq bsscleared
    
    movs r0, #0x00
    /* Store 0x0 in location held in r1 */
    str r0, [r1]
    add r1, r4

    cmp r1, r2
    bne clearbss

bsscleared:
    /* Disable interrupts */
    CPSID IF

    bl main

/*  Function for copying from rom to ram:
*   r0 = current source location
*   r1 = start of target location
*   r2 = end of target location
*/
copytoram:
    push {r4-r7, lr}
    movs r4, #4
copy:
    /* load from ROM and post increment */
    ldr r3, [r0]
    add r0, r4
    /* Store in RAM and post increment */
    str r3, [r1]
    add r1, r4

    /* Compare current data pointer to end
     * and if equal, then branch to main
     */
    cmp r1, r2
    bne copy

    /* Return */
    pop {r4-r7, pc}

dead:
	b dead
