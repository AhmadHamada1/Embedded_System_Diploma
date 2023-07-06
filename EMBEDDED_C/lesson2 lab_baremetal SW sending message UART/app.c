#include "uart.h"

unsigned char Arrstr[100] = "learn-in-depth:<Belal>";

void main(){

	Uart_send_str(Arrstr);
}
