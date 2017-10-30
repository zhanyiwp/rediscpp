#include "RedisConnPool.h"

RedisConnPool::RedisConnPool(RedisOpt &Opt)
:_opt(Opt)
, _conn_count(0)
{

}

RedisConnPool::~RedisConnPool()
{
	for (auto it : _conn_pool)
	{

	}
}

std::shared_ptr<RedisConn> RedisConnPool::GetConn()
{
	std::shared_ptr<RedisConn> Conn = nullptr;
	if (_conn_pool.empty() && _conn_count < _opt._pool_size)
	{
		Conn = NewConntion();
		return Conn;
	}
	if (!_conn_pool.empty()) 
	{
		Conn = _conn_pool.front();
		_conn_pool.pop_front();
	}
	return Conn;
}

void RedisConnPool::FreeConn(std::shared_ptr<RedisConn>Conn)
{
	if(Conn)
		_conn_pool.push_back(Conn);
}

std::shared_ptr<RedisConn> RedisConnPool::NewConntion()
{
	std::shared_ptr<RedisConn> Conn = std::make_shared<RedisConn>(_opt);
	//_conn_pool.push_back(Conn);
	Conn->Connect();
	return Conn;
}