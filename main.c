#include "reg.h"

// Things we need
//
// LED is PC7
//
// Bit set and reset register (GPIOx_ BSRR) for bitwise write access to
// GPIOx_ODR
//
// Locking mechanism (GPIOx_LCKR) provided to freeze the port A or B I/O port
// configuration
//
// Each of the GPIO ports has four 32-bit memory-mapped control registers
// (GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR, GPIOx_PUPDR) to configure up to 16
// I/Os. The GPIOx_MODER register is used to select the I/O mode (input, output,
// AF, analog). The GPIOx_OTYPER and GPIOx_OSPEEDR registers are used to select
// the output type (push- pull or open-drain) and speed. The GPIOx_PUPDR
// register is used to select the pull- up/pull-down whatever the I/O direction.
//
// Each GPIO has two 16-bit memory-mapped data registers: input and output data
// registers (GPIOx_IDR and GPIOx_ODR). GPIOx_ODR stores the data to be output,
// it is read/write accessible. The data input through the I/O are stored into
// the input data register (GPIOx_IDR), a read-only register.

int main(void)
{
    REG_RCC_AHBENR |= 1 << 19;

    REG_GPIOC_MODER |= 1 << ((7 * 2) + 0);

    while (1) {
        REG_GPIOC_BSRR |= 1 << (7 + 16);
        for (int volatile i = 0; i < 100000; i++)
        {
            // Wait
        }
        REG_GPIOC_BSRR |= 1 << (7);
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
