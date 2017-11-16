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

shared_ptr<RedisConn> RedisConnPool::GetConn()
{
	//std::lock_guard<std::mutex> lock(_mutex);
	MutexLockGuard lock(_mutex);
	shared_ptr<RedisConn> Conn ;
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

void RedisConnPool::PutConn(shared_ptr<RedisConn>Conn)
{
	MutexLockGuard lock(_mutex);
	if(Conn)
		_conn_pool.push_back(Conn);
}

shared_ptr<RedisConn> RedisConnPool::NewConntion()
{
	shared_ptr<RedisConn> Conn = shared_ptr<RedisConn>(new RedisConn(_opt));
	Conn->Connect();
	return Conn;
}

void RedisConnPool::Release()
{
	for (list<shared_ptr<RedisConn> > ::iterator it = _conn_pool.begin(); it != _conn_pool.end(); it++)
	{
		it->get()->Close();
	}
	MutexLockGuard lock(_mutex);
	_conn_pool.clear();
}