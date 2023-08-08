#ifndef APP_H_
#define APP_H_


#include "State.h"

// threshold is predefined by user 
#define  threshold  20

//application state
enum{
	app_pressure_detect,
	app_alarm_On
	
}app_state_id;

//prototypes
// pressure detection state
STATE_DEFINE(pressure_detection);

// alarm on state
STATE_DEFINE(app_alarm_on);

// reading pressure valure func.
void set_pressure_value();

//genric pointer to function
void (*app_pointer)();

#endif