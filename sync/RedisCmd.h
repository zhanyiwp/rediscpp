#include "RedisConnPool.h"

#pragma once

using namespace std;

class RedisCtxGuard
{
public:
	explicit RedisCtxGuard(RedisConnPool *conn_pool);
	~RedisCtxGuard();
	RedisCtxGuard(const RedisCtxGuard &) = delete;
	RedisCtxGuard & operator = (const RedisCtxGuard &) = delete;
	redisContext* Get();
private:
	RedisConnPool *_conn_pool;
	std::shared_ptr<RedisConn > pConn;
};

class RedisCmd
{
public:
	RedisCmd(RedisOpt &Opt);
	~RedisCmd();

	redisReply *Command(const char* cmd, ...);

private:
	RedisConnPool _conn_pool;
};