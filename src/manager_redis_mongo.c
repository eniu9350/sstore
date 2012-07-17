#include "manager_redis_mongo.h"

int _nstart = 0;
int _nend = 0;

void mr_userstart(manager_mr* mgr, user* u)
{
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
				mrof_create(mgr, "user", b);
				//redisCommand(r, "SET user#%s.starttime %ld", u->id, tv.tv_sec);
				//redisCommand(r, "SADD user.id %s", u->id);

				if(_nstart==0)	{
								printf("s#%d\n", _nstart);
				}	else if(_nstart%10000==1)	{
								printf("s#%d\n", _nstart);
				}
				_nstart++;

}

void mr_userend(manager_mr* mgr, user* u)
{

				struct timeval tv;
				redisContext* r = mgr->r;
				mongo* m = mgr->m;

				bson b[1];
				void* reply;

				gettimeofday(&tv, NULL);
				redisCommand(r, "SREM user.id %s", u->id);
				reply = redisCommand(r, "GET user#%s.starttime", u->id);

				bson_init( b );
				//bson_append_new_oid( b, "_id" );
				bson_append_string( b, "id", u->id );
				bson_append_long( b, "starttime", 1);
				bson_finish( b );

				mrof_deleteAndLog(mgr, "user", b, 2);	//mmm: temp 2

				if(_nend==0)	{
								printf("e#%d\n", _nend);
				}	else if(_nend%10000==1)	{
								printf("e#%d\n", _nend);
				}
				_nend++;

}

static int mr_init_mongo(manager_mr* mgr)
{
				int status;
				mongo* conn = mgr->m;
				status = mongo_connect( conn, "192.168.8.16", 27017 );

				if( status != MONGO_OK ) {
								switch ( conn->err ) {
												case MONGO_CONN_SUCCESS:    printf( "connection succeeded\n" ); break;
												case MONGO_CONN_NO_SOCKET:  printf( "no socket\n" ); return 1;
												case MONGO_CONN_FAIL:       printf( "connection failed\n" ); return 1;
												case MONGO_CONN_NOT_MASTER: printf( "not master\n" ); return 1;
								}
				}
}


static void mr_init_redis(manager_mr* mgr)
{
				redisContext* r = redisConnect("192.168.8.16", 6379);
				mgr->r = r;
}

manager_mr* mr_init()
{
				manager_mr* mgr = (manager_mr*)malloc(sizeof(manager_mr));
				mr_init_redis(mgr);
				mr_init_mongo(mgr);
				return mgr;
}
