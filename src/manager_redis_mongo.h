#ifndef _SSTORE_MANAGER_REDIS_MONGO_H_
#define _SSTORE_MANAGER_REDIS_MONGO_H_

#include "user.h"
#include "hiredis.h"
#include <mongo.h>

typedef struct _manager_mr	{
	redisContext* r;
	mongo m[1];
}manager_mr;


typedef struct _cbcontext_mr	{
	manager_mr* mgr;
	user* u;
}cbcontext_mr;

void mr_userstart(manager_mr* mgr, user* u);
void mr_userend(manager_mr* mgr, user* u);
manager_mr* mr_init();

#endif
