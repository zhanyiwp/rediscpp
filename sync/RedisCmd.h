#include "RedisConnPool.h"

#pragma once

using namespace std;

class RedisCmd
{
public:
	RedisCmd(RedisOpt &Opt);
	~RedisCmd();

	redisReply *Command(const char* cmd, ...);

private:
	RedisConnPool _conn_pool;
};