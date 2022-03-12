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

.thumb_func
dead:
    b dead
