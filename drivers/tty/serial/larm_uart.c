#include <linux/module.h>
#include <linux/console.h>
#include <linux/serial.h>
#include <linux/serial_core.h>
#include <linux/tty.h>

#define LARM_SERIAL_DEV_NAME "ttyLARM"

static void larm_console_write(struct console *co, const char *s,
                        unsigned int count) {
}

static int larm_console_setup(struct console *co, char *options) {
}

static struct uart_driver larm_uart_driver;
static struct console larm_uart_console = {
	.name		= LARM_SERIAL_DEV_NAME,
	.device		= uart_console_device,
	.write		= larm_console_write,
	.setup		= larm_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &larm_uart_driver,
};

static struct uart_driver larm_uart_driver = {
	.owner		= THIS_MODULE,
	.driver_name	= "larm_uart",
	.dev_name	= LARM_SERIAL_DEV_NAME,
	.major		= 0,
	.minor		= 0,
	.nr		= 1,
#ifdef CONFIG_SERIAL_LARM_CONSOLE
	.cons		= &larm_uart_console,
#endif
};

static int __init larm_uart_init(void) {
}

static void __exit larm_uart_exit(void) {
}

module_init(larm_uart_init);
module_exit(larm_uart_exit);
