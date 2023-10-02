MEMORY
{
    flash   (RX) : ORIGIN = 0x08000000, LENGTH = 128K
    sram    (RW) : ORIGIN = 0x20000000, LENGTH = 16K
}

ENTRY(main);

SECTIONS {
    .text :
    {
        KEEP(*(.prologue));
        *(.text)
    } > flash

    .data :
    {
        *(.data)
    } > sram
}


