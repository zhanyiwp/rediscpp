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

RedisCmd::RedisCmd(RedisOpt &Opt)
:_conn_pool(Opt)
{

}

RedisCmd::~RedisCmd()
{

}

redisReply *RedisCmd::Command(const char* cmd, ...)
{
	redisContext* Ctx = nullptr;
	redisReply *reply = nullptr;
	// to do maxretry
	for(int i=0;i<2;i++)
	{
		RedisCtxGuard CtxGuard(&_conn_pool);
		Ctx= CtxGuard.GetCtx();
		if (nullptr == Ctx)
		{ 
			continue;
		}
		if (nullptr != reply)
		{
			freeReplyObject((void*)reply);
			reply = nullptr;
		}
		va_list args;
		va_start(args, cmd);
		reply = static_cast<redisReply *>(redisvCommand(Ctx, cmd, args));
		va_end(args);
		if(reply)
		{	
			break;
		}
		else
		{
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
		}
	}
	return reply;
}

void RedisCmd::Command(ReplyType Type, BaseResult &Result, void *Val, const char* Cmd, ...)
{
	
	redisContext* Ctx = nullptr;
	redisReply *reply = nullptr;
	// to do maxretry
	for (int i = 0; i<2; i++)
	{
		RedisCtxGuard CtxGuard(&_conn_pool); //必须放在for循环里面，否则连接不会被正确put会pool
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

void RedisCmd::DovCommand(ReplyType Type, vector<const char *> &Argv, const vector<size_t> &Argvlen, BaseResult &Result, void *Val)
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
			break;
		}
		case RT_TYPE:
		{
			break;
		}
		case RT_BOOL:
		{
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
		case RT_FLOAT_ARRAY:
		{
			break;
		}
		case RT_STRING_STRING_MAP:
		{
			std::map<std::string, std::string> *p = static_cast<std::map<std::string, std::string> *>(Val);
			for (size_t i = 0; i<Reply->elements - 1; i = i + 2)
			{
				p->insert(std::make_pair(string(Reply->element[i]->str, Reply->element[i]->len), string(Reply->element[i + 1]->str, Reply->element[i + 1]->len)));
			}
			Result.Set(CMD_SUCCESS, "");
			break;
		}
		case RT_STRING_FLOAT_MAP:
		{
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
			//return (strcasecmp(reply->str, "OK") == 0) ? true : false;
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