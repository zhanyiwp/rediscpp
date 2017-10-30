#include "RedisCmd.h"

RedisCmd::RedisCmd(RedisOpt &Opt)
:_conn_pool(Opt)
{

}

RedisCmd::~RedisCmd()
{

}

redisReply *RedisCmd::Command(const char* cmd, ...)
{
	std::shared_ptr<RedisConn > pConn = _conn_pool.GetConn();
	if (pConn == nullptr)
	{
		return NULL;
	}
	va_list args;
	va_start(args, cmd);
	redisReply *reply = static_cast<redisReply *>(redisvCommand(pConn->GetRedisCtx(), cmd, args));
	va_end(args);
	_conn_pool.FreeConn(pConn);
	return reply;
}