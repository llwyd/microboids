MEMORY {
    ROM  (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
    RAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

STACK_SIZE = 0x1000;

SECTIONS
{
    . = ORIGIN(ROM);
    .text :
    {
        KEEP(*(.core_vectors))
        KEEP(*(.target_vectors))
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
    
    . = ALIGN(4);
    .no_init :
    {
        _sno_init = .;
        *(.no_init*)
        . = ALIGN(4);
        _eno_init = .;
    } > RAM AT > ROM  

    .stack :
    {
        . = ALIGN(8);
        . += STACK_SIZE;
        . = ALIGN(8);
        _estack = .;
    } > RAM
}
