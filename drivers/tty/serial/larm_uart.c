#include <linux/module.h>
#include <linux/console.h>
#include <linux/serial.h>
#include <linux/serial_core.h>
#include <linux/tty.h>

#define UFCON0	((volatile unsigned int *)(0xFF000000))
static void larm_put(const char c) {
    *UFCON0=c;
}
static void early_larm_putc(struct uart_port *port, int c) {
    larm_put(c);
}
static void early_larm_write(struct console *console,
				 const char *s, unsigned n)
{
	struct earlycon_device *device = console->data;
	uart_console_write(&device->port, s, n, early_larm_putc);
}

static int __init early_larm_setup(struct earlycon_device *device,
				       const char *options)
{
	device->con->write = early_larm_write;
	return 0;
}
EARLYCON_DECLARE(larm, early_larm_setup);

#define LARM_SERIAL_DEV_NAME    "ttyLARM"
#define LARM_NR_UARTS           1

static struct uart_port larm_port[LARM_NR_UARTS];
static struct uart_port *console_port;


static unsigned int larm_tx_empty(struct uart_port *port){
    printk("larm_tx_emtpy\n");
    return 0;
}
static void larm_set_mctrl(struct uart_port *port, unsigned int mctrl){
    printk("larm_set_mctrl\n");
}
static unsigned int larm_get_mctrl(struct uart_port *port){
    printk("larm_get_mctrl\n");
    return 0;
}
static void larm_stop_tx(struct uart_port *port){
    printk("larm_stop_tx\n");
}
static void larm_start_tx(struct uart_port *port){
    printk("larm_start_tx\n");
}
static void larm_throttle(struct uart_port *port){
    printk("larm_start_tx\n");
}
static void larm_unthrottle(struct uart_port *port){
    printk("larm_unthrottle\n");
}
static void larm_send_xchar(struct uart_port *port, char ch){
    printk("larm_send_xchar\n");
}
static void larm_stop_rx(struct uart_port *port){
    printk("larm_stop_rx\n");
}
static void	larm_enable_ms(struct uart_port *port){
    printk("larm_enable_ms\n");
}
static void	larm_break_ctl(struct uart_port *port, int ctl){
    printk("larm_break_ctl\n");
}
static int larm_startup(struct uart_port *port){
    printk("larm_startup\n");
    return 0;
}
static void	larm_shutdown(struct uart_port *port){
    printk("larm_shutdown\n");
}
static void	larm_flush_buffer(struct uart_port *port){
    printk("larm_flush_buffer\n");
}

static void	larm_set_termios(struct uart_port *port, struct ktermios *new, struct ktermios *old){
    printk("larm_set_termios\n");
}

static void	larm_set_ldisc(struct uart_port *port, struct ktermios *k){
    printk("larm_set_ldisc\n");
}
static const char *larm_type(struct uart_port *port) {
    printk("larm_type\n");
    return NULL;
}

static void larm_pm(struct uart_port *port, unsigned int state, unsigned int oldstate){
    printk("larm_pm\n");
}
/*
 * Return a string describing the type of the port
 */
static const char larm_pe(struct uart_port *port){
    printk("larm_pe\n");
    return 0;
}
/*
 * Release IO and memory resources used by the port.
 * This includes iounmap if necessary.
 */
static void	larm_release_port(struct uart_port *port){
    printk("larm_release_port\n");
}
/*
 * Request IO and memory resources used by the port.
 * This includes iomapping the port if necessary.
 */
static int larm_request_port(struct uart_port *port){
    printk("larm_request_port\n");
    return 0;
}
static void	larm_config_port(struct uart_port *port, int n){
    printk("larm_config_port\n");
}
static int larm_verify_port(struct uart_port *port, struct serial_struct *s){
    printk("larm_verify_port\n");
    return 0;
}
static int larm_ioctl(struct uart_port *port, unsigned int n, unsigned long m){
    printk("larm_ioctl\n");
    return 0;
}

static const struct uart_ops larm_uart_ops = {
	.tx_empty	= larm_tx_empty,
	.set_mctrl	= larm_set_mctrl,
	.get_mctrl	= larm_get_mctrl,
	.stop_tx	= larm_stop_tx,
	.start_tx	= larm_start_tx,
	.stop_rx	= larm_stop_rx,
	.break_ctl	= larm_break_ctl,
	.startup	= larm_startup,
	.shutdown	= larm_shutdown,
	.set_termios	= larm_set_termios,
	.type		= larm_type,
	.release_port	= larm_release_port,
	.request_port	= larm_request_port,
	.config_port	= larm_config_port,
	.verify_port	= larm_verify_port,
	.pm		= larm_pm,
};


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
	.nr		= LARM_NR_UARTS,
#ifdef CONFIG_SERIAL_LARM_CONSOLE
	.cons		= &larm_uart_console,
#endif
};

static int __init larm_uart_init(void) {
    printk("printk\n");
    printk("larm_uart_init\n");
    int ret;
    const int id = 0; 
    struct uart_port *port = &larm_port[id];

	ret = uart_register_driver(&larm_uart_driver);
    
    spin_lock_init(&port->lock);
	port->iotype	= UPIO_MEM;
	port->flags	= UPF_BOOT_AUTOCONF;
	port->ops	= &larm_uart_ops;
	port->irq	= 0;
	port->line = id;
#ifdef CONFIG_SERIAL_LARM_CONSOLE
    console_port = port;
#endif
    
    ret = uart_add_one_port(&larm_uart_driver, port);


    return ret;
}

static void __exit larm_uart_exit(void) {
    printk("larm_uart_exit\n");
}

module_init(larm_uart_init);
module_exit(larm_uart_exit);


