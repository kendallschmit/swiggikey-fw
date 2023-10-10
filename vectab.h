#ifndef VECTAB_H
#define VECTAB_H

// Pass a function to one of the VECTAB_X() macros to have the linker place the
// appropriate reference in the vector table.
//
// Functions should have no return value or arguments. They may be static.
#define VECTAB_RESET(fn)                      VECTAB_SET(vectab_reset, fn)
#define VECTAB_NMI(fn)                        VECTAB_SET(vectab_nmi, fn)
#define VECTAB_HARDFAULT(fn)                  VECTAB_SET(vectab_hardfault, fn)
#define VECTAB_SVCALL(fn)                     VECTAB_SET(vectab_svcall, fn)
#define VECTAB_PENDSV(fn)                     VECTAB_SET(vectab_pendsv, fn)
#define VECTAB_SYSTICK(fn)                    VECTAB_SET(vectab_systick, fn)
#define VECTAB_WWDG(fn)                       VECTAB_SET(vectab_wwdg, fn)
#define VECTAB_PVD_VDDIO2(fn)                 VECTAB_SET(vectab_pvd_vddio2, fn)
#define VECTAB_RTC(fn)                        VECTAB_SET(vectab_rtc, fn)
#define VECTAB_FLASH(fn)                      VECTAB_SET(vectab_flash, fn)
#define VECTAB_RCC_CRS(fn)                    VECTAB_SET(vectab_rcc_crs, fn)
#define VECTAB_EXTI0_1(fn)                    VECTAB_SET(vectab_exti0_1, fn)
#define VECTAB_EXTI2_3(fn)                    VECTAB_SET(vectab_exti2_3, fn)
#define VECTAB_EXTI4_15(fn)                   VECTAB_SET(vectab_exti4_15, fn)
#define VECTAB_TSC(fn)                        VECTAB_SET(vectab_tsc, fn)
#define VECTAB_DMA_CH1(fn)                    VECTAB_SET(vectab_dma_ch1, fn)
#define VECTAB_DMA_CH2_3_DMA2_CH1_2(fn)       VECTAB_SET(vectab_dma_ch2_3_dma2_ch1_2, fn)
#define VECTAB_DMA_CH4_5_6_7_DMA2_CH3_4_5(fn) VECTAB_SET(vectab_dma_ch4_5_6_7_dma2_ch3_4_5, fn)
#define VECTAB_ADC_COMP(fn)                   VECTAB_SET(vectab_adc_comp, fn)
#define VECTAB_TIM1_BRK_UP_TRG_COM(fn)        VECTAB_SET(vectab_tim1_brk_up_trg_com, fn)
#define VECTAB_TIM1_CC(fn)                    VECTAB_SET(vectab_tim1_cc, fn)
#define VECTAB_TIM2(fn)                       VECTAB_SET(vectab_tim2, fn)
#define VECTAB_TIM3(fn)                       VECTAB_SET(vectab_tim3, fn)
#define VECTAB_TIM6_DAC(fn)                   VECTAB_SET(vectab_tim6_dac, fn)
#define VECTAB_TIM7(fn)                       VECTAB_SET(vectab_tim7, fn)
#define VECTAB_TIM14(fn)                      VECTAB_SET(vectab_tim14, fn)
#define VECTAB_TIM15(fn)                      VECTAB_SET(vectab_tim15, fn)
#define VECTAB_TIM16(fn)                      VECTAB_SET(vectab_tim16, fn)
#define VECTAB_TIM17(fn)                      VECTAB_SET(vectab_tim17, fn)
#define VECTAB_I2C1(fn)                       VECTAB_SET(vectab_i2c1, fn)
#define VECTAB_I2C2(fn)                       VECTAB_SET(vectab_i2c2, fn)
#define VECTAB_SPI1(fn)                       VECTAB_SET(vectab_spi1, fn)
#define VECTAB_SPI2(fn)                       VECTAB_SET(vectab_spi2, fn)
#define VECTAB_USART1(fn)                     VECTAB_SET(vectab_usart1, fn)
#define VECTAB_USART2(fn)                     VECTAB_SET(vectab_usart2, fn)
#define VECTAB_USART3_4_5_6_7_8(fn)           VECTAB_SET(vectab_usart3_4_5_6_7_8, fn)
#define VECTAB_CEC_CAN(fn)                    VECTAB_SET(vectab_cec_can, fn)
#define VECTAB_USB(fn)                        VECTAB_SET(vectab_usb, fn)

// Do not use VECTAB_SET() directly. Use one of the macros defined above.
#define VECTAB_SET(name, fn) void *const (name) __attribute__((section("."#name))) = (void *)(fn)

#endif
