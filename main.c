#include <stddef.h>

#include "reg.h"
#include "vectab.h"

VECTAB_SET(vectab_initial_stack_pointer, 0x20004000);

int main(void)
{
    REG_RCC_AHBENR |= BIT(19); // Enable GPIOC peripheral clock
    REG_GPIOC_MODER |= BIT((6 * 2) + 0); // Output mode for red LED
    REG_GPIOC_MODER |= BIT((8 * 2) + 0); // Output mode for orange LED
    REG_GPIOC_MODER |= BIT((9 * 2) + 0); // Output mode for green LED
    REG_GPIOC_MODER |= BIT((7 * 2) + 0); // Output mode for blue LED

    REG_GPIOC_BSRR |= BIT(8); // Orange LED

    REG_RCC_CR2 |= BIT(0); // Set HSI48ON
    // Wait for HSI48RDY to be high...
    while (1) {
        if (REG_RCC_CR2 & BIT(1)) {
            break;
        }
    }
    REG_RCC_CFGR |= BIT(1) | BIT(0); // Use HSI48 as system clock

    REG_GPIOC_BSRR |= BIT(8 + 16); // Orange LED

    REG_STK_RVR = 100000; // SysTick counts down from here
    REG_STK_CVR = 100000; // Initial value for counter
    REG_STK_CSR |= BIT(1); // Enable SysTick exception request
    REG_STK_CSR |= BIT(0); // Enable counter

    // Green LED
    while (1) {
        REG_GPIOC_BSRR |= BIT(9);
        for (int volatile i = 0; i < 100000; i++) {
            // Wait
        }
        REG_GPIOC_BSRR |= BIT(9 + 16);
        for (int volatile i = 0; i < 100000; i++) {
            // Wait
        }
    }
    while (1);
}
VECTAB_SET(vectab_reset, main);

// Blue LED
void handle_systick(void)
{
    static int a = 0;
    if (!a)
        REG_GPIOC_BSRR |= BIT(7);
    else
        REG_GPIOC_BSRR |= BIT(7 + 16);
    a = !a;

}
VECTAB_SET(vectab_systick, handle_systick);

void handle_hardfault(void)
{
    REG_GPIOC_BSRR |= BIT(6);
}
VECTAB_SET(vectab_hardfault, handle_hardfault);
