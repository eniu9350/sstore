#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

lua_State* L;

static void mapex_set(char* key, char** values, int n);
static char** mapex_get(char* key);

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


int main()
{
				char** values;
				char** results;
				int n;
				int i;
				char v1[10] = "aws";
				char v2[10] = "gae";
				char v3[10] = "shanda";

				L = lua_newstate(l_alloc, NULL);
				luaopen_base(L);
				luaopen_io(L);
				luaopen_string(L);
				luaopen_math(L);

				n = 3;
				values = (char**)malloc(n*sizeof(char*));	
				values[0] = v1;
				values[1] = v2;
				values[2] = v3;

				mapex_set("services", values, 3);
				results = mapex_get("services");
				for(i=0;i<n;i++)	{
								printf("result[%d]: %s\n", i, results[i]);
				}
}
int main_()
{

				/*
					 struct event_base* base;
					 struct event* ev;

					 base = event_base_new();
					 ev = event_new(base, 0, EV_ET, test_cb, 0);
				 */

				L = lua_newstate(l_alloc, NULL);
				luaopen_base(L);
				luaopen_io(L);
				luaopen_string(L);
				luaopen_math(L);

				lua_pushstring(L, "001");
				lua_setglobal(L, "users");

				lua_pop(L,1);

				lua_getglobal(L, "users");
				printf("result=>%s \n", (char*)lua_tostring(L, -1));

				//wrap several methods representing ops of type Map<k, List<v>>


}
/*
	 static void mapex_init(char* tname)
	 {
	 lua_newtable(L);
	 lua_setglobal(L, tname);
	 lua_pop(L,1);
	 }
 */

static void mapex_set(char* key, char** values, int n)
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

static char** mapex_get(char* key, size_t* n)
{
				int i;
				char** values;
				//check if exist
				lua_getglobal(L, key);
				if(lua_isnil(L, -1))	{
								lua_pop(L,1);	//mmm: right?
								printf("table is nil, return\n");
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

void _register(char* classname, char** attnames, int n)
{
}
