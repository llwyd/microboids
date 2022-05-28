    .syntax unified
    .cpu cortex-m0plus
    .thumb

/* Generic Vectors for M0+ Arm Chips */
.section .isr_vectors
    .word _estack       /* 0x00 Top of Stack */
    .word _reset        /* 0x04 Reset */
    .word _nmi          /* 0x08 NMI */
    .word _hardFault    /* 0x0C Hard Fault */
    
    .word 0x0           /* 0x10 Reserved */
    .word 0x0           /* 0x14 Reserved */
    .word 0x0           /* 0x18 Reserved */
    .word 0x0           /* 0x1C Reserved */
    .word 0x0           /* 0x20 Reserved */
    .word 0x0           /* 0x24 Reserved */
    .word 0x0           /* 0x28 Reserved */
    .word _svCall       /* 0x2C SV Call */
    .word _debug        /* 0x30 Monitor */
    .word 0x0           /* 0x34 Reserved */
    .word _pEndSV       /* 0x38 Pendable request for system service */
    .word _sysTick      /* 0x3C SysTick timer */

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

.text
.weak _reset
.thumb_set _reset, dead

.weak _nmi
.thumb_set _nmi, dead

.weak _hardFault
.thumb_set _hardFault, dead

.weak _memManage
.thumb_set _memManage, dead

.weak _busFault
.thumb_set _busFault, dead

.weak _usageFault
.thumb_set _usageFault, dead

.weak _svCall
.thumb_set _svCall, dead

.weak _debug
.thumb_set _debug, dead

.weak _pEndSV
.thumb_set _pEndSV, dead

.weak _sysTick
.thumb_set _sysTick, dead

.weak _tcc0
.thumb_set _tcc0, dead

.weak _tcc1
.thumb_set _tcc1, dead

.weak _tcc2
.thumb_set _tcc2, dead

.weak _sercom0
.thumb_set _sercom0, dead

.weak _sercom1
.thumb_set _sercom1, dead

.weak _sercom2
.thumb_set _sercom2, dead

.weak _eic
.thumb_set _eic, dead

.thumb_func
dead:
    b dead
