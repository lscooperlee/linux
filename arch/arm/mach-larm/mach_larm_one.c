
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/rawnand.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/clk.h>
#include <linux/spi/spi.h>
#include <linux/spi/eeprom.h>
#include <linux/platform_data/i2c-davinci.h>
#include <linux/platform_data/mmc-davinci.h>
#include <linux/platform_data/mtd-davinci.h>
#include <linux/platform_data/usb-davinci.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>

//#include <mach/serial.h>

MACHINE_START(LARM_ONE, "larm_one")
	//.atag_offset = 0x100,
	.map_io = NULL,
	.init_early = NULL,
	.init_irq = NULL,
	.init_machine	= NULL,
	.init_late	= NULL,
	.init_time	= NULL,
	.restart	= NULL,
MACHINE_END
