#include "RedisCmd.h"
#include <map>

RedisCtxGuard::RedisCtxGuard(RedisConnPool *conn_pool)
:_conn_pool(conn_pool)
{

}

RedisCtxGuard::~RedisCtxGuard()
{
	if (_conn_pool)
	{
		printf("Put Conn\n");
		_conn_pool->PutConn(pConn);
	}
}

redisContext* RedisCtxGuard::GetCtx()
{
	printf("Get Conn\n");
	pConn = _conn_pool->GetConn();
	if (pConn == nullptr)
	{
		return nullptr;
	}
	return pConn->GetRedisCtx();
}

RedisCmd::RedisCmd()
{

}

RedisCmd::~RedisCmd()
{

}

void RedisCmd::vCommand(ReplyType Type, const string &Command, const vector<string> &V, BaseResult &Result, void *Val)
{
	vector<const char *> argv(V.size() + 1);
	vector<size_t> argvlen(V.size() + 1);
	argv[0] = Command.c_str();
	argvlen[0] = Command.size();
	size_t j = 1;
	for (vector<string>::const_iterator it = V.begin(); it != V.end(); ++it, ++j)
	{
		argv[j] = it->c_str();
		argvlen[j] = it->size();
	}
	DovCommand(Type, argv, argvlen, Result, Val);
	return;
}

void RedisCmd::vCommand(ReplyType Type, const vector<string> &Commands, const vector<string> &V, BaseResult &Result, void *Val)
{
	vector<const char *> argv(V.size() + Commands.size());
	vector<size_t> argvlen(V.size() + Commands.size());
	size_t j = 0;
	for (vector<string>::const_iterator it = Commands.begin(); it != Commands.end(); ++it, ++j)
	{
		argv[j] = it->c_str();
		argvlen[j] = it->size();
	}
	for (vector<string>::const_iterator it = V.begin(); it != V.end(); ++it, ++j)
	{
		argv[j] = it->c_str();
		argvlen[j] = it->size();
	}
	DovCommand(Type, argv, argvlen, Result, Val);
	return;
}

void RedisCmd::vCommand(ReplyType Type, const string &Command ,const vector<pair<string, string> >&V, BaseResult &Result, void *Val)
{	
	vector<const char *> argv(V.size() + 1);
	vector<size_t> argvlen(V.size() + 1);
	argv[0] = Command.c_str();
	argvlen[0] = Command.size();
	size_t j = 1;
	for (vector<pair<string, string> >::const_iterator it = V.begin(); it != V.end(); ++it, j=j+2)
	{
		argv[j] = it->first.c_str();
		argvlen[j] = it->first.size();
		argv[j+1] = it->second.c_str();
		argvlen[j + 1] = it->second.size();
	}
	DovCommand(Type, argv, argvlen, Result, Val);
	return;
}

void RedisCmd::vCommand(ReplyType Type, const vector<string> &Commands, const vector<pair<string, string> >&V, BaseResult &Result, void *Val)
{
	vector<const char *> argv(V.size() + Commands.size());
	vector<size_t> argvlen(V.size() + Commands.size());
	size_t j = 0;
	for (vector<string>::const_iterator it = Commands.begin(); it != Commands.end(); ++it, ++j)
	{
		argv[j] = it->c_str();
		argvlen[j] = it->size();
	}
	for (vector<pair<string, string> >::const_iterator it = V.begin(); it != V.end(); ++it, j = j + 2)
	{
		argv[j] = it->first.c_str();
		argvlen[j] = it->first.size();
		argv[j + 1] = it->second.c_str();
		argvlen[j + 1] = it->second.size();
	}
	DovCommand(Type, argv, argvlen, Result, Val);
	return;
}

void RedisCmd::vCommand(ReplyType Type, const vector<string> &Commands, const vector<pair<float, string> >&V, BaseResult &Result, void *Val)
{
	vector<const char *> argv(V.size() + Commands.size());
	vector<size_t> argvlen(V.size() + Commands.size());
	size_t j = 0;
	for (vector<string>::const_iterator it = Commands.begin(); it != Commands.end(); ++it, ++j)
	{
		argv[j] = it->c_str();
		argvlen[j] = it->size();
	}
	for (vector<pair<float, string> >::const_iterator it = V.begin(); it != V.end(); ++it, j = j + 2)
	{
		argv[j] = ToString(it->first).c_str();
		argvlen[j] = ToString(it->first).size();
		argv[j + 1] = it->second.c_str();
		argvlen[j + 1] = it->second.size();
	}
	DovCommand(Type, argv, argvlen, Result, Val);
	return;
}

