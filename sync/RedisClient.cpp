#include "RedisClient.h"

IRedisClient::IRedisClient()
//:_cmd(Opt)
{
	//_cmd = new RedisNormalCmd(Opt);
}

IRedisClient::~IRedisClient()
{
	/*if (_cmd)
	{
		delete _cmd;
		_cmd = NULL;
	}*/
}

shared_ptr<IntResult> IRedisClient::Del(const vector<string>& Keys)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->vCommand(RT_INTEGER, "del", Keys, *Result,&Result->val);
	return Result;
}

shared_ptr<StringResult> IRedisClient::Dump(const string& Key)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "dump %s", Key.c_str());
	return Result;
}

shared_ptr<BoolResult> IRedisClient::Exists(const string& Key)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "exists %s", Key.c_str());
	return Result;
}

shared_ptr<BoolResult> IRedisClient::Expire(const string& Key, uint32_t Seconds)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "expire %s %d", Key.c_str(), Seconds);
	return Result;
}

shared_ptr<BoolResult> IRedisClient::ExpireAt(const string& Key, uint64_t Timestamp)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "expire %s %u", Key.c_str(), Timestamp);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::Keys(const string& Pattern)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Pattern.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Pattern is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "keys %s", Pattern.c_str());
	return Result;
}

shared_ptr<BoolResult> IRedisClient::Persist(const string& Key)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "persist %s", Key.c_str());
	return Result;
}

shared_ptr<BoolResult> IRedisClient::PExpire(const string& Key, uint32_t MilliSec)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "pexpire %s %d", Key.c_str(), MilliSec);
	return Result;
}

shared_ptr<BoolResult> IRedisClient::PExpireAt(const string&Key, uint64_t Timestamp)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "pexpireat %s %lu", Key.c_str(), Timestamp);
	return Result;
}

shared_ptr<IntResult> IRedisClient::PTTL(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "pttl %s", Key.c_str());
	return Result;
}

shared_ptr<StringResult> IRedisClient::RandomKey()
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	_cmd->Command(RT_STRING, *Result, &Result->val, "randomkey");
	return Result;
}

shared_ptr<StatusResult> IRedisClient::Rename(const string& Key, const string& NewKey)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty() || NewKey.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_STATUS, *Result, &Result->val, "rename %s %s", Key.c_str(), NewKey.c_str());
	return Result;
}

shared_ptr<BoolResult> IRedisClient::RenameNX(const string& Key, const string& NewKey)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty() || NewKey.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "renamenx %s %s", Key.c_str(), NewKey.c_str());
	return Result;
}

shared_ptr<StatusResult> IRedisClient::Restore(const string& Key, int64_t TTL, const string& SerializedValue, bool Repalce /*= false*/)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty() || SerializedValue.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	if (Repalce)
	{
		_cmd->Command(RT_STATUS, *Result, &Result->val, "restore %s %d %b replace", Key.c_str(), TTL, SerializedValue.c_str(), SerializedValue.size());
	}
	_cmd->Command(RT_STATUS, *Result, &Result->val, "restore %s %d %b", Key.c_str(), TTL, SerializedValue.c_str(), SerializedValue.size());
	return Result;
}

shared_ptr<IntResult> IRedisClient::TTL(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "ttl %s", Key.c_str());
	return Result;
}

shared_ptr<StringResult> IRedisClient::Type(const string& Key)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "type %s", Key.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::Append(const string& Key, const string& Value)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "append %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

shared_ptr<IntResult> IRedisClient::BitCount(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "bitcount %s", Key.c_str());
	return Result;
}
shared_ptr<IntResult> IRedisClient::BitCount(const string& Key, int Start, int End)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "bitcount %s %d %d", Key.c_str(), Start, End);
	return Result;
}

