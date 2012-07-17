#ifndef _SSTORE_INPUT_GENERATOR_H_
#define _SSTORE_INPUT_GENERATOR_H_

#include "user.h"

typedef struct duration	{
	int t; //lasting time
	double f; //frequency
	int fint;
}duration;

void generate_users(int total, user** users);

#endif
