#include "RedisConn.h"
#include <memory>
#include <mutex>

#pragma once

typedef std::list<std::shared_ptr<RedisConn>> ConnPool;

class RedisConnPool
{
public:
	RedisConnPool(RedisOpt &Opt);
	~RedisConnPool();

	std::shared_ptr<RedisConn> GetConn();
	void PutConn(std::shared_ptr<RedisConn> Conn);
	void Release();
private:
	std::shared_ptr<RedisConn> NewConntion();
private:
	ConnPool		_conn_pool;
	RedisOpt		_opt;
	unsigned int	_conn_count;
	std::mutex		_mutex;
};