shared_ptr<IntResult> IRedisClient::BitOp(const string& Op, const string& DestKey, const vector<string>& Keys)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Op.empty() || DestKey.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("bitop");
	Cmd.push_back(Op);
	Cmd.push_back(DestKey);
	_cmd->vCommand(RT_INTEGER, Cmd, Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::BitOpAnd(const string& DestKey, const vector<string>& Keys)
{
	return BitOp("AND", DestKey, Keys);
}

shared_ptr<IntResult> IRedisClient::BitOpOr(const string& DestKey, const vector<string>& Keys)
{
	return BitOp("OR", DestKey, Keys);
}

shared_ptr<IntResult> IRedisClient::BitOpXor(const string& DestKey, const vector<string>& Keys)
{
	return BitOp("XOR", DestKey, Keys);
}

shared_ptr<IntResult> IRedisClient::BitOpNot(const string& DestKey, const vector<string>& Keys)
{
	return BitOp("NOT", DestKey, Keys);
}

shared_ptr<IntResult> IRedisClient::Decr(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "decr %s", Key.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::DecrBy(const string& Key, int64_t By)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "decr %s %lld", Key.c_str(), By);
	return Result;
}

shared_ptr<StringResult> IRedisClient::Get(const string& Key)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "get %s", Key.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::GetBit(const string& Key, int Offset)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "getbit %s %d", Key.c_str(), Offset);
	return Result;
}

shared_ptr<StringResult> IRedisClient::GetRange(const string& Key, int Start, int End)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "getrange %s %d %d", Key.c_str(), Start,End);
	return Result;
}

shared_ptr<StringResult> IRedisClient::GetSet(const string& Key, const string& Value)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "getset %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

shared_ptr<IntResult> IRedisClient::Incr(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "incr %s", Key.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::IncrBy(const string& Key, int64_t Incr)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "incrby %s %lld", Key.c_str(),Incr);
	return Result;
}

shared_ptr<FloatResult> IRedisClient::IncrByFloat(const string& Key, float Incr)
{
	shared_ptr<FloatResult> Result = make_shared<FloatResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_FLOAT, *Result, &Result->val, "incrbyfloat %s %f", Key.c_str(), Incr);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::MGet(const vector<string>& Keys)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->vCommand(RT_STRING_ARRAY, "mget", Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<StatusResult> IRedisClient::MSet(const vector<pair<string, string> >& KeyValues)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (KeyValues.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->vCommand(RT_STATUS, "mget", KeyValues, *Result, &Result->val);
	return Result;
}

shared_ptr<BoolResult> IRedisClient::MSetNX(const vector<pair<string, string> >& KeyValues)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (KeyValues.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->vCommand(RT_BOOL, "msetnx", KeyValues, *Result, &Result->val);
	return Result;
}

shared_ptr<StatusResult> IRedisClient::PSetEX(const string& Key, int64_t MilliSeconds, const string& Val)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty() || Val.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STATUS, *Result, &Result->val, "psetex %s %d %b", Key.c_str(), MilliSeconds, Val.c_str(),Val.size());
	return Result;
}

shared_ptr<StatusResult> IRedisClient::Set(const string& Key, const string& Value)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STATUS, *Result, &Result->val, "set %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

shared_ptr<StatusResult> IRedisClient::Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	string con;
	con = (Unit == em_sec) ? "ex" : "px";
	_cmd->Command(RT_STATUS, *Result, &Result->val, "set %s %b %s %d", Key.c_str(), Value.c_str(), Value.size(), con.c_str(), Time);
	return Result;
}

shared_ptr<StatusResult> IRedisClient::Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time, string_set_type Type)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	string con;
	con = (Unit == em_sec) ? "ex" : "px";
	string excon;
	excon = (Type == em_set_nx) ? "nx" : "xx";
	_cmd->Command(RT_STATUS, *Result, &Result->val, "set %s %b %s %d %s", Key.c_str(), Value.c_str(), Value.size(), con.c_str(), Time, excon.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::SetBit(const string& Key, uint32_t Offset, int64_t NewBitValue)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "setbit %s %d %d", Key.c_str(), Offset, NewBitValue);
	return Result;
}

shared_ptr<StatusResult> IRedisClient::SetEX(const string& Key, int Seconds, const string& Value)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STATUS, *Result, &Result->val, "setex %s %d %b", Key.c_str(), Seconds, Value.c_str(), Value.size());
	return Result;
}

