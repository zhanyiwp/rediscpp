#include "RedisConn.h"

//#ifdef __GXX_EXPERIMENTAL_CXX0X__
//#include <memory>
//#include <mutex>
//#else
#include <tr1/memory>
#include "Mutex.h"
//#endif


using namespace std;
using namespace std::tr1;
#pragma once

typedef std::list<shared_ptr<RedisConn> > ConnPool;

class RedisConnPool
{
public:
	RedisConnPool(RedisOpt &Opt);
	~RedisConnPool();

	shared_ptr<RedisConn> GetConn();
	void PutConn(shared_ptr<RedisConn> Conn);
	void Release();
private:
	shared_ptr<RedisConn> NewConntion();
private:
	ConnPool		_conn_pool;
	RedisOpt		_opt;
	unsigned int	_conn_count;
	//std::mutex		_mutex;
	MutexLock _mutex;
};