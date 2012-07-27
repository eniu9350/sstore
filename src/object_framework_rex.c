#include "object_framework.h"

#include <stdio.h>
#include <string.h>

#include "mapex.h"



void of_register(manager_mr* mgr, char* classname, char** attnames, int nattnames)
{

	redisContext* r = mgr->r;
	
	//config saving options
	//redisCommand(r, "OFREGISTER user starttime endtime | updatetime");
	redisCommand(r, "OFREGISTER user id starttime |");
}

void of_create(manager_mr* mgr, char* classname, bson* b)
{
				//get id
				char* id;

				const char* key;
				char cmd[255] = "OFCREATE ";

				bson_iterator i[1];
				bson_type type;
				type = bson_find( i, b, "id" );
				id = bson_iterator_string(i);

				//redisCommand("OFCREATE user %s starttime=666 endtime=777 updatetime=701",id, );

				strcat(cmd, classname);
				strcat(cmd, " ");
				strcat(cmd, id);
				
				//iterate through members
				bson_iterator_init(i, b);

				do	{
								type = bson_iterator_next(i);
								key = bson_iterator_key(i);

								//mmm: assume all string or long

								switch(type)	{
												case BSON_STRING:
																//redisCommand(mgr->r, "SET %s#%s.%s %s", classname, id, key, bson_iterator_string(i));
																strcat(cmd, " ");
																strcat(cmd, key);
																strcat(cmd, "=");
																strcat(cmd, bson_iterator_string(i));

																break;
												case BSON_LONG:
																//redisCommand(mgr->r, "SET %s#%s.%s %ld", classname, id, key, bson_iterator_long(i));
																sprintf(cmd, "%s %s=%ld", cmd, key,  bson_iterator_long(i));
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

				redisCommand(mgr->r, cmd);
				//printf("cmd--------->%s\n", cmd);
}

ofvalue* of_get(manager_mr* mgr, char* classname, char* id, char* attname)
{
							ofvalue* v = NULL;
							redisReply* reply;
							reply = (redisReply*)redisCommand(mgr->r, "GET %s#%s.%s", classname, id, attname);
							//printf("persist value name %s\n", values[i]);
							if(reply!=NULL) {
											switch(reply->type) {
															case REDIS_REPLY_STRING:
v = ofvalue_createString(reply->str);
																			//bson_append_string( bnew, values[i], reply->str);
																			//printf("reply is string --- %s\n", reply->str);
																			break;
															case REDIS_REPLY_INTEGER:
																			//bson_append_long( bnew, values[i], reply->integer);
v = ofvalue_createString(reply->integer);																			
																			//printf("reply is long --- %ld\n", reply->integer);
																			break;
															default:
																			printf("unrecogonized type of response in of_get\n");
																			break;
											}
							}else {
											printf("reply null in of_get\n");
							}

	return v;
	
}


void of_update(manager_mr* mgr, char* classname, bson* b, char* attname)
{
				//not implemented yet
				printf("not impl yet!!!\n");
			
}


void of_delete(manager_mr* mgr, char* classname, bson* b)
{
				//not implemented yet
				printf("not impl yet!!!\n");

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

				//remove id from idset of the class
				redisCommand(mgr->r, "OFDELSAVE %s %s", classname, id); 

				//printf("cmd--------->OFDELSAVE %s %s\n",  classname, id);
				

}

