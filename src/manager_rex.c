#include "manager.h"

int _nstart = 0;
int _nend = 0;

//--- local ------------
static void mgr_init_redis(manager_mr* mgr)
{
				redisContext* r = redisConnect("192.168.8.16", 6379);
				mgr->r = r;
}


static void mgr_cleardata(manager_mr* mgr)
{
	redisCommand(mgr->r, "FLUSHALL");
}

//--- public ------------


void mgr_cbuserstart(evutil_socket_t fd, short events, void* arg)
{
				cbcontext_mr* ctx = (cbcontext_mr*)arg;
				manager_mr* mgr = ctx->mgr;
				user* u = ctx->u;

				//printf("in start\n");

				//init bsonobj
				bson b[1];
				bson_init( b );
				bson_append_new_oid( b, "_id" );

				struct timeval tv;

				//printf("in cb_start, uid=%s\n", u->id);
				gettimeofday(&tv, NULL);
				bson_append_string( b, "id", u->id );
				bson_append_long( b, "starttime", tv.tv_sec);
				bson_finish( b );
				of_create(mgr, "user", b);
				//redisCommand(r, "SET user#%s.starttime %ld", u->id, tv.tv_sec);
				//redisCommand(r, "SADD user.id %s", u->id);

				if(_nstart==0)	{
								printf("s#%d\n", _nstart);
				}	else if(_nstart%10000==1)	{
								printf("s#%d\n", _nstart);
				}
				_nstart++;

}

void mgr_cbuserend(evutil_socket_t fd, short events, void* arg)
{
				cbcontext_mr* ctx = (cbcontext_mr*)arg;
				manager_mr* mgr = ctx->mgr;
				user* u = ctx->u;

				struct timeval tv;
				redisContext* r = mgr->r;
				mongo* m = mgr->m;

				bson b[1];
				void* reply;

				gettimeofday(&tv, NULL);
				//redisCommand(r, "SREM user.id %s", u->id);
				//reply = redisCommand(r, "GET user#%s.starttime", u->id);

				bson_init( b );
				//bson_append_new_oid( b, "_id" );
				bson_append_string( b, "id", u->id );
				bson_append_long( b, "starttime", 1);
				bson_finish( b );

				of_deleteAndLog(mgr, "user", b, 2);	//mmm: temp 2

				if(_nend==0)	{
								printf("e#%d\n", _nend);
				}	else if(_nend%10000==1)	{
								printf("e#%d\n", _nend);
				}
				_nend++;

}

manager_mr* mgr_init()
{
				char** attnames;
				char v1[10] = "id";
				char v2[10] = "starttime";
				int n = 2;
				attnames = (char**)malloc(n*sizeof(char*)); 
				attnames[0] = v1;
				attnames[1] = v2;


				manager_mr* mgr = (manager_mr*)malloc(sizeof(manager_mr));
				mgr_init_redis(mgr);
				//mr_init_mongo(mgr);

				mgr_cleardata(mgr);

				of_register(mgr, "user", attnames, 2);
				
				return mgr;
}


