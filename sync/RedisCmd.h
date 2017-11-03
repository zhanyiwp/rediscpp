#include "RedisConnPool.h"
#include <vector>
#include <sstream>
#include <map>
#include <mutex>
#pragma once

using namespace std;


enum ReplyType
{
	RT_BEGIN = 0,
	RT_STATUS = 1,
	RT_TYPE = 2,	//for type cmd
	RT_BOOL = 3,
	RT_INTEGER = 4,
	RT_DOUBLE = 5,
	RT_FLOAT = 6,
	RT_STRING = 7,
	RT_STRING_ARRAY = 8,
	RT_FLOAT_ARRAY = 9,
	RT_STRING_STRING_MAP = 10,
	RT_STRING_FLOAT_MAP = 11,
	RT_RAW = 12,
	RT_END=9999
};

enum CMDRESULT
{
	CMD_SUCCESS = 0,
	CMD_OPERATE_FAILED = 1,
	CMD_REPLY_NIL=2,
	CMD_REPLY_NOT_OK=3
};

struct RedisReply
{
	explicit RedisReply(redisReply * Reply) :_reply(Reply){}
	~RedisReply()
	{
		if (nullptr !=_reply)
		{
			freeReplyObject((void*)_reply);
			_reply = nullptr;
		}
	}
private:
	redisReply *_reply;
};
struct BaseResult
{
	BaseResult()
	{
		Ret = CMD_SUCCESS;
		ErrInfo = "";
	}
	void Set(CMDRESULT result, const string &Err)
	{
		Ret = result;
		ErrInfo = Err;
	}
	bool Success(){ return (CMD_SUCCESS == Ret) ? true : false; }
	const string &GetErr()const{ return ErrInfo; }
private:
	CMDRESULT Ret;
	string ErrInfo;
};

struct BoolResult :public BaseResult
{
	bool TRUE(){}
	const bool &GetVal()const { return val; }
	bool val;
};

struct StatusResult :public BaseResult
{
	bool OK(){}
	const string &GetVal()const { return val; }
	string val;
};

struct StringResult :public BaseResult
{
	const string &GetVal()const { return val; }
	string val;
};

struct IntResult :public BaseResult
{
	const int64_t &GetVal()const { return val; }
	int64_t val;
};

struct StringArrayResult :public BaseResult
{
	const vector<string> &GetVal()const { return val; }
	vector<string> val;
};

struct FloatResult :public BaseResult
{
	const float &GetVal()const { return val; }
	float val;
};

struct StringStringMapResult :public BaseResult
{
	const map<string,string> &GetVal()const { return val; }
	map<string,string> val;
};

struct StringFloatMapResult :public BaseResult
{
	const map<string, float> &GetVal()const { return val; }
	map<string, float> val;
};

struct RawResult:public BaseResult
{
	shared_ptr<RedisReply> GetVal()const { return val; }
	shared_ptr<RedisReply> val;
};

template<class T>
std::string ToString(const T &t)
{
	ostringstream oss;
	oss << t;
	return oss.str();
}

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
	RedisCmd();
	~RedisCmd();

	virtual void Command(ReplyType Type, BaseResult &Result,void *Val, const char* Cmd, ...) = 0;
	void vCommand(ReplyType Type, const string &Command, const vector<string> &V, BaseResult &Result, void *Val);
	void vCommand(ReplyType Type, const vector<string> &Commands, const vector<string> &V, BaseResult &Result, void *Val);
	void vCommand(ReplyType Type, const string &Command, const vector<pair<string, string> >&V, BaseResult &Result, void *Val);
	void vCommand(ReplyType Type, const vector<string> &Commands, const vector<pair<string, string> >&V, BaseResult &Result, void *Val);
	void vCommand(ReplyType Type, const vector<string> &Commands, const vector<pair<float, string> >&V, BaseResult &Result, void *Val);
	redisReply *Command(const char* cmd, ...);
protected:
	virtual void DovCommand(ReplyType Type, vector<const char *> &Argv, const vector<size_t> &Argvlen, BaseResult &Result, void *Val) = 0;
	bool CheckReply(const redisReply *Reply, BaseResult &Result);
	void FormatReply(ReplyType Type, redisReply *Reply, BaseResult &Result, void *Val);
};

class RedisNormalCmd :public RedisCmd
{
	friend class IRedisClient;
public:
	RedisNormalCmd(RedisOpt &Opt);
	~RedisNormalCmd();
	void Command(ReplyType Type, BaseResult &Result, void *Val, const char* Cmd, ...);
	RedisConnPool &GetConnPool(){ return _conn_pool; }
private:
	void DovCommand(ReplyType Type, vector<const char *> &Argv, const vector<size_t> &Argvlen, BaseResult &Result, void *Val);
private:
	RedisConnPool _conn_pool;
};

class RedisPipelineCmd :public RedisCmd
{
public:
	RedisPipelineCmd(RedisConnPool *ConnPool);
	~RedisPipelineCmd();
	void Begin();
	void Command(ReplyType Type, BaseResult &Result, void *Val, const char* Cmd, ...);
	int Exec();
private:
	void DovCommand(ReplyType Type, vector<const char *> &Argv, const vector<size_t> &Argvlen, BaseResult &Result, void *Val);
private:
	RedisConnPool* _conn_pool;
	shared_ptr<RedisConn> _conn;
	redisContext* _ctx;
	std::mutex	_mutex;
	map<int,tuple<ReplyType, BaseResult*,void *>> _reply;
	vector<tuple<ReplyType, BaseResult*,void *>> _success_reply;
	int index;
};