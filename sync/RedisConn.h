
#include "hiredis.h"
#include <string.h>
#include <string>
#include <list>
#include <time.h>

#pragma once

using namespace std;

enum ConnState
{
	CS_UNCONNECTED = 0,
	CS_CONNECTING = 1,
	CS_CONNECTED = 2,
	CS_AUTHENTICATION = 3
};

struct RedisOpt
{
	string          _host;          // redis host
	unsigned int    _port;          // redis sever port
	string          _password;         // redis server password
	unsigned int	_timeout = 1500;
	unsigned int	_pool_size = 10;
};

class RedisConn
{
public:
	RedisConn(RedisOpt &Opt);
	//RedisConn(const string &Host, unsigned int Port, const string &Password, struct timeval	Timeout);
	~RedisConn();

	int Connect();
	int Close();
	int ReConnect();
	int Ping();

	redisContext*	GetRedisCtx() const     { return _ctx; }
	ConnState      GetStatus() const   { return  _status; }

private:
	int Auth();
	inline void FreeCtx()
	{
		if (_ctx)
		{
			redisFree(_ctx);
			_ctx = NULL;
		}
	}

private:
	// redis connector context
	redisContext*	_ctx;
	string          _host;          // redis host
	unsigned int    _port;          // redis sever port
	string          _password;         // redis server password
	struct timeval	_timeout;
	ConnState       _status;    // redis connection status
	unsigned long long _last_active_time;
};