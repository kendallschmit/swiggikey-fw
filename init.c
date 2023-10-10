#include "vectab.h"

// main() should be defined somewhere else
extern int main(void);

// Section boundaries for initialization
extern char ld_section_data_lma[];
extern char ld_section_data_vma[];
extern char ld_section_data_vma_end[];
extern char ld_section_bss_vma[];
extern char ld_section_bss_vma_end[];

static void init(void)
{
    // Load values into .data section
    char *dest = ld_section_data_vma;
    char *src = ld_section_data_lma;
    while (dest != ld_section_data_vma_end) {
        *dest = *src;
        dest++;
        src++;
    }

    // Zero .bss section
    dest = ld_section_bss_vma;
    while (dest != ld_section_bss_vma_end) {
        *dest = 0;
        dest++;
    }

    // Execute main
    main();

    // Infinite loop
    while (1);
}
VECTAB_RESET(init); // Make init() the first thing that runs
