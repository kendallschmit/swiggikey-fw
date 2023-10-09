#include "reg.h"

int main(void)
{
    REG_RCC_CR2 |= BIT(16); // Set HSI48ON
    // Wait for HSI48RDY
    while (1) {
        if (REG_RCC_CR2 & BIT(17)) {
            break;
        }
    }
    REG_RCC_CFGR |= BIT(1) | BIT(0); // Use HSI48 as system clock

    REG_RCC_AHBENR |= BIT(19); // Enable GPIOC peripheral clock
    REG_GPIOC_MODER |= BIT((7 * 2) + 0); // MODER14 = 01 (output)

    while (1) {
        REG_GPIOC_BSRR |= BIT(7 + 16);
        for (int volatile i = 0; i < 100000; i++)
        {
            // Wait
        }
        REG_GPIOC_BSRR |= BIT(7);
        for (int volatile i = 0; i < 100000; i++)
        {
            // Wait
        }
    }
    while (1);
}

void *prologue[] __attribute__((section (".prologue"))) = {
    (void *)0x20004000,
    (void *)main,
};
