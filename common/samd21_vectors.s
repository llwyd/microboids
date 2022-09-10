    .syntax unified
    .cpu cortex-m0plus
    .thumb

/* STM32 G0 ISRs */
.section .samd21_vectors
    /* Rest of vectors would go here */
    .word 0x0           /* 0 */
    .word 0x0           /* 1 */
    .word 0x0           /* 2 */
    .word 0x0           /* 3 */
    .word _eic          /* 4 */
    .word 0x0           /* 5 */
    .word 0x0           /* 6 */
    .word 0x0           /* 7 */
    .word 0x0           /* 8 */
    .word _sercom0      /* 9 */
    .word _sercom1      /* 10 */
    .word _sercom2      /* 11 */
    .word 0x0           /* 12 */
    .word 0x0           /* 13 */
    .word 0x0           /* 14 */
    .word _tcc0         /* 15 */
    .word _tcc1         /* 16 */
    .word _tcc2         /* 17 */
    .word 0x0           /* 18 */
    .word 0x0           /* 19 */
    .word 0x0           /* 20 */
    .word 0x0           /* 21 */
    .word 0x0           /* 22 */
    .word _adc          /* 23 */

.weak _tcc0
.thumb_set _tcc0, _unhandled_isr

.weak _tcc1
.thumb_set _tcc1, _unhandled_isr

.weak _tcc2
.thumb_set _tcc2, _unhandled_isr

.weak _sercom0
.thumb_set _sercom0, _unhandled_isr

.weak _sercom1
.thumb_set _sercom1, _unhandled_isr

.weak _sercom2
.thumb_set _sercom2, _unhandled_isr

.weak _eic
.thumb_set _eic, _unhandled_isr

.weak _adc
.thumb_set _adc, _unhandled_isr

.thumb_func
_unhandled_isr:
    b _unhandled_isr