shared_ptr<BoolResult> IRedisClient::SetNX(const string& Key, const string& Value)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "setnx %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

shared_ptr<IntResult> IRedisClient::SetRange(const string& Key, uint32_t Offset, const string& Value)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "setrange %s %d %b", Key.c_str(), Offset, Value.c_str(), Value.size());
	return Result;
}

shared_ptr<IntResult> IRedisClient::StrLen(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "strlen %s", Key.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::HDel(const string& Key, const vector<string>& Fields)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Fields.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("hdel");
	Cmd.push_back(Key);
	_cmd->vCommand(RT_INTEGER, Cmd, Fields, *Result, &Result->val);
	return Result;
}

shared_ptr<BoolResult> IRedisClient::HExists(const string& Key, const string& Field)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty() || Field.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "hexists %s %s", Key.c_str(),Field.c_str());
	return Result;
}

shared_ptr<StringResult> IRedisClient::HGet(const string& Key, const string& Field)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty() || Field.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "hget %s %s", Key.c_str(),Field.c_str());
	return Result;
}

shared_ptr<StringStringMapResult> IRedisClient::HGetAll(const string& Key)
{
	shared_ptr<StringStringMapResult> Result = make_shared<StringStringMapResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_STRING_MAP, *Result, &Result->val, "hgetall %s", Key.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::HIncrBy(const string& Key, const string& Field, int64_t Incr)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Field.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "hincrby %s %s %ld", Key.c_str(),Field.c_str(),Incr);
	return Result;
}

shared_ptr<FloatResult> IRedisClient::HIncrByFloat(const string& Key, const string& Field, float Incr)
{
	shared_ptr<FloatResult> Result = make_shared<FloatResult>();
	if (Key.empty() || Field.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_FLOAT, *Result, &Result->val, "hincrbyfloat %s %s %f", Key.c_str(),Field.c_str(),Incr);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::HKeys(const string& Key)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "hkeys %s", Key.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::HLen(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "hlen %s", Key.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::HMGet(const string& Key, const vector<string>& Fields)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty() || Fields.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("hmget");
	Cmd.push_back(Key);
	_cmd->vCommand(RT_STRING_ARRAY, Cmd, Fields, *Result, &Result->val);
	return Result;
}

shared_ptr<StatusResult> IRedisClient::HMSet(const string& Key, const vector<pair<string, string> >& FieldVal)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty() || FieldVal.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("hmset");
	Cmd.push_back(Key);
	_cmd->vCommand(RT_STATUS, Cmd, FieldVal, *Result, &Result->val);
	return Result;
}

shared_ptr<BoolResult> IRedisClient::HSet(const string& Key, const string& Field, const string& Value)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty() || Field.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "hset %s %s %b", Key.c_str(), Field.c_str(), Value.c_str(), Value.size());
	return Result;
}

shared_ptr<BoolResult> IRedisClient::HSetNX(const string& Key, const string& Field, const string& Value)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty() || Field.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "hsetnx %s %s %b", Key.c_str(), Field.c_str(), Value.c_str(), Value.size());
	return Result;
}

shared_ptr<IntResult> IRedisClient::HStrLen(const string& Key, const string& Field)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Field.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "hstrlen %s %s", Key.c_str(), Field.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::HVals(const string& Key)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "hvals %s", Key.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::BLPop(vector<string>& Keys, int Timeout)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	Keys.push_back(ToString(Timeout));
	_cmd->vCommand(RT_STRING_ARRAY, "blpop", Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::BRPop(vector<string>& Keys, int Timeout)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	Keys.push_back(ToString(Timeout));
	_cmd->vCommand(RT_STRING_ARRAY, "brpop", Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::BRPopLPush(const string& Src, const string& Dst, int Timeout)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Src.empty() || Dst.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "brpoplpush %s %s %d", Src.c_str(), Dst.c_str(), Timeout);
	return Result;
}

shared_ptr<StringResult> IRedisClient::LIndex(const string& Key, int64_t index)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "lindex %s %lld", Key.c_str(), index);
	return Result;
}

