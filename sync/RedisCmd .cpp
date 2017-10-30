#include "RedisCmd.h"

RedisCtxGuard::RedisCtxGuard(RedisConnPool *conn_pool)
:_conn_pool(conn_pool)
{

}

RedisCtxGuard::~RedisCtxGuard()
{
	if (_conn_pool)
	{
		_conn_pool->FreeConn(pConn);
	}
}

redisContext* RedisCtxGuard::Get()
{
	pConn = _conn_pool->GetConn();
	if (pConn == nullptr)
	{
		return NULL;
	}
	return pConn->GetRedisCtx();
}

RedisCmd::RedisCmd(RedisOpt &Opt)
:_conn_pool(Opt)
{

}

RedisCmd::~RedisCmd()
{

}

redisReply *RedisCmd::Command(const char* cmd, ...)
{
	RedisCtxGuard CtxGuard(&_conn_pool);
	redisContext* Ctx = CtxGuard.Get();
	if (NULL == Ctx)
	{
		return NULL;
	}
	va_list args;
	va_start(args, cmd);
	redisReply *reply = static_cast<redisReply *>(redisvCommand(Ctx, cmd, args));
	va_end(args);
	return reply;
}