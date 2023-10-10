MEMORY {
    flash (RX) : ORIGIN = 0x08000000, LENGTH = 128K
    sram  (RW) : ORIGIN = 0x20000000, LENGTH = 16K
}

SECTIONS {
    /* Vector table */
    .vector_table : ALIGN(4) {
        . = 0x0000; LONG(ORIGIN(sram) + LENGTH(sram)); /* Init stack pointer */
        . = 0x0004; KEEP(*(.vectab_reset));
        . = 0x0008; KEEP(*(.vectab_nmi));
        . = 0x000c; KEEP(*(.vectab_hardfault));
        . = 0x002c; KEEP(*(.vectab_svcall));
        . = 0x0038; KEEP(*(.vectab_pendsv));
        . = 0x003c; KEEP(*(.vectab_systick));
        . = 0x0040; KEEP(*(.vectab_wwdg));
        . = 0x0044; KEEP(*(.vectab_pvd_vddio2));
        . = 0x0048; KEEP(*(.vectab_rtc));
        . = 0x004c; KEEP(*(.vectab_flash));
        . = 0x0050; KEEP(*(.vectab_rcc_crs));
        . = 0x0054; KEEP(*(.vectab_exti0_1));
        . = 0x0058; KEEP(*(.vectab_exti2_3));
        . = 0x005c; KEEP(*(.vectab_exti4_15));
        . = 0x0060; KEEP(*(.vectab_tsc));
        . = 0x0064; KEEP(*(.vectab_dma_ch1));
        . = 0x0068; KEEP(*(.vectab_dma_ch2_3_dma2_ch1_2));
        . = 0x006c; KEEP(*(.vectab_dma_ch4_5_6_7_dma2_ch3_4_5));
        . = 0x0070; KEEP(*(.vectab_adc_comp));
        . = 0x0074; KEEP(*(.vectab_tim1_brk_up_trg_com));
        . = 0x0078; KEEP(*(.vectab_tim1_cc));
        . = 0x007c; KEEP(*(.vectab_tim2));
        . = 0x0080; KEEP(*(.vectab_tim3));
        . = 0x0084; KEEP(*(.vectab_tim6_dac));
        . = 0x0088; KEEP(*(.vectab_tim7));
        . = 0x008c; KEEP(*(.vectab_tim14));
        . = 0x0090; KEEP(*(.vectab_tim15));
        . = 0x0094; KEEP(*(.vectab_tim16));
        . = 0x0098; KEEP(*(.vectab_tim17));
        . = 0x009c; KEEP(*(.vectab_i2c1));
        . = 0x00a0; KEEP(*(.vectab_i2c2));
        . = 0x00a4; KEEP(*(.vectab_spi1));
        . = 0x00a8; KEEP(*(.vectab_spi2));
        . = 0x00ac; KEEP(*(.vectab_usart1));
        . = 0x00b0; KEEP(*(.vectab_usart2));
        . = 0x00b4; KEEP(*(.vectab_usart3_4_5_6_7_8));
        . = 0x00b8; KEEP(*(.vectab_cec_can));
        . = 0x00bc; KEEP(*(.vectab_usb));
    } >flash AT>flash

    /* Code */
    .text : ALIGN(4) {
        *(.text)
        *(.text.*)
    } >flash AT>flash

    /* Initialized data */
    .data : {
        *(.data)
        *(.data.*)
    } >sram AT>flash

    /* Uninitialized data */
    .bss : {
        *(.bss)
        *(.bss.*)
    } >sram AT>sram

    /* Section boundries so we can initialize .data and .bss */
    PROVIDE(ld_section_data_lma = LOADADDR(.data));
    PROVIDE(ld_section_data_vma = ADDR(.data));
    PROVIDE(ld_section_data_vma_end = ADDR(.data) + SIZEOF(.data));
    PROVIDE(ld_section_bss_vma = ADDR(.bss));
    PROVIDE(ld_section_bss_vma_end = ADDR(.bss) + SIZEOF(.bss));
}