shared_ptr<IntResult> IRedisClient::LInsert(const string& Key, const list_insert_type Type, const string& Pivot, const string& Value)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Pivot.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	string stype = (Type == em_insert_before) ? "before" : "after";
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "linsert %s %s %b %b", Key.c_str(), stype.c_str(), Pivot.c_str(), Pivot.size(), Value.c_str(), Value.size());
	return Result;
}

shared_ptr<IntResult> IRedisClient::LInsertBefore(const string& Key, const string& Pivot, const string& Value)
{
	return LInsert(Key, em_insert_before, Pivot, Value);
}

shared_ptr<IntResult> IRedisClient::LInsertAfter(const string& Key, const string& Pivot, const string& Value)
{
	return LInsert(Key, em_insert_after, Pivot, Value);
}

shared_ptr<IntResult> IRedisClient::LLen(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "llen %s", Key.c_str());
	return Result;
}

shared_ptr<StringResult> IRedisClient::LPop(const string& Key)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "lpop %s", Key.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::LPush(const string& Key, const vector<string>& Values)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Values.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("lpush");
	Cmd.push_back(Key);
	_cmd->vCommand(RT_INTEGER, Cmd, Values,*Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::LPushX(const string& Key, const string& Value)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "lpushx %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::LRange(const string& Key, int64_t Start, int64_t Stop)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "lrange %s %lld %lld", Key.c_str(), Start, Stop);
	return Result;
}

shared_ptr<IntResult> IRedisClient::LRem(const string& Key, int64_t Count, const string& Value)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "lrem %s %lld %b", Key.c_str(), Count,Value.c_str(), Value.size());
	return Result;
}

shared_ptr<StatusResult> IRedisClient::LSet(const string& Key, int64_t Index, const string& Value)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STATUS, *Result, &Result->val, "lset %s %lld %b", Key.c_str(), Index, Value.c_str(), Value.size());
	return Result;
}

shared_ptr<StatusResult> IRedisClient::LTrim(const string& Key, int64_t Start, int64_t End)
{
	shared_ptr<StatusResult> Result = make_shared<StatusResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STATUS, *Result, &Result->val, "ltrim %s %lld %lld", Key.c_str(), Start, End);
	return Result;
}

shared_ptr<StringResult> IRedisClient::RPop(const string& Key)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "rpop %s", Key.c_str());
	return Result;
}

