#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mongo.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

lua_State* L;

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
				bson b[1];

				bson_iterator i[1];
				bson_type type;
				char* id;
				char* key;

				bson_init( b );
				bson_append_new_oid( b, "_id" );

				//type = bson_find( i, b, "id" );
				//id = bson_iterator_string(i);

				//add id to idset of the class
				//redisCommand(mgr->r, "SADD %s.id %s", classname, id); 

				//iterate through members
				bson_iterator_init(i, b);

				do	{
								type = bson_iterator_next(i);
								key = bson_iterator_key(i);

								switch(type)	{
												case BSON_STRING:
																printf("bson type BSON_STRING\n");
																break;
												case BSON_LONG:
																printf("bson type BSON_LONG\n");
																break;
												case BSON_OID:
																printf("bson type BSON_OID\n");
																break;
												default:
																printf("unknown bson type in mrof_create!(type=%d, name=%s)\n", type, key);
																break;
								}
				}while(type!=NULL);

				return 0;
}


int main_()
{

				/*
					 struct event_base* base;
					 struct event* ev;

					 base = event_base_new();
					 ev = event_new(base, 0, EV_ET, test_cb, 0);
				 */

				int status;
				mongo conn[1];
				status = mongo_connect( conn, "192.168.8.16", 27017 );
				bson b[1];

				L = lua_newstate(l_alloc, NULL);
				luaopen_base(L);
				luaopen_io(L);
				luaopen_string(L);
				luaopen_math(L);


				if( status != MONGO_OK ) {
								switch ( conn->err ) {
												case MONGO_CONN_SUCCESS:    printf( "connection succeeded\n" ); break;
												case MONGO_CONN_NO_SOCKET:  printf( "no socket\n" ); return 1;
												case MONGO_CONN_FAIL:       printf( "connection failed\n" ); return 1;
												case MONGO_CONN_NOT_MASTER: printf( "not master\n" ); return 1;
								}
				}


				bson_init( b );
				bson_append_new_oid( b, "_id" );
				bson_append_string( b, "name", "Joe" );
				bson_append_int( b, "age", 33 );
				bson_finish( b );

				mongo_insert( conn, "tutorial.people", b , NULL);

				bson_destroy( b );

				mongo_destroy( conn );
}
