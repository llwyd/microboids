    .syntax unified
    .cpu cortex-m0plus
    .thumb

/* STM32 G0 ISRs */
.section .target_vectors
    /* Rest of vectors would go here */
    .word 0x0           /* 0 */
    .word 0x0           /* 1 */
    .word 0x0           /* 2 */
    .word 0x0           /* 3 */
    .word 0x0           /* 4 */
    .word 0x0           /* 5 */
    .word 0x0           /* 6 */
    .word 0x0           /* 7 */
    .word 0x0           /* 8 */
    .word 0x0           /* 9 */
    .word 0x0           /* 10 */
    .word 0x0           /* 11 */
    .word 0x0           /* 12 */
    .word 0x0           /* 13 */
    .word 0x0           /* 14 */
    .word _tim2         /* 15 */
    .word 0x0           /* 16 */
    .word 0x0           /* 17 */
    .word 0x0           /* 18 */
    .word 0x0           /* 19 */
    .word 0x0           /* 20 */
    .word 0x0           /* 21 */
    .word 0x0           /* 22 */
    .word 0x0           /* 23 */
    .word 0x0           /* 24 */
    .word 0x0           /* 25 */
    .word 0x0           /* 26 */
    .word 0x0           /* 27 */
    .word 0x0           /* 28 */
    .word 0x0           /* 29 */
    .word 0x0           /* 30 */
    .word 0x0           /* 31 */

.weak _tim2
.thumb_set _tim2, _unhandled_isr

.thumb_func
_unhandled_isr:
    b _unhandled_isr
