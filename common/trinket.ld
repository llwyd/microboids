MEMORY {
    ROM  (rx)  : ORIGIN = 0x00000000, LENGTH = 256K
    RAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

STACK_SIZE = 0x1000;

SECTIONS
{
    . = ORIGIN(ROM);
    .text :
    {
        KEEP(*(.core_vectors))
        KEEP(*(.samd21_vectors))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } > ROM

    . = ORIGIN(RAM);
    .data :
    {
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT > ROM
    
    . = ALIGN(4);
    .bss :
    { 
        _sbss = .;
        *(.bss*)
        . = ALIGN(4);
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > RAM AT > ROM  

    .stack :
    {
        . = ALIGN(8);
        . += STACK_SIZE;
        . = ALIGN(8);
        _estack = .;
    } > RAM
}
