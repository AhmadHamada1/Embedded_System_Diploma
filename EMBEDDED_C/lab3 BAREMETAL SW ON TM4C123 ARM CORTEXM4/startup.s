

.word 	0x20001000   
.word 	_reset
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler
.word 	Vector_handler


_reset:
	bl main
	b .
Vector_handler:
	b _reset