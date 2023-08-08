#ifndef PRESSURESENEOR_H_
#define PRESSURESENEOR_H_


#include "State.h"




// pressure sensor states
enum{
	sen_Init,
	sen_reading,
	
}sen_state_id;

// prototypes

// initial state
STATE_DEFINE(sen_init);

// reading pressure values state
STATE_DEFINE(reading);


// genric pointer to function
void (*sen_pointer)();

#endif