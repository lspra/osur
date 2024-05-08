/*! Timer in arch layer; use 'arch_timer_t' device defined in configuration */

#include "time.h"

#include <types/time.h>

extern arch_timer_t TIMER;
static arch_timer_t *timer = &TIMER;
static long HZ;

void arch_enable_timer_interrupt()	{ timer->enable_interrupt();	}
void arch_disable_timer_interrupt()	{ timer->disable_interrupt();	}

void arch_get_min_interval(timespec_t *time)
{
	*time = timer->min_interval;
}

void arch_get_max_interval(timespec_t *time)
{
	*time = timer->max_interval;
}

void arch_set_hz(long hz) {
	HZ = hz;
	timer->max_interval.tv_nsec = 1000000000L / HZ;
	timer->max_interval.tv_sec = 0;
}

/*! Initialize timer 'arch' subsystem: timer device, subsystem data */
void arch_timer_init(void *kernel_timer_handler)
{
	timer->init();
	arch_set_hz(1000);
	timespec_t period = timer->max_interval;
	timer->set_interval(&period);
	timer->register_interrupt(kernel_timer_handler);
	timer->enable_interrupt();

	return;
}

/*!
 * Set next timer activation
 * \param period Time of next activation
 */
void arch_timer_set(timespec_t period)
{
	timer->set_interval(&period);
}

/*!
 * Get remaining time in timer
 * \param time Store address
 */
void arch_timer_remainder(timespec_t *time)
{
	timer->get_interval_remainder(time);
}