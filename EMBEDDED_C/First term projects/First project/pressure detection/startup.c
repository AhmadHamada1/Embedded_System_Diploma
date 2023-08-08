/*Eng.Ali Abo Oof*/

#include"stdint.h"
#define STACK_start_sp 0x20001000
extern int main(void);
void Rest_Handler(void);
void Default_Handler()
{
    Rest_Handler();
}
void NMI_Handler(void)__attribute__((weak,alias("Default_Handler")));
void HardFault_Handler(void)__attribute__((weak,alias("Default_Handler")));
void MemManage_Handler(void)__attribute__((weak,alias("Default_Handler")));
void BusFault_Handler(void)__attribute__((weak,alias("Default_Handler")));
void UsageFault_Handler(void)__attribute__((weak,alias("Default_Handler")));
extern unsigned int stack_top;



uint32_t Vectors[]__attribute__((section(".vectors"))) = {
    (uint32_t)&stack_top,
    (uint32_t)&Rest_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler
};



extern unsigned int _E_text ;
extern unsigned int _s_data ;
extern unsigned int _E_data ;
extern unsigned int _s_bss ;
extern unsigned int _E_bss ;




void Rest_Handler(void){
	unsigned int data_size = (unsigned char *)&_E_data -(unsigned char *) &_s_data ;
	unsigned char*p_src = (unsigned char *) _E_text;
	unsigned char *p_dst = (unsigned char *) _s_data;
	int i;
	for( i=0 ; i<data_size;i++){
		*((unsigned char *)p_dst++)= *((unsigned char*)p_src++);
	}
	unsigned int bss_size = (unsigned char *)&_E_bss -(unsigned char *) &_s_bss ;
	for( i=0 ; i<bss_size;i++){
		*((unsigned char *)p_dst++)= (unsigned char) 0;
	}
	main();
}