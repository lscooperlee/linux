#define CONFIG_DEBUG_UART_PHYS  0xFF000000
#define CONFIG_DEBUG_UART_VIRT  0xFF000000

.macro	addruart, rp, rv, tmp
ldr	\rp, =CONFIG_DEBUG_UART_PHYS
ldr	\rv, =CONFIG_DEBUG_UART_VIRT
.endm

.macro	senduart,rd,rx
strb	\rd, [\rx, #0]
.endm

.macro	busyuart,rd,rx
.endm

.macro	waituartcts,rd,rx
.endm

.macro	waituarttxrdy,rd,rx
.endm
