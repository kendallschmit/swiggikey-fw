#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "reg.h"
#include "vectab.h"

static void handle_systick(void);
static void handle_hardfault(void);

static void busy_wait(int count);

uint32_t systick = 0;
int blink_state = 1;

int main(void)
{
    // Use 48MHz clock (HSI48) //

    REG_FLASH_ACR |= BIT32(1); // Set flash latency to 001
    REG_RCC_CR2 |= REG_RCC_CR2_HSI48ON; // Enable HSI48
    while (!(REG_RCC_CR2 & REG_RCC_CR2_HSI48RDY)) {
        // Wait for 48MHz clock to be ready
    }
    REG_RCC_CFGR |= BIT32(1) | BIT32(0); // Use HSI48 as system clock


    // Init GPIO //

    REG_RCC_AHBENR |= BIT32(19); // Enable GPIOC peripheral clock
    REG_GPIOC_MODER |= BIT32((6 * 2) + 0); // Output mode for red LED
    REG_GPIOC_MODER |= BIT32((8 * 2) + 0); // Output mode for orange LED
    REG_GPIOC_MODER |= BIT32((9 * 2) + 0); // Output mode for green LED
    REG_GPIOC_MODER |= BIT32((7 * 2) + 0); // Output mode for blue LED


    // Set up SysTick //

    REG_STK_RVR = 48000 - 1; // Count every 48000 cycles (1ms)
    REG_STK_CVR = 0; // Clear current counter value
    REG_STK_CSR |= BIT32(2); // Clock source is processor clock
    REG_STK_CSR |= BIT32(1); // Enable SysTick exception request
    REG_STK_CSR |= BIT32(0); // Enable counter


    // Blink green LED (roughly) twice per second using busy waits //

    while (1) {
        REG_GPIOC_BSRR |= BIT32(9);
        busy_wait(500000);
        REG_GPIOC_BSRR |= BIT32(9 + 16);
        busy_wait(500000);
    }
}

static void handle_systick(void)
{
    // Orange LED is on for 1000ms. After that, the blue LED blinks twice per
    // second.
    if (systick < 1000) {
        REG_GPIOC_BSRR |= BIT32(8);
    }
    else {
        REG_GPIOC_BSRR |= BIT32(8 + 16);
        if (systick % 250 == 0) {
            if (!blink_state)
                REG_GPIOC_BSRR |= BIT32(7);
            else
                REG_GPIOC_BSRR |= BIT32(7 + 16);
            blink_state = !blink_state;
        }
    }
    systick++;
}
VECTAB_SYSTICK(handle_systick);

static void handle_hardfault(void)
{
    REG_RCC_AHBENR |= BIT32(19); // Enable GPIOC peripheral clock
    REG_GPIOC_MODER |= BIT32((6 * 2) + 0); // Output mode for red LED
    REG_GPIOC_BSRR |= BIT32(6); // Red LED
}
VECTAB_HARDFAULT(handle_hardfault);

static void busy_wait(int count)
{
    for (int volatile i = 0; i < count; i++) {
        // Wait
    }
}
