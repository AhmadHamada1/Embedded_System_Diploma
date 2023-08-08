//application C code

#include "App.h"
#include "driver.h"

int Pval = 0;

//pressure detection 
STATE_DEFINE(pressure_detection){
	// state action
	app_state_id = app_pressure_detect;
	
	// pressure detection condition and updating app_pointer
	(Pval > threshold)?(app_pointer = STATE(app_alarm_on)): (app_pointer = STATE(pressure_detection));
	
}

//alarm on
STATE_DEFINE(app_alarm_on){
	// state action
	app_state_id = app_alarm_On;
	
	//send signal start alarm to actuator
	start_alarm();
	
	// update pointer to pressure_detection state
	app_pointer = STATE(pressure_detection);
}


void set_pressure_value(){
	//readig pressure value 

	Pval = getPressureVal();
	
}