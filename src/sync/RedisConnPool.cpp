#include "RedisConnPool.h"

RedisConnPool::RedisConnPool(RedisOpt &Opt)
:_opt(Opt)
, _conn_count(0)
{

}

RedisConnPool::~RedisConnPool()
{
	Release();
}

std::shared_ptr<RedisConn> RedisConnPool::GetConn()
{
	std::lock_guard<std::mutex> lock(_mutex);
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

void RedisConnPool::PutConn(std::shared_ptr<RedisConn>Conn)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if(Conn)
		_conn_pool.push_back(Conn);
}

std::shared_ptr<RedisConn> RedisConnPool::NewConntion()
{
	std::shared_ptr<RedisConn> Conn = std::make_shared<RedisConn>(_opt);
	_conn_count++;
	Conn->Connect();
	return Conn;
}

void RedisConnPool::Release()
{
	std::lock_guard<std::mutex> lock(_mutex);
	for (auto it : _conn_pool)
	{
		it->Close();
		_conn_count--;
	}
	_conn_pool.clear();
}