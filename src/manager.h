#ifndef _SSTORE_MANAGER_REDIS_MONGO_H_
#define _SSTORE_MANAGER_REDIS_MONGO_H_

#include "user.h"
#include "hiredis.h"
#include <mongo.h>

#include <event2/event-config.h>
#include <event2/event.h>
#include <event2/util.h>


/* application specific manager */

typedef struct _manager_mr	{
	redisContext* r;
	mongo m[1];
}manager_mr;


typedef struct _cbcontext_mr	{
	manager_mr* mgr;
	user* u;
}cbcontext_mr;


void mgr_cbuserstart(evutil_socket_t fd, short events, void* arg);
void mgr_cbuserend(evutil_socket_t fd, short events, void* arg);
manager_mr* mgr_init();




#endif
