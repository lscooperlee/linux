
#include <mach/irqs.h>

		.macro  get_irqnr_preamble, base, tmp
		.endm

		.macro	get_irqnr_and_base, irqnr, irqstat, base, tmp
        ldr \base, =0xFF0F0000
        ldr \irqnr, [\base]
        mov \irqstat, \irqnr
        teq \irqstat, #0
		.endm
