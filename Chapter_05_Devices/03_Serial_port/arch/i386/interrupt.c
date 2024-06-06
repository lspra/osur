/*! Interrupt handling - 'arch' layer (only basic operations) */

#define _ARCH_INTERRUPTS_C_
#include "interrupt.h"
#include <kernel/kprint.h>

#include <arch/processor.h>
#include <kernel/errno.h>
#include <lib/list.h>
#include <kernel/memory.h>

#define IRQ_NUM_SIM0 48
#define PRIO_SIM_MAX 9

/*! Interrupt controller device */
extern arch_ic_t IC_DEV;
static arch_ic_t *icdev = &IC_DEV;

/*! interrupt handlers */
static list_t ihandlers[INTERRUPTS+PRIO_SIM_MAX];
static list_t requests;
int irq_prio = 0, depth = 0;

struct ihndlr
{
	void *device;
	int (*ihandler)(unsigned int, void *device);

	list_h list;
};

struct ir_request
{
	struct ihndlr* handler;
	int processing;
	int priority;
	list_h list;
};

int cmp_requent(void* ir1, void* ir2) {
	struct ir_request *i1, *i2;
	if(ir1 == ir2)
		return 0;
	if(ir2 == NULL)
		return -1;
	i1 = (struct ir_request*) ir1;
	i2 = (struct ir_request*) ir2;
	return i2->priority - i1->priority;
}

void dodaj_zahtjeve(int irq_num) {
	struct ihndlr* handler = list_get(&ihandlers[irq_num], FIRST);
	struct ir_request* req;

	while (handler) {
		// kprintf("%d\n", handler);
		req = (struct ir_request*) kmalloc(sizeof(struct ir_request));
		ASSERT(req);
		req->handler = handler;
		req->processing = 0;
		//TODO ovaj priority mozda nije dobar
		req->priority = irq_num < IRQ_NUM_SIM0 ? 20 : irq_num - IRQ_NUM_SIM0;
		list_sort_add(&requests, req, &req->list, cmp_requent);
		if(handler->list.next)
			handler = handler->list.next->object;
		else
			break;
	}
}


/*! Initialize interrupt susubsystem (in 'arch' layer) */
void arch_init_interrupts()
{
	int i;

	icdev->init();

	for (i = 0; i < INTERRUPTS+PRIO_SIM_MAX; i++)
		list_init(&ihandlers[i]);
}

/*!
 * enable and disable interrupts generated outside processor, controller by
 * interrupt controller (PIC or APIC or ...)
 */
void arch_irq_enable(unsigned int irq)
{
	icdev->enable_irq(irq);
}
void arch_irq_disable(unsigned int irq)
{
	icdev->disable_irq(irq);
}

/*! Register handler function for particular interrupt number */
void arch_register_interrupt_handler(unsigned int inum, void *handler,
				       void *device)
{
	struct ihndlr *ih;

	if (inum < INTERRUPTS + PRIO_SIM_MAX)
	{
		ih = kmalloc(sizeof(struct ihndlr));
		ASSERT(ih);

		ih->device = device;
		ih->ihandler = handler;

		list_append(&ihandlers[inum], ih, &ih->list);
	}
	else {
		LOG(ERROR, "Interrupt %d can't be used!\n", inum);
		halt();
	}
}

/*! Unregister handler function for particular interrupt number */
void arch_unregister_interrupt_handler(unsigned int irq_num, void *handler,
					 void *device)
{
	struct ihndlr *ih, *next;

	ASSERT(irq_num >= 0 && irq_num < INTERRUPTS+PRIO_SIM_MAX);

	ih = list_get(&ihandlers[irq_num], FIRST);

	while (ih)
	{
		next = list_get_next(&ih->list);

		if (ih->ihandler == handler && ih->device == device)
			list_remove(&ihandlers[irq_num], FIRST, &ih->list);

		ih = next;
	}
}

/*!
 * "Forward" interrupt handling to registered handler
 * (called from interrupts.S)
 */
void arch_interrupt_handler(int irq_num)
{
	dodaj_zahtjeve(irq_num);
	struct ir_request *ih = list_get(&requests, FIRST);

	while(ih && !ih->processing && (depth < 3 || ih->priority > PRIO_SIM_MAX))
	{
		depth++;
		/* enable interrupts on PIC immediately since program may not
		 * return here immediately */

		list_remove(&requests, 0, &ih->list);
		ih->processing = TRUE;
		enable_interrupts();
		if (icdev->at_exit)
			icdev->at_exit(irq_num);
		ih->handler->ihandler(irq_num, ih->handler->device);
		disable_interrupts();
		depth--;
		if(irq_prio > 0) {
			dodaj_zahtjeve(IRQ_NUM_SIM0 + irq_prio);
			irq_prio = 0;
		}
		ih = list_get(&requests, FIRST);
	
	}

}
