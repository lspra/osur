/*! Program info */

#include <api/prog_info.h>
#include <arch/memory.h>

#include <api/pthread.h>
#include <api/malloc.h>

/* symbols from user.ld */
extern char user_code, user_end, user_heap, user_stack;

extern int PROG_START_FUNC(char *args[]);

module_program_t _program_module_header_
__attribute__((section(".program_header"))) =
{
	.proc = {
		.p = {
			.magic =	{ PMAGIC1, ~PMAGIC1, PMAGIC2, ~PMAGIC2 },
			.type = 	MS_PROGRAM,

			.start =	&user_code,
			.end =		&user_end,

			.name =		PROG_START_FUNC_NAME,

			.init =		prog_init,
			.entry =	PROG_START_FUNC,
			.param =	NULL,
			.exit =		pthread_exit,
			.prio =		THR_DEFAULT_PRIO,
		},
		.heap = &user_heap,
		.stack = &user_stack
	}
};

/* used in runtime */
process_t *_uproc_;

int stdio_init(); /* implemented in stdio.c */

/*! Initialize process environment */
void prog_init(void *args)
{
	_uproc_ = &_program_module_header_.proc;

	/* open stdin & stdout */
	stdio_init();

	/* initialize dynamic memory */
	_uproc_->mpool = mem_init(_uproc_->heap, _uproc_->p.heap_size);

	/* call starting function */
	((void (*)(void *)) _uproc_->p.entry)(args);

	pthread_exit(NULL);
}
