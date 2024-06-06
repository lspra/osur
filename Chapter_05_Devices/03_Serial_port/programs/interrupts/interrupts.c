
/*! Testing interrupts by priority */

#include <stdio.h>
#include <time.h>
#include <api/prog_info.h>
#include <arch/interrupt.h>

void prekid(unsigned int irq_num, void *device)
{
	int prio = irq_num - SOFT_IRQ, i;
	timespec_t t;

	t.tv_sec = 1;
	t.tv_nsec = 0;

	printf("Pocetak obrade prekida prioriteta %d\n", prio);
	for (i = 0; i < 10; i++) {
		printf("Obrada prioriteta %d %d/10\n", prio, i+1);
		clock_nanosleep(CLOCK_REALTIME, 0, &t, NULL);
	}
	printf("Kraj obrade prekida prioriteta %d\n", prio);
}

int interrupts()
{
	printf("Example program: [%s:%s]\n%s\n\n", __FILE__, __FUNCTION__,
		 "interrupts_PROG_HELP");

	int i;

	for (i = 1; i < 10; i++)
		arch_register_interrupt_handler(SOFT_IRQ + i, prekid, NULL);
	return 0;
}