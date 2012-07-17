#ifndef _SSTORE_OBJECT_FRAMEWORK_H_
#define _SSTORE_OBJECT_FRAMEWORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


void mapex_set(char* key, char** values, int n);
char** mapex_get(char* key, size_t* n);


#endif
