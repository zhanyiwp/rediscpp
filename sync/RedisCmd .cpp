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

redisContext* RedisCtxGuard::GetCtx()
{
	pConn = _conn_pool->GetConn();
	if (pConn == nullptr)
	{
		return nullptr;
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
	redisContext* Ctx = nullptr;
	redisReply *reply = nullptr;
	// to do maxretry
	for(int i=0;i<2;i++)
	{
		Ctx= CtxGuard.GetCtx();
		if (nullptr == Ctx)
		{ 
			return nullptr;
		}
		va_list args;
		va_start(args, cmd);
		reply = static_cast<redisReply *>(redisvCommand(Ctx, cmd, args));
		va_end(args);
		if(reply)
		{	
			break;
		}
		else
		{
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
		}
	}
	return reply;
}

// to do 
int RedisCmd::CommandBool(bool &ret,const char* cmd, ...)
{
	RedisCtxGuard CtxGuard(&_conn_pool);
	redisContext* Ctx = nullptr;
	redisReply *reply = nullptr;
	// to do maxretry
	for(int i=0;i<2;i++)
	{
		Ctx= CtxGuard.GetCtx();
		if (nullptr == Ctx)
		{ 
			return -1;
		}
		va_list args;
		va_start(args, cmd);
		reply = static_cast<redisReply *>(redisvCommand(Ctx, cmd, args));
		va_end(args);
		if(reply)
		{	
			break;
		}
		else
		{
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
		}
	}
	ReplytoBool(reply,ret);
	return 0;
}

void RedisCmd::ReplytoBool(redisReply *reply,bool &ret)
{

}