    .syntax unified
    .cpu cortex-m4
    .thumb

/* Generic Vectors for M4 Arm Chips */
.section .core_vectors
    .word _estack       /* 0x00 Top of Stack */
    .word _reset        /* 0x04 Reset */
    .word _nmi          /* 0x08 NMI */
    .word _hardFault    /* 0x0C Hard Fault */
    
    .word _memManage    /* 0x10 Reserved */
    .word _busFault     /* 0x14 Reserved */
    .word _usageFault   /* 0x18 Reserved */
    .word 0x0           /* 0x1C Reserved */
    .word 0x0           /* 0x20 Reserved */
    .word 0x0           /* 0x24 Reserved */
    .word 0x0           /* 0x28 Reserved */
    .word _svCall       /* 0x2C SV Call */
    .word _debug        /* 0x30 Monitor */
    .word 0x0           /* 0x34 Reserved */
    .word _pEndSV       /* 0x38 Pendable request for system service */
    .word _sysTick      /* 0x3C SysTick timer */

.text
.weak _reset
.thumb_set _reset, core_dead

.weak _nmi
.thumb_set _nmi, core_dead

.weak _hardFault
.thumb_set _hardFault, core_dead

.weak _memManage
.thumb_set _memManage, core_dead

.weak _busFault
.thumb_set _busFault, core_dead

.weak _usageFault
.thumb_set _usageFault, core_dead

.weak _svCall
.thumb_set _svCall, core_dead

.weak _debug
.thumb_set _debug, core_dead

.weak _pEndSV
.thumb_set _pEndSV, core_dead

.weak _sysTick
.thumb_set _sysTick, core_dead

.thumb_func
core_dead:
    b core_dead

