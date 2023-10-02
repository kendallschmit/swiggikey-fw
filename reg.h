#ifndef REG_H
#define REG_H

#include <stdint.h>

#define REG32(addr) (*(uint32_t volatile *)(void *)(addr))

struct reg_gpio {
    uint32_t mode;
    uint32_t otype;
    uint32_t ospeed;
    uint32_t pupd;
    uint32_t id;
    uint32_t od;
    uint32_t bsr;
    uint32_t lck;
    uint32_t afrl;
    uint32_t afrh;
    uint32_t br;
};
#define REG_GPIOC_START 0x48000800


#define REG_RCC 0x40021000



#endif