shared_ptr<StringResult> IRedisClient::RPopLPush(const string& Src, const string& Dst)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Src.empty() || Dst.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "rpoplpush %s %s", Src.c_str(),Dst.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::RPush(const string& Key, const vector<string>& Values)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Values.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("rpush");
	Cmd.push_back(Key);
	_cmd->vCommand(RT_INTEGER, Cmd, Values, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::RPushX(const string& Key, const string& Value)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Value.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "rpushx %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

shared_ptr<IntResult> IRedisClient::SAdd(const string& Key, const vector<string>& Members)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Members.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("sadd");
	Cmd.push_back(Key);
	_cmd->vCommand(RT_INTEGER, Cmd, Members, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::SCard(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "scard %s", Key.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::SDiff(const vector<string>& Keys)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->vCommand(RT_STRING_ARRAY, "sdiff", Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::SDiffStore(const string& Dst, const vector<string>& Keys)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Dst.empty() || Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("sdiffstore");
	Cmd.push_back(Dst);
	_cmd->vCommand(RT_INTEGER, Cmd, Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::SInter(const vector<string>& Keys)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->vCommand(RT_STRING_ARRAY, "sinter", Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::SInterStore(const string& Dst, const vector<string>& Keys)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Dst.empty() || Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("sinterstore");
	Cmd.push_back(Dst);
	_cmd->vCommand(RT_INTEGER, Cmd, Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<BoolResult> IRedisClient::SIsMember(const string& Key, const string& Member)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Key.empty() || Member.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "sismember %s %b", Key.c_str(), Member.c_str(), Member.size());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::SMembers(const string& Key)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "smembers %s", Key.c_str());
	return Result;
}

shared_ptr<BoolResult> IRedisClient::SMove(const string& Src, const string& Dst, const string& Member)
{
	shared_ptr<BoolResult> Result = make_shared<BoolResult>();
	if (Src.empty() || Dst.empty() || Member.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_BOOL, *Result, &Result->val, "smove %s %s %b", Src.c_str(), Dst.c_str(), Member.c_str(), Member.size());
	return Result;
}

shared_ptr<StringResult> IRedisClient::SPop(const string& Key)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "spop %s", Key.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::SPopN(const string& Key, int64_t Count)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "spop %s %lld", Key.c_str(), Count);
	return Result;
}

shared_ptr<StringResult> IRedisClient::SRandMember(const string& Key)
{
	shared_ptr<StringResult> Result = make_shared<StringResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING, *Result, &Result->val, "srandmember %s", Key.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::SRandMemberN(const string& Key, int64_t Count)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "srandmember %s %lld", Key.c_str(), Count);
	return Result;
}

shared_ptr<IntResult> IRedisClient::SRem(const string& Key, const vector<string>& Members)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Members.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("srem");
	Cmd.push_back(Key);
	_cmd->vCommand(RT_INTEGER, Cmd, Members, *Result, &Result->val);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::SUnion(const vector<string>& Keys)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->vCommand(RT_STRING_ARRAY, "sunion", Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::SUnionStore(const string& Dst, const vector<string>& Keys)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Dst.empty() || Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("sunionstore");
	Cmd.push_back(Dst);
	_cmd->vCommand(RT_INTEGER, Cmd, Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZAdd(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || ScoreMem.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	_cmd->vCommand(RT_INTEGER, Cmd, ScoreMem, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZAddNX(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || ScoreMem.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("NX");
	_cmd->vCommand(RT_INTEGER, Cmd, ScoreMem, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZAddXX(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || ScoreMem.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("XX");
	_cmd->vCommand(RT_INTEGER, Cmd, ScoreMem, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZAddCh(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || ScoreMem.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("CH");
	_cmd->vCommand(RT_INTEGER, Cmd, ScoreMem, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZAddNXCh(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || ScoreMem.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("NX");
	Cmd.push_back("CH");
	_cmd->vCommand(RT_INTEGER, Cmd, ScoreMem, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZAddXXCh(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || ScoreMem.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("XX");
	Cmd.push_back("CH");
	_cmd->vCommand(RT_INTEGER, Cmd, ScoreMem, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZCard(const string& Key)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "zcard %s", Key.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZCount(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Min.empty() || Max.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "zcount %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<FloatResult> IRedisClient::ZincrBy(const string& Key, const float Incr, const string& Member)
{
	shared_ptr<FloatResult> Result = make_shared<FloatResult>();
	if (Key.empty() || Member.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_FLOAT, *Result, &Result->val, "zincrby %s %f %s", Key.c_str(), Incr, Member.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZlexCount(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Min.empty() || Max.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "zlexcount %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRange(const string& Key, int64_t Start, int64_t End)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrange %s %lld %lld", Key.c_str(), Start, End);
	return Result;
}

shared_ptr<StringFloatMapResult> IRedisClient::ZRangeWithScores(const string& Key, int64_t Start, int64_t End)
{
	shared_ptr<StringFloatMapResult> Result = make_shared<StringFloatMapResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_FLOAT_MAP, *Result, &Result->val, "zrange %s %lld %lld withscores", Key.c_str(), Start, End);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRangeByLex(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrangebylex %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRangeByLex(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrangebylex %s %s %s limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRangeByScore(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrangebyscore %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRangeByScore(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrangebyscore %s %s %s limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

shared_ptr<StringFloatMapResult> IRedisClient::ZRangeByScoreWithScores(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<StringFloatMapResult> Result = make_shared<StringFloatMapResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_FLOAT_MAP, *Result, &Result->val, "zrangebyscore %s %s %s withscores", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<StringFloatMapResult> IRedisClient::ZRangeByScoreWithScores(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	shared_ptr<StringFloatMapResult> Result = make_shared<StringFloatMapResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_FLOAT_MAP, *Result, &Result->val, "zrangebyscore %s %s %s withscores limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZRank(const string& Key, const string& Member)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Member.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "zrank %s %s", Key.c_str(), Member.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZRem(const string& Key, const vector<string>& Members)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Members.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zrem");
	Cmd.push_back(Key);
	_cmd->vCommand(RT_INTEGER, Cmd, Members, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZRemRangeByLex(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "zremrangebylex %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZRemRangeByRank(const string& Key, int64_t Start, int64_t End)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "zremrangebyrank %s %lld %lld", Key.c_str(), Start, End);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZRemRangeByScore(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "zremrangebyscore %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRevRange(const string& Key, int64_t Start, int64_t End)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrevrange %s %lld %lld", Key.c_str(), Start, End);
	return Result;
}

shared_ptr<StringFloatMapResult> IRedisClient::ZRevRangeWithScores(const string& Key, int64_t Start, int64_t End)
{
	shared_ptr<StringFloatMapResult> Result = make_shared<StringFloatMapResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_FLOAT_MAP, *Result, &Result->val, "zrevrange %s %lld %lld withscores", Key.c_str(), Start, End);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRevRangeByLex(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrevrangebylex %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRevRangeByLex(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrevrangebylex %s %s %s limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRevRangeByScore(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrevrangebyscore %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<StringArrayResult> IRedisClient::ZRevRangeByScore(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	shared_ptr<StringArrayResult> Result = make_shared<StringArrayResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_ARRAY, *Result, &Result->val, "zrevrangebyscore %s %s %s limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

shared_ptr<StringFloatMapResult> IRedisClient::ZRevRangeByScoreWithScores(const string& Key, const string& Min, const string& Max)
{
	shared_ptr<StringFloatMapResult> Result = make_shared<StringFloatMapResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_FLOAT_MAP, *Result, &Result->val, "zrevrangebyscore %s %s %s withscores", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

shared_ptr<StringFloatMapResult> IRedisClient::ZRevRangeByScoreWithScores(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	shared_ptr<StringFloatMapResult> Result = make_shared<StringFloatMapResult>();
	if (Key.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_STRING_FLOAT_MAP, *Result, &Result->val, "zrevrangebyscore %s %s %s withscores limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZRevRank(const string& Key, const string& Member)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Key.empty() || Member.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_INTEGER, *Result, &Result->val, "zrevrank %s %s", Key.c_str(), Member.c_str());
	return Result;
}

shared_ptr<FloatResult> IRedisClient::Zscore(const string& Key, const string& Member)
{
	shared_ptr<FloatResult> Result = make_shared<FloatResult>();
	if (Key.empty() || Member.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd->Command(RT_FLOAT, *Result, &Result->val, "zscore %s %s", Key.c_str(), Member.c_str());
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZunionStore(const string& Dst, vector<string>& Keys, const string &Aggregate /*= "SUM"*/)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Dst.empty() || Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zunionstore");
	Cmd.push_back(Dst);
	Cmd.push_back(ToString(Keys.size()));
	Keys.push_back(Aggregate);
	_cmd->vCommand(RT_INTEGER, Cmd, Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<IntResult> IRedisClient::ZunionStoreWeights(const string& Dst, vector<string>& Keys, const vector<float>& Weights, const string &Aggregate /*= "SUM"*/)
{
	shared_ptr<IntResult> Result = make_shared<IntResult>();
	if (Dst.empty() || Keys.empty())
	{
		Result->Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zunionstore");
	Cmd.push_back(Dst);
	Cmd.push_back(ToString(Keys.size()));
	for (auto i : Weights)
	{
		Keys.push_back(ToString(i));
	}
	Keys.push_back(Aggregate);
	_cmd->vCommand(RT_INTEGER, Cmd, Keys, *Result, &Result->val);
	return Result;
}

shared_ptr<RawResult> IRedisClient::RawCommand(const char* Cmd, ...)
{
	redisContext* Ctx = nullptr;
	redisReply *reply = nullptr;
	shared_ptr<RawResult> Result = make_shared<RawResult>();
	Result->Set(CMD_OPERATE_FAILED, "exec cmd failed");
	// to do maxretry
	for (int i = 0; i<2; i++)
	{
		RedisCtxGuard CtxGuard(&(static_cast<RedisNormalCmd*>(_cmd))->_conn_pool);
		Ctx = CtxGuard.GetCtx();
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
		va_start(args, Cmd);
		reply = static_cast<redisReply *>(redisvCommand(Ctx, Cmd, args));
		va_end(args);
		if (Ctx && Ctx->err == 1) //超时重试
		{
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
			continue;
		}
		if (reply)
		{
			Result->val = make_shared<RedisReply>(reply);
			if (REDIS_REPLY_ERROR == reply->type)
			{
				Result->Set(CMD_OPERATE_FAILED, string(reply->str, reply->len));
			}
			else
			{
				Result->Set(CMD_SUCCESS, "");
			}
			return Result;
		}
		else
		{
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
		}
	}
	if (nullptr == reply)
	{
		Result->Set(CMD_OPERATE_FAILED, "reply is null");
	}
	return Result;
}

shared_ptr<RawResult> IRedisClient::RawCommandv(const vector<string> &Cmd)
{
	vector<const char *> argv(Cmd.size());
	vector<size_t> argvlen(Cmd.size());
	unsigned int j = 0;
	for (vector<string>::const_iterator it = Cmd.begin(); it != Cmd.end(); ++it, ++j)
	{
		argv[j] = it->c_str();
		argvlen[j] = it->size();
	}
	redisContext* Ctx = nullptr;
	redisReply *reply = nullptr;
	shared_ptr<RawResult> Result = make_shared<RawResult>();
	// to do maxretry
	for (int i = 0; i<2; i++)
	{
		RedisCtxGuard CtxGuard(&(static_cast<RedisNormalCmd*>(_cmd))->_conn_pool);
		Ctx = CtxGuard.GetCtx();
		if (nullptr == Ctx)
		{
			continue;
		}
		if (nullptr != reply)
		{
			freeReplyObject((void*)reply);
			reply = nullptr;
		}
		reply = static_cast<redisReply *>(redisCommandArgv(Ctx, argv.size(), &(argv[0]), &(argvlen[0])));
		if (Ctx && Ctx->err == 1) //超时重试
		{
			printf("come here\n");
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
			continue;
		}
		if (reply)
		{
			Result->val = make_shared<RedisReply>(reply);
			if (REDIS_REPLY_ERROR == reply->type)
			{
				Result->Set(CMD_OPERATE_FAILED, string(reply->str, reply->len));
			}
			else
			{
				Result->Set(CMD_SUCCESS, "");
			}
			return Result;
		}
		else
		{
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
		}
	}
	if (nullptr == reply)
	{
		Result->Set(CMD_OPERATE_FAILED, "reply is null");
	}
	return Result;
}

RedisClient::RedisClient(RedisOpt &Opt)
{
	_cmd = new RedisNormalCmd(Opt);
}

RedisClient::~RedisClient()
{
	if (_cmd)
	{
		delete _cmd;
		_cmd = NULL;
	}
}

RedisPipeClient::RedisPipeClient(RedisClient *Client)
{
	if (Client && Client->_cmd)
	{
		_cmd = new RedisPipelineCmd(&(static_cast<RedisNormalCmd*>(Client->_cmd))->GetConnPool());
	}
	else
	{
		_cmd = nullptr;
	}
}

RedisPipeClient::~RedisPipeClient()
{
	if (_cmd)
	{
		delete _cmd;
		_cmd = NULL;
	}
}

void RedisPipeClient::Begin()
{
	if (_cmd == nullptr)
	{
		return;
	}
	static_cast<RedisPipelineCmd*>(_cmd)->Begin();
}

int RedisPipeClient::Exec()
{
	if (_cmd == nullptr)
	{
		return -1;
	}
	return static_cast<RedisPipelineCmd*>(_cmd)->Exec();
}