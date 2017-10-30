#include "RedisConn.h"
#include <memory>

#pragma once

typedef std::list<std::shared_ptr<RedisConn>> ConnPool;

class RedisConnPool
{
public:
	RedisConnPool(RedisOpt &Opt);
	~RedisConnPool();

	std::shared_ptr<RedisConn> GetConn();
	void FreeConn(std::shared_ptr<RedisConn> Conn);
private:
	std::shared_ptr<RedisConn> NewConntion();
private:
	ConnPool		_conn_pool;
	RedisOpt		_opt;
	unsigned int	_conn_count;
};