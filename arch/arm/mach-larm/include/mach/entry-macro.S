
#include <mach/irqs.h>

		.macro  get_irqnr_preamble, base, tmp
		.endm

		.macro	get_irqnr_and_base, irqnr, irqstat, base, tmp
        ldr \base, =0xFF0F0000
        ldr \irqnr, [\base]

        tst \irqnr, #0x1
        movne \irqnr, #0x1
        bne  9527f

        tst \irqnr, #0x2
        movne \irqnr, #0x2
        bne  9527f

        mov \irqnr, #0

9527:
        mov \irqstat, \irqnr
        teq \irqstat, #0
		.endm
