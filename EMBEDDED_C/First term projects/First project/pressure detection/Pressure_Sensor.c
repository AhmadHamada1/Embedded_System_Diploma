// pressure sensor c code
#include "Pressure_Sensor.h"
// init
STATE_DEFINE(sen_init){
	//state action
	sen_state_id = sen_Init;
	
	//update pointer to reading state
	sen_pointer = STATE(reading);
	
}

// reading state
STATE_DEFINE(reading){
	
	//state action
	sen_state_id = sen_reading;
	
	//read pressure value from sensor by calling this fun.
	set_pressure_value();
	
	//delay for 5 secs.
	Delay(5000);
	
	//update pointer to reading state

	sen_pointer = STATE(sen_init);
	
}


