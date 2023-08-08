/* 
	linker_script for cortexM3
	@Omar Ahmed
*/

MEMORY
{
	flash(RX) : ORIGIN = 0x08000000 , LENGTH = 128k
	sram(RWX) : ORIGIN = 0x20000000 , LENGTH = 20k
}

SECTIONS
{
	.text : {
		*(.vectors*) /*anything.vector*/
		*(.text*)
		*(.rodata)
		. = ALIGN(4);
		_E_text = . ;
	}> flash

	.data : {
		_s_data = .;
		*(.data)
		_E_data = .;
	}> sram AT> flash

	.bss : {
		_s_bss = . ;
		*(.bss*)
		_E_bss = .;
		. = ALIGN(4);
		. = . + 0x1000 ;
		stack_top = . ;
	}> sram
}