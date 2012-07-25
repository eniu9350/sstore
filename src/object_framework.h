#ifndef _SSTORE_OBJECT_FRAMEWORK_H_
#define _SSTORE_OBJECT_FRAMEWORK_H_

#include <bson.h>
#include "manager.h"

void of_register(manager_mr* mgr, char* classname, char** attnames, int nattnames);
void of_create(manager_mr* mgr, char* classname, bson* b);
//b -- only get id
void of_update(manager_mr* mgr, char* classname, bson* b, char* attname);
//b -- only get id, attnames
void of_delete(manager_mr* mgr, char* classname, bson* b);
//nattnames --- n of saved names
void of_deleteAndLog(manager_mr* mgr, char* classname, bson* b);

#endif
