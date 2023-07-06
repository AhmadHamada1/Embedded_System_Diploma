typedef volatile unsigned int vuint32_t;
#include <stdint.h>
//register address

#define Rcc_base 0x40021000
#define GBIO_base 0x40010800
#define Rcc_APB2ENR *(volatile uint32_t*)(Rcc_base + 0x18)
#define GBIO_CRH    *(volatile uint32_t*)(GBIO_base + 0x04)
#define GBIO_ODR    *(volatile uint32_t*)(GBIO_base + 0x0c)

typedef union{
    vuint32_t   all_fields;
    struct{
    vuint32_t reserved:13;
    vuint32_t p_13:1;
    }p13;
}R_ODR_t;

volatile R_ODR_t* PT_ODR = (volatile R_ODR_t*) (GBIO_base + 0x0c);

int main()
{
    Rcc_APB2ENR |= (1<<2);
    GBIO_CRH &= 0xff0fffff;
    GBIO_CRH |= 0x00200000;

    while(1){
       PT_ODR->p13.p_13 =1;
       for(int i =0; i< 5000;i++);
       PT_ODR->p13.p_13 =0;
       for(int i =0; i< 5000;i++);
    }

}
