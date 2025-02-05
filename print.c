/*
* 2012-5-31 PIONEER CORPORATION 
*
* Modify this file for ANDROID.
*
*/

#include "efence.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

#if defined(ANDROID)
#include <private/logd.h>
#include <unwind.h>


#define debug_log(format, ...)  \
    __libc_android_log_print(ANDROID_LOG_DEBUG, "EFence", (format), ##__VA_ARGS__ )
#define error_log(format, ...)  \
    __libc_android_log_print(ANDROID_LOG_ERROR, "EFence", (format), ##__VA_ARGS__ )
#define info_log(format, ...)  \
    __libc_android_log_print(ANDROID_LOG_INFO, "EFence", (format), ##__VA_ARGS__ )

#define debug_vlog(format, args)  \
    __libc_android_log_vprint(ANDROID_LOG_DEBUG, "EFence", (format), (args) )
#define error_vlog(format, args)  \
    __libc_android_log_vprint(ANDROID_LOG_ERROR, "EFence", (format), (args) )
#define info_vlog(format, args)  \
    __libc_android_log_vprint(ANDROID_LOG_INFO, "EFence", (format), (args) )


// =============================================================================
// stack trace functions
// Note: copied from bionic source code
// =============================================================================

typedef struct
{
    size_t count;
    intptr_t* addrs;
} stack_crawl_state_t;


/* depends how the system includes define this */
#ifdef HAVE_UNWIND_CONTEXT_STRUCT
typedef struct _Unwind_Context __unwind_context;
#else
typedef _Unwind_Context __unwind_context;
#endif

static _Unwind_Reason_Code trace_function(__unwind_context *context, void *arg)
{
    stack_crawl_state_t* state = (stack_crawl_state_t*)arg;
    if (state->count) {
        intptr_t ip = (intptr_t)_Unwind_GetIP(context);
        if (ip) {
            state->addrs[0] = ip;
            state->addrs++;
            state->count--;
            return _URC_NO_REASON;
        }
    }
    /*
     * If we run out of space to record the address or 0 has been seen, stop
     * unwinding the stack.
     */
    return _URC_END_OF_STACK;
}

static inline
int get_backtrace(intptr_t* addrs, size_t max_entries)
{
    stack_crawl_state_t state;
    state.count = max_entries;
    state.addrs = (intptr_t*)addrs;
    _Unwind_Backtrace(trace_function, (void*)&state);
    return max_entries - state.count;
}

static void dump_stack_trace()
{
    intptr_t addrs[20];
    int c = get_backtrace(addrs, 20);
    char buf[16];
    char tmp[16*20];
    int i;

    tmp[0] = 0; // Need to initialize tmp[0] for the first strcat
    for (i=0 ; i<c; i++) {
        snprintf(buf, sizeof buf, "%2d: %08x\n", i, addrs[i]);
        strlcat(tmp, buf, sizeof tmp);
    }
    __libc_android_log_print(ANDROID_LOG_ERROR, "EFence", "call stack:\n%s", tmp);

	/* Printk process's maps */
	sprintf(&tmp[0], "/system/bin/logwrapper /system/bin/toolbox cat /proc/%d/maps", getpid());
	system(tmp);
}
#endif	/* ANDROID */

/*
 * These routines do their printing without using stdio. Stdio can't
 * be used because it calls malloc(). Internal routines of a malloc()
 * debugger should not re-enter malloc(), so stdio is out.
 */

/*
 * NUMBER_BUFFER_SIZE is the longest character string that could be needed
 * to represent an unsigned integer, assuming we might print in base 2.
 */
#define	NUMBER_BUFFER_SIZE	(sizeof(ef_number) * NBBY)

static void
do_abort()
{
#if defined(ANDROID)
	dump_stack_trace();
#endif

	/*
	 * I use kill(getpid(), SIGILL) instead of abort() because some
	 * mis-guided implementations of abort() flush stdio, which can
	 * cause malloc() or free() to be called.
	 */
	*(int *)0 = 0;
	kill(getpid(), SIGILL);
	/* Just in case something handles SIGILL and returns, exit here. */
	_exit(-1);
}

static void
printNumber(ef_number number, ef_number base)
{
	char		buffer[NUMBER_BUFFER_SIZE];
	char *		s = &buffer[NUMBER_BUFFER_SIZE];
	int		size;
	
	do {
		ef_number	digit;

		if ( --s == buffer )
			EF_Abort("Internal error printing number.");

		digit = number % base;

		if ( digit < 10 )
			*s = '0' + digit;
		else
			*s = 'a' + digit - 10;

	} while ( (number /= base) > 0 );

	size = &buffer[NUMBER_BUFFER_SIZE] - s;

	if ( size > 0 )
		write(2, s, size);
}

void
EF_Printv(const char * pattern, va_list args)
{
#if defined(ANDROID)
	info_vlog(pattern, args);
#else
	static const char	bad_pattern[] =
	 "\nBad pattern specifier %%%c in EF_Print().\n";
	const char *	s = pattern;
	char		c;

	while ( (c = *s++) != '\0' ) {
		if ( c == '%' ) {
			c = *s++;
			switch ( c ) {
			case '%':
				(void) write(2, &c, 1);
				break;
			case 'a':
				/*
				 * Print an address passed as a void pointer.
				 * The type of ef_number must be set so that
				 * it is large enough to contain all of the
				 * bits of a void pointer.
				 */
				printNumber(
				 (ef_number)va_arg(args, void *)
				,0x10);
				break;
			case 's':
				{
					const char *	string;
					size_t		length;

					string = va_arg(args, char *);
					length = strlen(string);

					(void) write(2, string, length);
				}
				break;
			case 'd':
				{
					int	n = va_arg(args, int);

					if ( n < 0 ) {
						char	c = '-';
						write(2, &c, 1);
						n = -n;
					}
					printNumber(n, 10);
				}
				break;
			case 'x':
				printNumber(va_arg(args, u_int), 0x10);
				break;
			case 'c':
				{
					char	c = va_arg(args, char);
					
					(void) write(2, &c, 1);
				}
				break;
			default:
				{
					EF_Print(bad_pattern, c);
				}
		
			}
		}
		else
			(void) write(2, &c, 1);
	}
#endif
}

void
EF_Abortv(const char * pattern, va_list args)
{
	EF_Print("\nElectricFence Aborting: ");
	EF_Printv(pattern, args);
	EF_Print("\n");
	do_abort();
}

void
EF_Abort(const char * pattern, ...)
{
	va_list	args;

	va_start(args, pattern);
	EF_Abortv(pattern, args);
	/* Not reached: va_end(args); */
}

void
EF_Exitv(const char * pattern, va_list args)
{
	EF_Print("\nElectricFence Exiting: ");
	EF_Printv(pattern, args);
	EF_Print("\n");

#if defined(ANDROID)
	dump_stack_trace();
#endif

	/*
	 * I use _exit() because the regular exit() flushes stdio,
	 * which may cause malloc() or free() to be called.
	 */
	_exit(-1);
}

void
EF_Exit(const char * pattern, ...)
{
	va_list	args;

	va_start(args, pattern);

	EF_Exitv(pattern, args);

	/* Not reached: va_end(args); */
}

void
EF_Print(const char * pattern, ...)
{
	va_list	args;

	va_start(args, pattern);
	EF_Printv(pattern, args);
	va_end(args);
}

void
EF_InternalError(const char * pattern, ...)
{
	va_list	args;

	EF_Print("\nInternal error in allocator: ");
	va_start(args, pattern);
	EF_Printv(pattern, args);
	EF_Print("\n");
	va_end(args);
	do_abort();
}
