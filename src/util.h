#ifndef _SSTORE_UTIL_H_
#define _SSTORE_UTIL_H_

#include <sys/time.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


extern lua_State* L;

//Push, check and get (assume g variable of lua state is declared as "L");
//remember to pop it to gurantee repetitive use of this micro.

#define LUA_PCG_STRING(k, v)  \
	lua_getglobal(L, k);  \
if(!lua_isstring(L, -1))  { \
	printf("%s not string\n", k); \
} \
else  { \
	v = lua_tostring(L, -1);  \
}

#define LUA_PCG_INT(k, v) \
	lua_getglobal(L, k);  \
if(!lua_isnumber(L, -1))  { \
	printf("%s not number\n", k); \
} \
else  { \
	v = (int)lua_tonumber(L, -1); \
}


int timeval_subtract (struct timeval* result, struct timeval* x, struct timeval* y);

void sstore_lua_init();

#endif
