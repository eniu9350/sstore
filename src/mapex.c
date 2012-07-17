#include "mapex.h"

extern lua_State* L;

void mapex_set(char* key, char** values, int n)
{
				int i;

				//check if exist
				lua_getglobal(L, key);
				if(lua_isnil(L, -1))	{
								lua_pop(L,1);	//mmm: right?
								//init table
								lua_newtable(L);
								lua_setglobal(L, key);	//mmm: prefix?
								lua_getglobal(L, key);
								printf("table is nil, creating..\n");
				}

				for(i=0;i<n;i++)	{
								lua_pushinteger(L, i+1);
								lua_pushstring(L, values[i]);
								lua_settable(L,-3);
				}
				lua_pop(L,1);
}

char** mapex_get(char* key, size_t* n)
{
				int i;
				char** values;
				//check if exist
				lua_getglobal(L, key);
				if(lua_isnil(L, -1))	{
								lua_pop(L,1);	//mmm: right?
								printf("table is nil, return (key=%s)\n", key);
								return NULL;
				}

				*n = lua_rawlen(L, -1);	//mmm: may be wrong with removing op
				//printf("table len=%d\n", *n);
				values = (char**)malloc((*n)*sizeof(char*));	

				for(i=0;i<*n;i++)	{
								lua_pushinteger(L, i+1);
								lua_gettable(L, -2);
								values[i] = lua_tostring(L, -1);
								lua_pop(L, 1);
				}

				//pop the table
				lua_pop(L, 1);
				return values;
}
