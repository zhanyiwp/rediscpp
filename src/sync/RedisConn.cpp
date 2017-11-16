#include "RedisConn.h"
#include <time.h>

RedisOpt::RedisOpt()
{

}

RedisOpt::RedisOpt(string Host, unsigned int Port, string Password, unsigned int Timeout, unsigned int PoolSize)
:_host(Host)
, _port(Port)
, _password(Password)
, _timeout(Timeout)
, _pool_size(PoolSize)
{

}

RedisConn::RedisConn(RedisOpt &Opt)
:_ctx(NULL)
,_host(Opt._host)
, _port(Opt._port)
, _password(Opt._password)
, _status(CS_UNCONNECTED)
, _last_active_time(0)
{
	_timeout.tv_sec = Opt._timeout / 1000;
	_timeout.tv_usec = (Opt._timeout % 1000) * 1000;
}

RedisConn::~RedisConn()
{
	FreeCtx();
}

int RedisConn::Connect()
{
	int Ret = -1;
	FreeCtx();
	_ctx = redisConnectWithTimeout(_host.c_str(), _port, _timeout);
	if (nullptr == _ctx || _ctx->err)
	{
		FreeCtx();
		return Ret;
	}
	_status = CS_CONNECTED;
	redisSetTimeout(_ctx, _timeout);
	Ret = Auth();
	return Ret;
}


int RedisConn::Auth()
{
	int Ret = -1;
	if (0 == _password.length()) 
	{
		Ret = 0;
	}
	else 
	{
		redisReply *Reply = static_cast<redisReply *>(redisCommand(_ctx, "auth %s", _password.c_str()));
		if ((nullptr == Reply) || (strcasecmp(Reply->str, "OK") != 0))
		{
			Ret = -1;
		}
		else
		{
			Ret = 0;
			_status = CS_AUTHENTICATION;
		}
		if (Reply)
		{
			freeReplyObject(Reply);
			Reply = nullptr;
		}
	}
	return Ret;
}

int RedisConn::Close()
{
	FreeCtx();
	_status = CS_UNCONNECTED;
	return 0;
}


int RedisConn::Ping()
{
	//redisReply *Reply = static_cast<redisReply *>(redisCommand(_ctx, "ping"));
	return 0;
}
