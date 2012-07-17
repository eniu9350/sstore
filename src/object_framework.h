#ifndef _SSTORE_OBJECT_FRAMEWORK_H_
#define _SSTORE_OBJECT_FRAMEWORK_H_

#include <bson.h>
#include "manager_redis_mongo.h"

void mrof_register(manager_mr* mgr, char* classname, char** attnames, int nattnames);
void mrof_create(manager_mr* mgr, char* classname, bson* b);
//b -- only get id
void mrof_update(manager_mr* mgr, char* classname, bson* b, char* attname);
//b -- only get id, attnames
void mrof_delete(manager_mr* mgr, char* classname, bson* b);
//nattnames --- n of saved names
void mrof_deleteAndLog(manager_mr* mgr, char* classname, bson* b);

#endif
