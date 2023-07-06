/*
 * memorymap.h
 *
 *  Created on: Dec 20, 2022
 *      Author: madaa
 */

#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

//RCC
#define RCC_BASE 0x40021000
#define RCC_ABP2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_IOPAEN (1<<2)




//GPIO
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)
//#define GPIOA13 (1UL<<13)

#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)





#endif /* MEMORYMAP_H_ */
