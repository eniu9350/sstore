#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "hiredis.h"
#include "input_generator.h"
#include "user.h"
#include "manager_redis_mongo.h"

#include <event2/event-config.h>
#include <event2/event.h>
#include <event2/util.h>

#include "util.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


#include "manager_redis_mongo.h"

void cb_end(evutil_socket_t fd, short events, void* arg)
{
				cbcontext_mr* ctx = (cbcontext_mr*)arg;
				mr_userend(ctx->mgr, ctx->u);
}


void cb_start(evutil_socket_t fd, short events, void* arg)
{
				cbcontext_mr* ctx = (cbcontext_mr*)arg;
				mr_userstart(ctx->mgr, ctx->u);
}

lua_State* L;

int main()
{
				manager_mr* mgr;
				cbcontext_mr* ctx;

				struct event_base* base;
				int nuser;

				int i;
				struct timeval* tvperiod;
				struct timeval* tvnow;
				struct timeval* tvthen;
				struct timeval* tvstart;
				struct event* e;
				user** users;
				user* u;

				char** attnames;
				char v1[10] = "id";
				char v2[10] = "starttime";
				int n = 2;
				attnames = (char**)malloc(n*sizeof(char*));	
				attnames[0] = v1;
				attnames[1] = v2;

				//init lua environment
				sstore_lua_init();

				//init db
				mgr = mr_init();
				//clear data
				mr_cleardata(mgr);

				base = event_base_new();

				//nuser = 5000*1000;
				nuser = 200000;

				mrof_register(mgr, "user", attnames, 2);

				//mmm: prepair user	
				users = (user**)malloc(nuser*sizeof(user*));
				generate_users(nuser, users);

				//mmm: prepair tvstart
				tvstart = (struct timeval*)malloc(sizeof(struct timeval));
				gettimeofday(tvstart, NULL);
				tvstart->tv_sec = tvstart->tv_sec + 5; 

				for(i=0;i<nuser;i++)	{
								u = users[i];
								//printf("u[i].id=%s\n", u->id);

								tvthen = (struct timeval*)malloc(sizeof(struct timeval));

								//1. add start event
								//printf("u->a=%d, tvstart->tvsec=%ld\n", u->a, tvstart->tv_sec);
								tvthen->tv_sec = tvstart->tv_sec + u->a;
								tvthen->tv_usec = tvstart->tv_usec;

								tvnow = (struct timeval*)malloc(sizeof(struct timeval));
								gettimeofday(tvnow, NULL);

								tvperiod = (struct timeval*)malloc(sizeof(struct timeval));
								//printf("tvnow s=%d\n", tvnow->tv_sec);
								//printf("tvthen s=%d\n", tvthen->tv_sec);
								timeval_subtract(tvperiod, tvthen, tvnow);	

								ctx = (cbcontext_mr*)malloc(sizeof(cbcontext_mr));
								ctx->mgr = mgr;
								ctx->u = u;

								e = evtimer_new(base, cb_start, (void*)ctx);
								//printf("tvperiod s=%d\n", tvperiod->tv_sec);
								evtimer_add(e, tvperiod);	

								//2. add end event
								tvthen->tv_sec = tvstart->tv_sec + u->a + u->d;
								tvthen->tv_usec = tvstart->tv_usec;

								tvnow = (struct timeval*)malloc(sizeof(struct timeval));
								gettimeofday(tvnow, NULL);

								tvperiod = (struct timeval*)malloc(sizeof(struct timeval));
								timeval_subtract(tvperiod, tvthen, tvnow);	

								ctx = (cbcontext_mr*)malloc(sizeof(cbcontext_mr));
								ctx->mgr = mgr;
								ctx->u = u;

								e = evtimer_new(base, cb_end, (void*)ctx);
								evtimer_add(e, tvperiod);	
				}
				printf("user preparation ended\n");

				event_base_dispatch(base);	

				//run loop
				printf("aaa\n");
}
