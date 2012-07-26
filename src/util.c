#include "util.h"

#include <stdlib.h>

static void *l_alloc (void *ud, void *ptr, size_t osize,
								size_t nsize) {
				(void)ud;  (void)osize;  /* not used */
				if (nsize == 0) {
								free(ptr);
								return NULL;
				}
				else
								return realloc(ptr, nsize);
}



int timeval_subtract (struct timeval* result, struct timeval* x, struct timeval* y)
{
				/* Perform the carry for the later subtraction by updating y. */
				if (x->tv_usec < y->tv_usec) {
								int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
								y->tv_usec -= 1000000 * nsec;
								y->tv_sec += nsec;
				}
				if (x->tv_usec - y->tv_usec > 1000000) {
								int nsec = (x->tv_usec - y->tv_usec) / 1000000;
								y->tv_usec += 1000000 * nsec;
								y->tv_sec -= nsec;
				}

				/* Compute the time remaining to wait.
					 tv_usec is certainly positive. */
				result->tv_sec = x->tv_sec - y->tv_sec;
				result->tv_usec = x->tv_usec - y->tv_usec;

				/* Return 1 if result is negative. */
				return x->tv_sec < y->tv_sec;
}

void sstore_lua_init()
{
				L = lua_newstate(l_alloc, NULL);
				luaopen_base(L);
				luaopen_io(L);
				luaopen_string(L);
				luaopen_math(L);

				if (luaL_loadfile(L, "conf/sstore.conf") || lua_pcall(L, 0, 0, 0)) {
					error(L, "cannot run configuration file: %s",
							lua_tostring(L, -1));
				}


}
