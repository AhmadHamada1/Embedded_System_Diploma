#include <stdint.h>
#include <stdio.h>


#include "Pressure_Sensor.h"
#include "App.h"
#include "Alarm_Actuator.h"
#include "driver.h"


void setup();
int main (){
	
	setup();
	while (1)
	{
		//Implement your Design 
		alarm_pointer();
		sen_pointer();
		app_pointer();
		
		
	}

}


void setup(){
	GPIO_INITIALIZATION();
	app_pointer = STATE(pressure_detection);
	alarm_pointer = STATE(alarm_off);
	sen_pointer = STATE(sen_init);
}