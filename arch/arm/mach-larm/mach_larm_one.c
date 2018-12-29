
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
#include <asm/mach/map.h>

#define UFCON0	((volatile unsigned int *)(0xFF000000))

static void larm_put(const char c) {
    *UFCON0=c;
}
static void larm_puts(const char *str) {
	while(*str){
		larm_put(*str++);
	};
}

void larm_print(const char *str, ...)
{
	char buf[256];
	va_list ap;

	va_start(ap, str);
	vsnprintf(buf, sizeof(buf), str, ap);
	va_end(ap);
    
    larm_puts(buf);
}

void larm_jump1(void) {
}

static struct map_desc larm_iodesc[] __initdata = {
	{	/* IO space	*/
		.virtual	= (u32)0xFF000000,
		.pfn		= __phys_to_pfn(0xFF000000),
		.length		= 0xF0000,
		.type		= MT_DEVICE,
    },
};

static void larm_l2c_write_sec(unsigned long l, unsigned u){
    larm_print("larm_l2c_write_sec\n");
}
static bool larm_smp_init(void) {
    larm_print("larm_smp_init\n");
}
static void larm_fixup(struct tag *t, char **s) {
    larm_print("larm_fixup\n");
}
static void larm_dt_fixup(void) {
    larm_print("larm_dt_fixup\n");
}
long long larm_pv_fixup(void) {
    larm_print("larm_pv_fixup\n");
}
static void larm_reserve(void) {
    larm_print("larm_reserve\n");
}
static void __init larm_map_io(void) {
    iotable_init(larm_iodesc, ARRAY_SIZE(larm_iodesc));
}
static void larm_init_early(void) {
    larm_print("larm_init_early\n");
}
static void larm_init_irq(void) {
    larm_print("larm_init_irq\n");
}
static void larm_init_time(void) {
    larm_print("larm_init_time\n");
}
static void larm_init_machine(void) {
    larm_print("larm_init_machine\n");
}
static void larm_init_late(void) {
    larm_print("larm_init_late\n");
}
static void larm_restart(enum reboot_mode r, const char *s) {
    larm_print("larm_restart\n");
}
#ifdef CONFIG_GENERIC_IRQ_MULTI_HANDLER
static void larm_handle_irq(struct pt_regs *p) {
    larm_print("larm_handle_irq\n");
}
#endif

MACHINE_START(LARM_ONE, "larm_one")
	//.atag_offset = 0x100,
	.map_io = larm_map_io,
	.init_early = larm_init_early,
	.init_irq = larm_init_irq,
	.init_machine	= larm_init_machine,
	.init_late	= larm_init_late,
	.init_time	= larm_init_time,
	.restart	= larm_restart,
MACHINE_END
