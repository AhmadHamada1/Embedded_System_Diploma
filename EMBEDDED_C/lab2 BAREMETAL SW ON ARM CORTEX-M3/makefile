cc=arm-none-eabi-
CFLAGS=-mcpu=cortex-m3 -g
INCS=-I
LIBS=
SRC=$(wildcard *.c)
OBJ= $(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s=.o)

all:learn-in-depth_cortexM4.hex

%.o: %.s
	$(cc)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(cc)gcc.exe $(INCS) $(CFLAGS)  -c $< -o $@	
learn-in-depth.elf: $(OBJ) $(ASOBJ)
	$(cc)ld.exe -T linker_script.ld  $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=Map_file.map
learn-in-depth_cortexM4.hex: learn-in-depth.elf
	$(cc)objcopy.exe -O binary $< $@
clean:
	rm -rf *.o *.bin *.elf	 *.map