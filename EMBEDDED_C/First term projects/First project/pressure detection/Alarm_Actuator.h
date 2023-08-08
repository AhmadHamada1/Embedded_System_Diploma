#ifndef ALARMACTUATOR_H_
#define ALARMACTUATOR_H_
#include "State.h"


// alarm states.
enum{
	alarm_Init,
	alarm_On,
	alarm_waiting
}alarm_state_id;

//prototypes
//init
STATE_DEFINE(alarm_init);

//alarm on
STATE_DEFINE(alarm_on);

//alarm off
STATE_DEFINE(alarm_off);
//waiting
STATE_DEFINE(waiting);

//start alarm func.
void start_alarm();

// genric pointer to function
void (*alarm_pointer)();

#endif