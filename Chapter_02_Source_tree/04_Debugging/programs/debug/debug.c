/*! Simple program prepared for little debugging */

#include <stdio.h>
#include <api/prog_info.h>
#include <api/errno.h>
#include <kernel/errno.h>

static int inc(int n)
{
	n++;

	return n;
}

int debug()
{
	int a, b, c;

	printf("Example program: [%s:%s]\n%s\n\n", __FILE__, __FUNCTION__,
		 debug_PROG_HELP);

	a = 1;

	b = a + 1;

	c = inc(a) + inc(b);

	a += b + c;
	b += a + c;
	c += a + b;

	printf("a=%d, b=%d, c=%d\n", a, b, c);
	extern char k_startup;
	printf("Address of 'startup' is %x\n", &k_startup);

#if 1	/* compile with 'debug=yes' and without */
	LOG(WARN, "This is log entry with WARN relevance");
	LOG(INFO, "Address of 'a' is %x", &a);
	LOG(INFO, "Address of 'debug' is %x", debug);

	ASSERT_ERRNO_AND_RETURN(TRUE, EINVAL);

	ASSERT(TRUE);
	//ASSERT(FALSE);
#endif
	return 0;
}
