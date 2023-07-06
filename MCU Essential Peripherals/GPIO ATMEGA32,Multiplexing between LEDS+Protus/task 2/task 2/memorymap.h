/*
 * memorymap.h
 *
 * Created: 12/20/2022 7:47:39 PM
 *  Author: madaa
 */ 


#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

#define DDRA (*(volatile unsigned char *)0x3A)
#define PORTA (*(volatile unsigned char *)0x3B)
#define PINA (*(volatile unsigned char *)0x39)


#define PORTC (*(volatile unsigned char *)0x35)
#define DDRC (*(volatile unsigned char *)0x34)
#define PINC (*(volatile unsigned char *)0x33)

#define setbit(reg,bit)     (reg=reg|(1<<bit))
#define clearbit(reg,bit)   (reg=reg &~(1<<bit))
#define readbit(reg,bit)    ((reg>>bit)&1)



#endif /* MEMORYMAP_H_ */