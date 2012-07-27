#include "object_framework.h"

#include <stdio.h>
#include <string.h>

#include "mapex.h"


void of_register(manager_mr* mgr, char* classname, char** attnames, int nattnames)
{
	//1. store class att names at redis
	redisContext* r = mgr->r;
	char atts[512] = "";	//mmm
	char key[512] = "";
	int i;
	for(i=0;i<nattnames;i++)	{
		strcat(atts, " ");
		strcat(atts, attnames[i]);
	}
	
	redisCommand(r, "SADD class#%s.att%s", classname, atts); 

	//2. cache att names at client	(or get this info from redis)
	sprintf(key, "class#%s", classname);
	mapex_set(key, attnames, nattnames);
}

void of_create(manager_mr* mgr, char* classname, bson* b)
{
				//get id
				char* id;

				const char* key;

				bson_iterator i[1];
				bson_type type;
				type = bson_find( i, b, "id" );
				id = bson_iterator_string(i);

				//add id to idset of the class
				redisCommand(mgr->r, "SADD %s.id %s", classname, id); 

				//iterate through members
				bson_iterator_init(i, b);

				do	{
								type = bson_iterator_next(i);
								key = bson_iterator_key(i);

								switch(type)	{
												case BSON_STRING:
																redisCommand(mgr->r, "SET %s#%s.%s %s", classname, id, key, bson_iterator_string(i));
																break;
												case BSON_LONG:
																redisCommand(mgr->r, "SET %s#%s.%s %ld", classname, id, key, bson_iterator_long(i));
																break;
												case BSON_OID:
																//mmm:
																break;
												case BSON_EOO:
																//mmm:
																break;
												default:
																printf("unknown bson type in mrof_create!(type=%d, name=%s)\n", type, key);
																break;
								}
				}while(type!=BSON_EOO);	//mmm: right?
}

ofvalue* of_get(manager_mr* mgr, char* classname, char* id, char* attname)
{
	return NULL;
}


void of_update(manager_mr* mgr, char* classname, bson* b, char* attname)
{
				//get id
				bson_iterator i[1];
				bson_type type;
				char* id;
				type = bson_find( i, b, "id" );
				id = bson_iterator_string(i);

				//get value and update
				type = bson_find( i, b, attname );
				switch(type)	{
								case BSON_STRING:
												redisCommand(mgr->r, "SET %s#%s.%s %s", classname, id, attname, bson_iterator_string(i));
												break;
								case BSON_LONG:
												redisCommand(mgr->r, "SET %s#%s.%s %ld", classname, id, attname, bson_iterator_long(i));
												break;
								default:
												printf("unknown bson type in mrof_create!\n");
												break;
				}
}


void of_delete(manager_mr* mgr, char* classname, bson* b)
{
				//get id
				bson_iterator i[1];
				bson_type type;
				char* id;
				const char* key;
				type = bson_find( i, b, "id" );
				id = bson_iterator_string(i);

				//remove id from idset of the class
				redisCommand(mgr->r, "SREM %s.id %s", classname, id); 

				//iterate through members
				bson_iterator_init(i, b);
				do	{
								type = bson_iterator_next(i);
								key = bson_iterator_key(i);

								redisCommand(mgr->r, "DEL %s#%s.%s", classname, id, key);
				}while(type!=NULL);	//mmm: right?
}


void of_deleteAndLog(manager_mr* mgr, char* classname, bson* b)
{
				char **values;
				int i;
				//get id
				//bson_iterator i[1];
				bson_iterator it[1];
				bson bnew[1];
				const char* key;
				bson_type type;
				char* id;
				char tkey[100];
				redisReply* reply; 
				int nattnames = 0;
				type = bson_find( it, b, "id" );
				id = bson_iterator_string(it);

				//mrof_delete(mgr, classname, b);

				//init bson obj
				bson_init( bnew );
				bson_append_new_oid( bnew, "_id" );
				//bson_append_string( bnew, "id", id );
				//bson_finish( bnew );

				//persist values to mongodb
				sprintf(tkey, "class#%s", classname);
				values = mapex_get(tkey, &nattnames);	//mmm:from cache, not redis!
				//printf("value.len=%d\n", nattnames);
				for(i=0;i<nattnames;i++)	{
								reply = (redisReply*)redisCommand(mgr->r, "GET %s#%s.%s", classname, id, values[i]);
								//printf("persist value name %s\n", values[i]);
								if(reply!=NULL)	{
												switch(reply->type)	{
																case REDIS_REPLY_STRING:
																				bson_append_string( bnew, values[i], reply->str);
																				//printf("reply is string --- %s\n", reply->str);
																				break;
																case REDIS_REPLY_INTEGER:
																				bson_append_long( bnew, values[i], reply->integer);
																				//printf("reply is long --- %ld\n", reply->integer);
																				break;
																default:
																				//printf("unrecogonized type of response in mrof_deleteAndLog\n");
																				break;
												}
								}else	{
												printf("reply null in mrof_deleteAndLog\n");
								}
				}
				bson_finish( bnew );
				mongo_insert(mgr->m, "sstore.users", bnew, NULL);	//
				bson_destroy(bnew);

				//remove id from idset of the class
				redisCommand(mgr->r, "SREM %s.id %s", classname, id); 

				//iterate through members
				bson_iterator_init(it, b);
				do	{
								type = bson_iterator_next(it);
								key = bson_iterator_key(it);
								if(type!=BSON_EOO && type!=BSON_OID)	{
												redisCommand(mgr->r, "DEL %s#%s.%s", classname, id, key);
								}
				}while(type!=BSON_EOO);	//mmm: right?

}