void RedisCmd::FormatReply(ReplyType Type, redisReply *Reply, BaseResult &Result, void *Val)
{
	if (!CheckReply(Reply, Result))
	{
		return ;
	}
	// to do 
	switch (Type)
	{
		case RT_STATUS:
		{
			static_cast<string *>(Val)->assign(Reply->str, Reply->len);
			Result.Set(CMD_SUCCESS, "");
			break;
		}
		case RT_TYPE:
		{
			break;
		}
		case RT_BOOL:
		{
			*(static_cast<bool *>(Val)) = ((Reply->integer == 1) ? true : false);
			Result.Set(CMD_SUCCESS, "");
			break;
		}
		case RT_INTEGER:
		{
			*(static_cast<int *>(Val)) = Reply->integer;
			Result.Set(CMD_SUCCESS, "");
			break;
		}
		case RT_DOUBLE:
		{
			break;
		}
		case RT_FLOAT:
		{
			string s(Reply->str, Reply->len);
			*static_cast<float *>(Val)= atof(s.c_str());
			Result.Set(CMD_SUCCESS, "");
			break;
		}
		case RT_STRING:
		{
			static_cast<string *>(Val)->assign(Reply->str, Reply->len);
			Result.Set(CMD_SUCCESS, "");
			break;
		}
		case RT_STRING_ARRAY:
		{
			std::vector<std::string> *p = static_cast<std::vector<std::string> *>(Val);
			for (size_t i = 0; i < Reply->elements; i++)
			{
				p->push_back(string(Reply->element[i]->str, Reply->element[i]->len));
			}
			Result.Set(CMD_SUCCESS, "");
			break;
		}
		case RT_BOOL_ARRAY:
		{
			std::vector<bool> *p = static_cast<std::vector<bool> *>(Val);
			for (size_t i = 0; i < Reply->elements; i++)
			{
				p->push_back(((Reply->element[i]->integer == 1) ? true : false));
			}
			Result.Set(CMD_SUCCESS, "");
			break;
		}
		case RT_STRING_STRING_MAP:
		{
			std::map<std::string, std::string> *p = static_cast<std::map<std::string, std::string> *>(Val);
			for (size_t i = 0; Reply->elements > 0 && i < Reply->elements - 1; i = i + 2)
			{
				p->insert(std::make_pair(string(Reply->element[i]->str, Reply->element[i]->len), string(Reply->element[i + 1]->str, Reply->element[i + 1]->len)));
			}
			Result.Set(CMD_SUCCESS, "");
			break;
		}
		case RT_STRING_FLOAT_MAP:
		{
			std::map<std::string, float> *p = static_cast<std::map<std::string, float> *>(Val);
			for (size_t i = 0; Reply->elements > 0 && i< Reply->elements - 1; i = i + 2)
			{
				string s(Reply->element[i + 1]->str, Reply->element[i + 1]->len);
				float f = atof(s.c_str());
				p->insert(std::make_pair(string(Reply->element[i]->str, Reply->element[i]->len), f));
			}
			Result.Set(CMD_SUCCESS, "");
			break;
		}
			
		default:
		{
			Result.Set(CMD_OPERATE_FAILED, "unkonw reply type");
			break;
		}
	}
	return;
}

bool RedisCmd::CheckReply(const redisReply *reply, BaseResult &Result)
{
	if (nullptr == reply) 
	{
		Result.Set(CMD_OPERATE_FAILED, "reply is null");
		return false;
	}
	switch (reply->type)
	{
		case REDIS_REPLY_STRING:
		{
			return true;
		}
		case REDIS_REPLY_ARRAY:
		{
			return true;
		}
		case REDIS_REPLY_INTEGER:
		{
			return true;
		}
		case REDIS_REPLY_NIL:
		{
			Result.Set(CMD_REPLY_NIL, "REDIS_REPLY_NIL");
			return false;
		}
		case REDIS_REPLY_STATUS:
		{
			return true;
		}
		case REDIS_REPLY_ERROR:
		{
			Result.Set(CMD_OPERATE_FAILED, string(reply->str, reply->len));
			return false;
		}
		default:
		{
			Result.Set(CMD_OPERATE_FAILED, "unknow reply type");
			return false;
		}
	}
	return false;
}

RedisNormalCmd::RedisNormalCmd(RedisOpt &Opt)
:_conn_pool(Opt)
{
	
}

RedisNormalCmd::~RedisNormalCmd()
{

}

void RedisNormalCmd::Command(ReplyType Type, BaseResult &Result, void *Val, const char* Cmd, ...)
{
	redisContext* Ctx = nullptr;
	redisReply *reply = nullptr;
	// to do maxretry
	for (int i = 0; i<2; i++)
	{
		RedisCtxGuard CtxGuard(&_conn_pool);  //必须放在for循环里面，否则连接不会被正确put会pool
		Ctx = CtxGuard.GetCtx();
		// GetCtx err
		if (nullptr == Ctx)
		{
			Result.Set(CMD_OPERATE_FAILED, "GetCtx Failed");
			continue;
		}
		if (nullptr != reply)
		{
			freeReplyObject((void*)reply);
			reply = nullptr;
		}
		va_list args;
		va_start(args, Cmd);
		reply = static_cast<redisReply *>(redisvCommand(Ctx, Cmd, args));
		va_end(args);
		if (Ctx && Ctx->err == 1) //超时重试
		{
			printf("come here\n");
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
			continue;
		}
		if (reply)
		{
			break;
		}
		else
		{
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
		}
	}
	FormatReply(Type, reply, Result, Val);
	if (nullptr != reply)
	{
		freeReplyObject((void*)reply);
		reply = nullptr;
	}
	return;
}

