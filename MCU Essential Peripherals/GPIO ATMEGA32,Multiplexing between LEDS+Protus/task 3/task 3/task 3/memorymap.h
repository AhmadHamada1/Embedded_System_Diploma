/*
 * memorymap.h
 *
 * Created: 12/20/2022 9:43:23 PM
 *  Author: madaa
 */ 


#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

#define DDRA (*(volatile unsigned char *)0x3A)
#define PORTA (*(volatile unsigned char *)0x3B)
#define PINA (*(volatile unsigned char *)0x39)


#define PORTD (*(volatile unsigned char *)0x32)
#define DDRD (*(volatile unsigned char *)0x31)
#define PIND (*(volatile unsigned char *)0x30)

#define setbit(reg,bit)     (reg=reg|(1<<bit))
#define clearbit(reg,bit)   (reg=reg &~(1<<bit))
#define readbit(reg,bit)    ((reg>>bit)&1)





#endif /* MEMORYMAP_H_ */