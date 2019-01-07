
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/err.h>

#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/sched_clock.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>

#include <mach/larm_one.h>

static void larm_put(const char c) {
    larm_write32(c, LARM_UART_REG_RTX);
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
		.virtual	= (u32)LARM_UART_REG_BASE,
		.pfn		= __phys_to_pfn(LARM_UART_REG_BASE),
		.length		= 0x100000,
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

static void larm_irq_mask(struct irq_data *d) {
}
static void larm_irq_unmask(struct irq_data *d) {
}
static struct irq_chip larm_irqchip = {
    .name       = "larm_irqchip",
    .irq_ack    = larm_irq_mask,
    .irq_mask   = larm_irq_mask,
    .irq_unmask = larm_irq_unmask,
};
static void larm_init_irq(void) {
    larm_print("larm_init_irq\n");
    irq_set_chip_and_handler(1, &larm_irqchip, handle_level_irq);
    irq_clear_status_flags(1, IRQ_NOREQUEST);
    irq_set_chip_and_handler(2, &larm_irqchip, handle_level_irq);
    irq_clear_status_flags(2, IRQ_NOREQUEST);
}


    /*
static struct clock_event_device larm_clockevent = {
    .name= "timer1",
    .features= CLOCK_EVT_FEAT_ONESHOT,
    .set_state_shutdown= ep93xx_clkevt_shutdown,
    .set_state_oneshot= ep93xx_clkevt_shutdown,
    .tick_resume= ep93xx_clkevt_shutdown,
    .set_next_event= ep93xx_clkevt_set_next_event,
    .rating= 400,
};
    */

static irqreturn_t larm_timer_interrupt(int irq, void *dev_id)
{
    larm_clearbit32(LARM_INTERRUPT_TIMER, LARM_INTERRUPT_REG_SOURCE);  //clear timer interrupt
//    larm_print("larm_timer_interrupt\n");
    timer_tick();
    return IRQ_HANDLED;
}
static struct irqaction larm_timer_irq = {
    .name= "larm timer",
    .flags= IRQF_TIMER|IRQF_IRQPOLL,
    .handler= larm_timer_interrupt,
};

static void __init larm_init_time(void) {
    larm_print("larm_init_time\n");
    /*
	clocksource_mmio_init(NULL, "timer4",
			      EP93XX_TIMER4_RATE, 200, 40,
			      ep93xx_clocksource_read);
	sched_clock_register(ep93xx_read_sched_clock, 40,
			     EP93XX_TIMER4_RATE);
                 */
    larm_write32(10000, LARM_TIMER_REG_FREQ);  //set freq
    larm_setbit32(LARM_INTERRUPT_TIMER, LARM_INTERRUPT_REG_ENABLE); //enable_irq
    larm_write32(100, LARM_TIMER_REG_COUNTER); //set counter
    larm_write32(1, LARM_TIMER_REG_ENABLE); //start timer
    
	setup_irq(2, &larm_timer_irq);
//	clockevents_config_and_register(&larm_clockevent, 100, 1, 0xffffffffU);
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