void RedisNormalCmd::DovCommand(ReplyType Type, vector<const char *> &Argv, const vector<size_t> &Argvlen, BaseResult &Result, void *Val)
{
	redisContext* Ctx = nullptr;
	redisReply *reply = nullptr;
	// to do maxretry
	for (int i = 0; i<2; i++)
	{
		RedisCtxGuard CtxGuard(&_conn_pool);
		Ctx = CtxGuard.GetCtx();
		if (nullptr == Ctx)
		{
			Result.Set(CMD_OPERATE_FAILED, "GetCtx Failed");
			continue;
		}
		if (nullptr != reply)
		{
			freeReplyObject((void*)reply);
			reply = nullptr;
		}
		reply = static_cast<redisReply *>(redisCommandArgv(Ctx, Argv.size(), &(Argv[0]), &(Argvlen[0])));
		if (Ctx && Ctx->err == 1)  //超时重试
		{
			printf("come here\n");
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
			continue;
		}
		if (reply)
		{
			break;
		}
		else
		{
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
		}
	}
	FormatReply(Type, reply, Result, Val);
	if (nullptr != reply)
	{
		freeReplyObject((void*)reply);
		reply = nullptr;
	}
}


RedisPipelineCmd::RedisPipelineCmd(RedisConnPool *ConnPool)
:_conn_pool(ConnPool)
{

}

RedisPipelineCmd::~RedisPipelineCmd()
{

}


void RedisPipelineCmd::GetCtx()
{
	printf("Get Conn\n");
	if (nullptr == _ctx && _conn_pool != nullptr)
	{
		index = 0;
		_conn = _conn_pool->GetConn();
		if (_conn)
		{
			_ctx = _conn->GetRedisCtx();
		}
		else
		{
			_ctx = nullptr;
		}
	}
	//_mutex.lock();
}

void RedisPipelineCmd::Command(ReplyType Type, BaseResult &Result, void *Val, const char* Cmd, ...)
{
	GetCtx();
	int ret = -1;
	_reply[index++] = std::make_tuple(Type,&Result, Val);
	if (nullptr == _ctx)
	{
		Result.Set(CMD_OPERATE_FAILED, "GetCtx Failed");
		return ;
	}
	va_list args;
	va_start(args, Cmd);
	ret = (redisvAppendCommand(_ctx, Cmd, args));
	va_end(args);
	if (ret == REDIS_OK)
	{
		_success_reply.push_back(std::make_tuple(Type, &Result, Val));
	}
	else
	{
		Result.Set(CMD_OPERATE_FAILED, "add command Failed");
	}
	return;
}

void RedisPipelineCmd::DovCommand(ReplyType Type, vector<const char *> &Argv, const vector<size_t> &Argvlen, BaseResult &Result, void *Val)
{
	GetCtx();
	int ret = -1;
	_reply[index++] = std::make_tuple(Type, &Result, Val);
	if (nullptr == _ctx)
	{
		Result.Set(CMD_OPERATE_FAILED, "GetCtx Failed");
		return;
	}
	ret = redisAppendCommandArgv(_ctx, Argv.size(), &(Argv[0]), &(Argvlen[0]));
	if (ret == REDIS_OK)
	{
		_success_reply.push_back(std::make_tuple(Type, &Result, Val));
	}
	else
	{
		Result.Set(CMD_OPERATE_FAILED, "add command Failed");
	}
}

int RedisPipelineCmd::Exec()
{
	for (size_t i = 0; i != _success_reply.size(); i++)
	{
		void *pReplay = NULL;
		redisGetReply(_ctx, &pReplay);
		if ((_ctx && _ctx->err == 1) || nullptr==pReplay)//超时重试
		{
			_conn->SetStatus(CS_UNCONNECTED);
			index = 0;
			_conn_pool->PutConn(_conn);
			//_mutex.unlock();
			return -1;
		}
		FormatReply(std::get<0>(_reply[i]), (redisReply*)pReplay, *std::get<1>(_reply[i]), std::get<2>(_reply[i]));
		if (nullptr != pReplay)
		{
			freeReplyObject((void*)pReplay);
			pReplay = nullptr;
		}
	}
	index = 0;
	if (_conn_pool != nullptr)
	{
		_conn_pool->PutConn(_conn);
		_conn.reset();
		_ctx = nullptr;
	}
	_reply.clear();
	_success_reply.clear();
	//_mutex.unlock();
	return 0;
}