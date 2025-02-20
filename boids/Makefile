NAME = boids
TARGET = TARGET_STM32

SRC =  boids.c qmath.c trig.c events.c fifo_base.c state.c clock.c bird.c timer.c i2c.c display.c systick.c gpio.c random.c
OBJ = $(SRC:.c=.o)

CC = arm-none-eabi-gcc
ASM = arm-none-eabi-as

HAL_DIR = ../hal/stm32g0
SRCDIR = ../common
BOILERPLATE_DIR = ../boilerplate/src
BIRD_DIR = ../conway/bird
BIRD_COMMON_DIR = ../conway/common
OPT = -O3

CFLAGS = -std=gnu11 -Wall -Wfatal-errors -c $(OPT) -g -I$(BIRD_DIR) -I$(BIRD_COMMON_DIR) -I$(SRCDIR) -I$(HAL_DIR) -I$(BOILERPLATE_DIR) -ffreestanding -nostdlib -nostartfiles -mcpu=cortex-m0plus -mthumb -fdata-sections -ffunction-sections -D $(TARGET) -D TARGET_ARM -D NDEBUG
ASMFLAGS = -g -mcpu=cortex-m0plus -mthumb 
LDFLAGS = -print-memory-usage -nostdlib --gc-sections

COMMON_DIR = ../common

STARTUP_STM32 = m0plus_vectors.o target_vectors.o startup.o

$(NAME).bin: $(NAME).elf
	arm-none-eabi-objcopy -Obinary boids.elf boids.bin
$(NAME).elf: $(OBJ) $(STARTUP_STM32) $(HAL_DIR)/memory.ld
	arm-none-eabi-ld -Map $(NAME).map -T$(HAL_DIR)/memory.ld -o $(NAME).elf $(OBJ) $(STARTUP_STM32) $(LDFLAGS)

%.o : $(COMMON_DIR)/%.s
	$(ASM) -c $(ASMFLAGS) -o $@ $<
%.o : $(HAL_DIR)/%.s
	$(ASM) -c $(ASMFLAGS) -o $@ $<
%.o : $(HAL_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<
%.o : $(BOILERPLATE_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<
%.o : $(BIRD_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<
%.o : $(BIRD_COMMON_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<
%.o : $(COMMON_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm *.o *.elf *.map *.bin
debug:
	openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/stm32g0x.cfg
flash:
	openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/stm32g0x.cfg -c "program boids.bin exit 0x08000000 verify reset"
gdb:
	arm-none-eabi-gdb -ex "target extended-remote localhost:3333" boids.elf
dump:
	hexdump -C boids.bin
objdump:
	arm-none-eabi-objdump -t boids.elf
