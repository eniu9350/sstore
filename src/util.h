#ifndef _SSTORE_UTIL_H_
#define _SSTORE_UTIL_H_

#include <sys/time.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


extern lua_State* L;

int timeval_subtract (struct timeval* result, struct timeval* x, struct timeval* y);

void sstore_lua_init();

#endif
