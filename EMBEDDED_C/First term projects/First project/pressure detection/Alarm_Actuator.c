#include "Alarm_Actuator.h"
#include "driver.h"




STATE_DEFINE(alarm_init){
	// state action
	alarm_state_id = alarm_Init;
	
	//update alarm_pointer to alarm_off
	alarm_pointer = STATE(alarm_off);
}
STATE_DEFINE(alarm_on){
	// state action
	alarm_state_id = alarm_On;
	
	//start alarm
	Set_Alarm_actuator(0);
	
	//wait for delay
	Delay(3000);
	
	//stop alarm
	Set_Alarm_actuator(1);
	
	//update alarm_pointer to waiting
	alarm_pointer = STATE(waiting);
	
}

STATE_DEFINE(waiting){
	//state action
	alarm_state_id = alarm_waiting;
}

STATE_DEFINE(alarm_off){
	//stop alarm
	Set_Alarm_actuator(1);
	
	//update alarm_pointer to waiting
	alarm_pointer = STATE(waiting);
}

void start_alarm(){
	
	//update alarm_pointer to alarm_on
	alarm_pointer = STATE(alarm_on);
}