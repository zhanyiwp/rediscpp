
#include "hiredis.h"
#include <string.h>
#include <string>
#include <list>
#include <time.h>
#include <stdio.h>

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
	string          _host ;          // redis Host
	unsigned int    _port ;          // redis sever Port
	string          _password ;         // redis server Password
	unsigned int	_timeout ;
	unsigned int	_pool_size;
	RedisOpt();
	RedisOpt(string Host, unsigned int Port, string Password = "", unsigned int Timeout = 1500, unsigned int PoolSize = 10);

};


class RedisConn
{
public:
	RedisConn(RedisOpt &Opt);
	~RedisConn();

	int Connect() ;
	int Close();
	int Ping();

	redisContext*	GetRedisCtx()      
	{
		if (!valid_conn())
		{
			if (0 != Connect())
			{
				return NULL;
			}
		}
		return _ctx; 
	}

	ConnState	GetStatus() 
	{ 
		return  _status; 
	}
	
	void SetStatus(ConnState Status){_status = Status;}
private:
	int Auth();
	inline void FreeCtx() 
	{
		if (_ctx)
		{
			printf("free redis\n");
			redisFree(_ctx);
			_ctx = NULL;
		}
	}

	bool valid_conn()const
	{
		if ((!_password.empty() && _status > CS_CONNECTED) || _status > CS_CONNECTING)
			return true;
		return false;
	}

private:
	// redis connector context
	redisContext*		_ctx;
	string				_host;          // redis host
	unsigned int		_port;          // redis sever port
	string				_password;         // redis server password
	struct timeval		_timeout;
	ConnState			_status;    // redis connection status
	unsigned long long	_last_active_time;
};