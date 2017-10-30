#include "RedisConnPool.h"

#pragma once

using namespace std;

class RedisCtxGuard
{
public:
	explicit RedisCtxGuard(RedisConnPool *conn_pool);
	~RedisCtxGuard();
	RedisCtxGuard(const RedisCtxGuard &) = delete;
	RedisCtxGuard & operator = (const RedisCtxGuard &) = delete;
	redisContext* GetCtx();
	std::shared_ptr<RedisConn > GetConn(){return pConn;}
private:
	RedisConnPool *_conn_pool;
	std::shared_ptr<RedisConn > pConn;
};

class RedisCmd
{
public:
	RedisCmd(RedisOpt &Opt);
	~RedisCmd();

	//redisReply *vCommand(redisContext *c, const char *format, va_list ap);
	redisReply *Command(const char* cmd, ...);
	int CommandBool(bool &ret,const char* cmd, ...);
	int CommandInter(long long &ret,const char* cmd, ...);
	int ReplytoString(string &ret,const char* cmd, ...);
public:
	/*template<typename T>
	void FormatReply(int type,redisReply *reply,T &ret)
	{
		switch(type)
		{
			case 0:
				break;
		}
	}*/
	void ReplytoBool(redisReply *reply,bool &ret);
	void ReplytoInter();
	void ReplytoString();
	void ReplytoList();
	void ReplytoArray();
	void ReplytoMap();
private:
	RedisConnPool _conn_pool;
};