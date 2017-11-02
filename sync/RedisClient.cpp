#include "RedisClient.h"

RedisClient::RedisClient(RedisOpt &Opt)
:_cmd(Opt)
{

}

RedisClient::~RedisClient()
{

}

IntResult RedisClient::Del(const vector<string>& Keys)
{
	IntResult Result;
	if (Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.vCommand(RT_INTEGER, "del", Keys, Result,&Result.val);
	return Result;
}

StringResult RedisClient::Dump(const string& Key)
{
	StringResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "dump %s", Key.c_str());
	return Result;
}

BoolResult RedisClient::Exists(const string& Key)
{
	BoolResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "exists %s", Key.c_str());
	return Result;
}

BoolResult RedisClient::Expire(const string& Key, uint32_t Seconds)
{
	BoolResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "expire %s %d", Key.c_str(), Seconds);
	return Result;
}

BoolResult RedisClient::ExpireAt(const string& Key, uint64_t Timestamp)
{
	BoolResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "expire %s %u", Key.c_str(), Timestamp);
	return Result;
}

StringArrayResult RedisClient::Keys(const string& Pattern)
{
	StringArrayResult Result;
	if (Pattern.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Pattern is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "keys %s", Pattern.c_str());
	return Result;
}

BoolResult RedisClient::Persist(const string& Key)
{
	BoolResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "persist %s", Key.c_str());
	return Result;
}

BoolResult RedisClient::PExpire(const string& Key, uint32_t MilliSec)
{
	BoolResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "pexpire %s %d", Key.c_str(), MilliSec);
	return Result;
}

BoolResult RedisClient::PExpireAt(const string&Key, uint64_t Timestamp)
{
	BoolResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "pexpireat %s %lu", Key.c_str(), Timestamp);
	return Result;
}

IntResult RedisClient::PTTL(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "pttl %s", Key.c_str());
	return Result;
}

StringResult RedisClient::RandomKey()
{
	StringResult Result;
	_cmd.Command(RT_STRING, Result, &Result.val, "randomkey");
	return Result;
}

StatusResult RedisClient::Rename(const string& Key, const string& NewKey)
{
	StatusResult Result;
	if (Key.empty() || NewKey.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_STATUS, Result, &Result.val, "rename %s %s", Key.c_str(), NewKey.c_str());
	return Result;
}

BoolResult RedisClient::RenameNX(const string& Key, const string& NewKey)
{
	BoolResult Result;
	if (Key.empty() || NewKey.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "renamenx %s %s", Key.c_str(), NewKey.c_str());
	return Result;
}

StatusResult RedisClient::Restore(const string& Key, int64_t TTL, const string& SerializedValue, bool Repalce /*= false*/)
{
	StatusResult Result;
	if (Key.empty() || SerializedValue.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	if (Repalce)
	{
		_cmd.Command(RT_STATUS, Result, &Result.val, "restore %s %d %b replace", Key.c_str(), TTL, SerializedValue.c_str(), SerializedValue.size());
	}
	_cmd.Command(RT_STATUS, Result, &Result.val, "restore %s %d %b", Key.c_str(), TTL, SerializedValue.c_str(), SerializedValue.size());
	return Result;
}

IntResult RedisClient::TTL(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "ttl %s", Key.c_str());
	return Result;
}

StringResult RedisClient::Type(const string& Key)
{
	StringResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "type %s", Key.c_str());
	return Result;
}

IntResult RedisClient::Append(const string& Key, const string& Value)
{
	IntResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "append %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

IntResult RedisClient::BitCount(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "bitcount %s", Key.c_str());
	return Result;
}
IntResult RedisClient::BitCount(const string& Key, int Start, int End)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "bitcount %s %d %d", Key.c_str(), Start, End);
	return Result;
}

IntResult RedisClient::BitOp(const string& Op, const string& DestKey, const vector<string>& Keys)
{
	IntResult Result;
	if (Op.empty() || DestKey.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("bitop");
	Cmd.push_back(Op);
	Cmd.push_back(DestKey);
	_cmd.vCommand(RT_INTEGER, Cmd, Keys, Result, &Result.val);
	return Result;
}

IntResult RedisClient::BitOpAnd(const string& DestKey, const vector<string>& Keys)
{
	return BitOp("AND", DestKey, Keys);
}

IntResult RedisClient::BitOpOr(const string& DestKey, const vector<string>& Keys)
{
	return BitOp("OR", DestKey, Keys);
}

IntResult RedisClient::BitOpXor(const string& DestKey, const vector<string>& Keys)
{
	return BitOp("XOR", DestKey, Keys);
}

IntResult RedisClient::BitOpNot(const string& DestKey, const vector<string>& Keys)
{
	return BitOp("NOT", DestKey, Keys);
}

IntResult RedisClient::Decr(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "decr %s", Key.c_str());
	return Result;
}

IntResult RedisClient::DecrBy(const string& Key, int64_t By)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Key is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "decr %s %lld", Key.c_str(), By);
	return Result;
}

StringResult RedisClient::Get(const string& Key)
{
	StringResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "get %s", Key.c_str());
	return Result;
}

IntResult RedisClient::GetBit(const string& Key, int Offset)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "getbit %s %d", Key.c_str(), Offset);
	return Result;
}

StringResult RedisClient::GetRange(const string& Key, int Start, int End)
{
	StringResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "getrange %s %d %d", Key.c_str(), Start,End);
	return Result;
}

StringResult RedisClient::GetSet(const string& Key, const string& Value)
{
	StringResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "getset %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

IntResult RedisClient::Incr(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "incr %s", Key.c_str());
	return Result;
}

IntResult RedisClient::IncrBy(const string& Key, int64_t Incr)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "incrby %s %lld", Key.c_str(),Incr);
	return Result;
}

FloatResult RedisClient::IncrByFloat(const string& Key, float Incr)
{
	FloatResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_FLOAT, Result, &Result.val, "incrbyfloat %s %f", Key.c_str(), Incr);
	return Result;
}

StringArrayResult RedisClient::MGet(const vector<string>& Keys)
{
	StringArrayResult Result;
	if (Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.vCommand(RT_STRING_ARRAY, "mget", Keys, Result, &Result.val);
	return Result;
}

StatusResult RedisClient::MSet(const vector<pair<string, string> >& KeyValues)
{
	StatusResult Result;
	if (KeyValues.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.vCommand(RT_STATUS, "mget", KeyValues, Result, &Result.val);
	return Result;
}

BoolResult RedisClient::MSetNX(const vector<pair<string, string> >& KeyValues)
{
	BoolResult Result;
	if (KeyValues.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.vCommand(RT_BOOL, "msetnx", KeyValues, Result, &Result.val);
	return Result;
}

StatusResult RedisClient::PSetEX(const string& Key, int64_t MilliSeconds, const string& Val)
{
	StatusResult Result;
	if (Key.empty() || Val.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STATUS, Result, &Result.val, "psetex %s %d %b", Key.c_str(), MilliSeconds, Val.c_str(),Val.size());
	return Result;
}

StatusResult RedisClient::Set(const string& Key, const string& Value)
{
	StatusResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STATUS, Result, &Result.val, "set %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

StatusResult RedisClient::Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time)
{
	StatusResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	string con;
	con = (Unit == em_sec) ? "ex" : "px";
	_cmd.Command(RT_STATUS, Result, &Result.val, "set %s %b %s %d", Key.c_str(), Value.c_str(), Value.size(), con.c_str(), Time);
	return Result;
}

StatusResult RedisClient::Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time, string_set_type Type)
{
	StatusResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	string con;
	con = (Unit == em_sec) ? "ex" : "px";
	string excon;
	excon = (Type == em_set_nx) ? "nx" : "xx";
	_cmd.Command(RT_STATUS, Result, &Result.val, "set %s %b %s %d %s", Key.c_str(), Value.c_str(), Value.size(), con.c_str(), Time, excon.c_str());
	return Result;
}

IntResult RedisClient::SetBit(const string& Key, uint32_t Offset, int64_t NewBitValue)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "setbit %s %d %d", Key.c_str(), Offset, NewBitValue);
	return Result;
}

StatusResult RedisClient::SetEX(const string& Key, int Seconds, const string& Value)
{
	StatusResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STATUS, Result, &Result.val, "setex %s %d %b", Key.c_str(), Seconds, Value.c_str(), Value.size());
	return Result;
}

BoolResult RedisClient::SetNX(const string& Key, const string& Value)
{
	BoolResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "setnx %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

IntResult RedisClient::SetRange(const string& Key, uint32_t Offset, const string& Value)
{
	IntResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "setrange %s %d %b", Key.c_str(), Offset, Value.c_str(), Value.size());
	return Result;
}

IntResult RedisClient::StrLen(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "strlen %s", Key.c_str());
	return Result;
}

IntResult RedisClient::HDel(const string& Key, const vector<string>& Fields)
{
	IntResult Result;
	if (Key.empty() || Fields.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("hdel");
	Cmd.push_back(Key);
	_cmd.vCommand(RT_INTEGER, Cmd, Fields, Result, &Result.val);
	return Result;
}

BoolResult RedisClient::HExists(const string& Key, const string& Field)
{
	BoolResult Result;
	if (Key.empty() || Field.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "hexists %s %s", Key.c_str(),Field.c_str());
	return Result;
}

StringResult RedisClient::HGet(const string& Key, const string& Field)
{
	StringResult Result;
	if (Key.empty() || Field.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "hget %s %s", Key.c_str(),Field.c_str());
	return Result;
}

StringStringMapResult RedisClient::HGetAll(const string& Key)
{
	StringStringMapResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_STRING_MAP, Result, &Result.val, "hgetall %s", Key.c_str());
	return Result;
}

IntResult RedisClient::HIncrBy(const string& Key, const string& Field, int64_t Incr)
{
	IntResult Result;
	if (Key.empty() || Field.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "hincrby %s %s %ld", Key.c_str(),Field.c_str(),Incr);
	return Result;
}

FloatResult RedisClient::HIncrByFloat(const string& Key, const string& Field, float Incr)
{
	FloatResult Result;
	if (Key.empty() || Field.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_FLOAT, Result, &Result.val, "hincrbyfloat %s %s %f", Key.c_str(),Field.c_str(),Incr);
	return Result;
}

StringArrayResult RedisClient::HKeys(const string& Key)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "hkeys %s", Key.c_str());
	return Result;
}

IntResult RedisClient::HLen(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "hlen %s", Key.c_str());
	return Result;
}

StringArrayResult RedisClient::HMGet(const string& Key, const vector<string>& Fields)
{
	StringArrayResult Result;
	if (Key.empty() || Fields.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("hmget");
	Cmd.push_back(Key);
	_cmd.vCommand(RT_STRING_ARRAY, Cmd, Fields, Result, &Result.val);
	return Result;
}

StatusResult RedisClient::HMSet(const string& Key, const vector<pair<string, string> >& FieldVal)
{
	StatusResult Result;
	if (Key.empty() || FieldVal.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("hmset");
	Cmd.push_back(Key);
	_cmd.vCommand(RT_STATUS, Cmd, FieldVal, Result, &Result.val);
	return Result;
}

BoolResult RedisClient::HSet(const string& Key, const string& Field, const string& Value)
{
	BoolResult Result;
	if (Key.empty() || Field.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "hset %s %s %b", Key.c_str(), Field.c_str(), Value.c_str(), Value.size());
	return Result;
}

BoolResult RedisClient::HSetNX(const string& Key, const string& Field, const string& Value)
{
	BoolResult Result;
	if (Key.empty() || Field.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "hsetnx %s %s %b", Key.c_str(), Field.c_str(), Value.c_str(), Value.size());
	return Result;
}

IntResult RedisClient::HStrLen(const string& Key, const string& Field)
{
	IntResult Result;
	if (Key.empty() || Field.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "hstrlen %s %s", Key.c_str(), Field.c_str());
	return Result;
}

StringArrayResult RedisClient::HVals(const string& Key)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "hvals %s", Key.c_str());
	return Result;
}

StringArrayResult RedisClient::BLPop(vector<string>& Keys, int Timeout)
{
	StringArrayResult Result;
	if (Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	Keys.push_back(ToString(Timeout));
	_cmd.vCommand(RT_STRING_ARRAY, "blpop", Keys, Result, &Result.val);
	return Result;
}

StringArrayResult RedisClient::BRPop(vector<string>& Keys, int Timeout)
{
	StringArrayResult Result;
	if (Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	Keys.push_back(ToString(Timeout));
	_cmd.vCommand(RT_STRING_ARRAY, "brpop", Keys, Result, &Result.val);
	return Result;
}

StringArrayResult RedisClient::BRPopLPush(const string& Src, const string& Dst, int Timeout)
{
	StringArrayResult Result;
	if (Src.empty() || Dst.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "brpoplpush %s %s %d", Src.c_str(), Dst.c_str(), Timeout);
	return Result;
}

StringResult RedisClient::LIndex(const string& Key, int64_t index)
{
	StringResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "lindex %s %lld", Key.c_str(), index);
	return Result;
}

IntResult RedisClient::LInsert(const string& Key, const list_insert_type Type, const string& Pivot, const string& Value)
{
	IntResult Result;
	if (Key.empty() || Pivot.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	string stype = (Type == em_insert_before) ? "before" : "after";
	_cmd.Command(RT_INTEGER, Result, &Result.val, "linsert %s %s %b %b", Key.c_str(), stype.c_str(), Pivot.c_str(), Pivot.size(), Value.c_str(), Value.size());
	return Result;
}

IntResult RedisClient::LInsertBefore(const string& Key, const string& Pivot, const string& Value)
{
	return LInsert(Key, em_insert_before, Pivot, Value);
}

IntResult RedisClient::LInsertAfter(const string& Key, const string& Pivot, const string& Value)
{
	return LInsert(Key, em_insert_after, Pivot, Value);
}

IntResult RedisClient::LLen(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "llen %s", Key.c_str());
	return Result;
}

StringResult RedisClient::LPop(const string& Key)
{
	StringResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "lpop %s", Key.c_str());
	return Result;
}

IntResult RedisClient::LPush(const string& Key, const vector<string>& Values)
{
	IntResult Result;
	if (Key.empty() || Values.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("lpush");
	Cmd.push_back(Key);
	_cmd.vCommand(RT_INTEGER, Cmd, Values,Result, &Result.val);
	return Result;
}

IntResult RedisClient::LPushX(const string& Key, const string& Value)
{
	IntResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "lpushx %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

StringArrayResult RedisClient::LRange(const string& Key, int64_t Start, int64_t Stop)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "lrange %s %lld %lld", Key.c_str(), Start, Stop);
	return Result;
}

IntResult RedisClient::LRem(const string& Key, int64_t Count, const string& Value)
{
	IntResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "lrem %s %lld %b", Key.c_str(), Count,Value.c_str(), Value.size());
	return Result;
}

StatusResult RedisClient::LSet(const string& Key, int64_t Index, const string& Value)
{
	StatusResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STATUS, Result, &Result.val, "lset %s %lld %b", Key.c_str(), Index, Value.c_str(), Value.size());
	return Result;
}

StatusResult RedisClient::LTrim(const string& Key, int64_t Start, int64_t End)
{
	StatusResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STATUS, Result, &Result.val, "ltrim %s %lld %lld", Key.c_str(), Start, End);
	return Result;
}

StringResult RedisClient::RPop(const string& Key)
{
	StringResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "rpop %s", Key.c_str());
	return Result;
}

StringResult RedisClient::RPopLPush(const string& Src, const string& Dst)
{
	StringResult Result;
	if (Src.empty() || Dst.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "rpoplpush %s %s", Src.c_str(),Dst.c_str());
	return Result;
}

IntResult RedisClient::RPush(const string& Key, const vector<string>& Values)
{
	IntResult Result;
	if (Key.empty() || Values.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("rpush");
	Cmd.push_back(Key);
	_cmd.vCommand(RT_INTEGER, Cmd, Values, Result, &Result.val);
	return Result;
}

IntResult RedisClient::RPushX(const string& Key, const string& Value)
{
	IntResult Result;
	if (Key.empty() || Value.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "rpushx %s %b", Key.c_str(), Value.c_str(), Value.size());
	return Result;
}

IntResult RedisClient::SAdd(const string& Key, const vector<string>& Members)
{
	IntResult Result;
	if (Key.empty() || Members.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("sadd");
	Cmd.push_back(Key);
	_cmd.vCommand(RT_INTEGER, Cmd, Members, Result, &Result.val);
	return Result;
}

IntResult RedisClient::SCard(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "scard %s", Key.c_str());
	return Result;
}

StringArrayResult RedisClient::SDiff(const vector<string>& Keys)
{
	StringArrayResult Result;
	if (Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.vCommand(RT_STRING_ARRAY, "sdiff", Keys, Result, &Result.val);
	return Result;
}

IntResult RedisClient::SDiffStore(const string& Dst, const vector<string>& Keys)
{
	IntResult Result;
	if (Dst.empty() || Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("sdiffstore");
	Cmd.push_back(Dst);
	_cmd.vCommand(RT_INTEGER, Cmd, Keys, Result, &Result.val);
	return Result;
}

StringArrayResult RedisClient::SInter(const vector<string>& Keys)
{
	StringArrayResult Result;
	if (Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.vCommand(RT_STRING_ARRAY, "sinter", Keys, Result, &Result.val);
	return Result;
}

IntResult RedisClient::SInterStore(const string& Dst, const vector<string>& Keys)
{
	IntResult Result;
	if (Dst.empty() || Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("sinterstore");
	Cmd.push_back(Dst);
	_cmd.vCommand(RT_INTEGER, Cmd, Keys, Result, &Result.val);
	return Result;
}

BoolResult RedisClient::SIsMember(const string& Key, const string& Member)
{
	BoolResult Result;
	if (Key.empty() || Member.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "sismember %s %b", Key.c_str(), Member.c_str(), Member.size());
	return Result;
}

StringArrayResult RedisClient::SMembers(const string& Key)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "smembers %s", Key.c_str());
	return Result;
}

BoolResult RedisClient::SMove(const string& Src, const string& Dst, const string& Member)
{
	BoolResult Result;
	if (Src.empty() || Dst.empty() || Member.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_BOOL, Result, &Result.val, "smove %s %s %b", Src.c_str(), Dst.c_str(), Member.c_str(), Member.size());
	return Result;
}

StringResult RedisClient::SPop(const string& Key)
{
	StringResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "spop %s", Key.c_str());
	return Result;
}

StringArrayResult RedisClient::SPopN(const string& Key, int64_t Count)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "spop %s %lld", Key.c_str(), Count);
	return Result;
}

StringResult RedisClient::SRandMember(const string& Key)
{
	StringResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING, Result, &Result.val, "srandmember %s", Key.c_str());
	return Result;
}

StringArrayResult RedisClient::SRandMemberN(const string& Key, int64_t Count)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "srandmember %s %lld", Key.c_str(), Count);
	return Result;
}

IntResult RedisClient::SRem(const string& Key, const vector<string>& Members)
{
	IntResult Result;
	if (Key.empty() || Members.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("srem");
	Cmd.push_back(Key);
	_cmd.vCommand(RT_INTEGER, Cmd, Members, Result, &Result.val);
	return Result;
}

StringArrayResult RedisClient::SUnion(const vector<string>& Keys)
{
	StringArrayResult Result;
	if (Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.vCommand(RT_STRING_ARRAY, "sunion", Keys, Result, &Result.val);
	return Result;
}

IntResult RedisClient::SUnionStore(const string& Dst, const vector<string>& Keys)
{
	IntResult Result;
	if (Dst.empty() || Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("sunionstore");
	Cmd.push_back(Dst);
	_cmd.vCommand(RT_INTEGER, Cmd, Keys, Result, &Result.val);
	return Result;
}

IntResult RedisClient::ZAdd(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	IntResult Result;
	if (Key.empty() || ScoreMem.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	_cmd.vCommand(RT_INTEGER, Cmd, ScoreMem, Result, &Result.val);
	return Result;
}

IntResult RedisClient::ZAddNX(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	IntResult Result;
	if (Key.empty() || ScoreMem.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("NX");
	_cmd.vCommand(RT_INTEGER, Cmd, ScoreMem, Result, &Result.val);
	return Result;
}

IntResult RedisClient::ZAddXX(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	IntResult Result;
	if (Key.empty() || ScoreMem.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("XX");
	_cmd.vCommand(RT_INTEGER, Cmd, ScoreMem, Result, &Result.val);
	return Result;
}

IntResult RedisClient::ZAddCh(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	IntResult Result;
	if (Key.empty() || ScoreMem.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("CH");
	_cmd.vCommand(RT_INTEGER, Cmd, ScoreMem, Result, &Result.val);
	return Result;
}

IntResult RedisClient::ZAddNXCh(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	IntResult Result;
	if (Key.empty() || ScoreMem.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("NX");
	Cmd.push_back("CH");
	_cmd.vCommand(RT_INTEGER, Cmd, ScoreMem, Result, &Result.val);
	return Result;
}

IntResult RedisClient::ZAddXXCh(const string& Key, const vector<pair<float, string> >& ScoreMem)
{
	IntResult Result;
	if (Key.empty() || ScoreMem.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zadd");
	Cmd.push_back(Key);
	Cmd.push_back("XX");
	Cmd.push_back("CH");
	_cmd.vCommand(RT_INTEGER, Cmd, ScoreMem, Result, &Result.val);
	return Result;
}

IntResult RedisClient::ZCard(const string& Key)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "zcard %s", Key.c_str());
	return Result;
}

IntResult RedisClient::ZCount(const string& Key, const string& Min, const string& Max)
{
	IntResult Result;
	if (Key.empty() || Min.empty() || Max.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "zcount %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

FloatResult RedisClient::ZincrBy(const string& Key, const float Incr, const string& Member)
{
	FloatResult Result;
	if (Key.empty() || Member.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_FLOAT, Result, &Result.val, "zincrby %s %f %s", Key.c_str(), Incr, Member.c_str());
	return Result;
}

IntResult RedisClient::ZlexCount(const string& Key, const string& Min, const string& Max)
{
	IntResult Result;
	if (Key.empty() || Min.empty() || Max.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "zlexcount %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

StringArrayResult RedisClient::ZRange(const string& Key, int64_t Start, int64_t End)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrange %s %lld %lld", Key.c_str(), Start, End);
	return Result;
}

StringFloatMapResult RedisClient::ZRangeWithScores(const string& Key, int64_t Start, int64_t End)
{
	StringFloatMapResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_FLOAT_MAP, Result, &Result.val, "zrange %s %lld %lld withscores", Key.c_str(), Start, End);
	return Result;
}

StringArrayResult RedisClient::ZRangeByLex(const string& Key, const string& Min, const string& Max)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrangebylex %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

StringArrayResult RedisClient::ZRangeByLex(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrangebylex %s %s %s limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

StringArrayResult RedisClient::ZRangeByScore(const string& Key, const string& Min, const string& Max)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrangebyscore %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

StringArrayResult RedisClient::ZRangeByScore(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrangebyscore %s %s %s limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

StringFloatMapResult RedisClient::ZRangeByScoreWithScores(const string& Key, const string& Min, const string& Max)
{
	StringFloatMapResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_FLOAT_MAP, Result, &Result.val, "zrangebyscore %s %s %s withscores", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

StringFloatMapResult RedisClient::ZRangeByScoreWithScores(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	StringFloatMapResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_FLOAT_MAP, Result, &Result.val, "zrangebyscore %s %s %s withscores limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

IntResult RedisClient::ZRank(const string& Key, const string& Member)
{
	IntResult Result;
	if (Key.empty() || Member.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "zrank %s %s", Key.c_str(), Member.c_str());
	return Result;
}

IntResult RedisClient::ZRem(const string& Key, const vector<string>& Members)
{
	IntResult Result;
	if (Key.empty() || Members.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zrem");
	Cmd.push_back(Key);
	_cmd.vCommand(RT_INTEGER, Cmd, Members, Result, &Result.val);
	return Result;
}

IntResult RedisClient::ZRemRangeByLex(const string& Key, const string& Min, const string& Max)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "zremrangebylex %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

IntResult RedisClient::ZRemRangeByRank(const string& Key, int64_t Start, int64_t End)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "zremrangebyrank %s %lld %lld", Key.c_str(), Start, End);
	return Result;
}

IntResult RedisClient::ZRemRangeByScore(const string& Key, const string& Min, const string& Max)
{
	IntResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "zremrangebyscore %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

StringArrayResult RedisClient::ZRevRange(const string& Key, int64_t Start, int64_t End)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrevrange %s %lld %lld", Key.c_str(), Start, End);
	return Result;
}

StringFloatMapResult RedisClient::ZRevRangeWithScores(const string& Key, int64_t Start, int64_t End)
{
	StringFloatMapResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_FLOAT_MAP, Result, &Result.val, "zrevrange %s %lld %lld withscores", Key.c_str(), Start, End);
	return Result;
}

StringArrayResult RedisClient::ZRevRangeByLex(const string& Key, const string& Min, const string& Max)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrevrangebylex %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

StringArrayResult RedisClient::ZRevRangeByLex(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrevrangebylex %s %s %s limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

StringArrayResult RedisClient::ZRevRangeByScore(const string& Key, const string& Min, const string& Max)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrevrangebyscore %s %s %s", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

StringArrayResult RedisClient::ZRevRangeByScore(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	StringArrayResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_ARRAY, Result, &Result.val, "zrevrangebyscore %s %s %s limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

StringFloatMapResult RedisClient::ZRevRangeByScoreWithScores(const string& Key, const string& Min, const string& Max)
{
	StringFloatMapResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_FLOAT_MAP, Result, &Result.val, "zrevrangebyscore %s %s %s withscores", Key.c_str(), Min.c_str(), Max.c_str());
	return Result;
}

StringFloatMapResult RedisClient::ZRevRangeByScoreWithScores(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count)
{
	StringFloatMapResult Result;
	if (Key.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_STRING_FLOAT_MAP, Result, &Result.val, "zrevrangebyscore %s %s %s withscores limit %lld %lld", Key.c_str(), Min.c_str(), Max.c_str(), Offset, Count);
	return Result;
}

IntResult RedisClient::ZRevRank(const string& Key, const string& Member)
{
	IntResult Result;
	if (Key.empty() || Member.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_INTEGER, Result, &Result.val, "zrevrank %s %s", Key.c_str(), Member.c_str());
	return Result;
}

FloatResult RedisClient::Zscore(const string& Key, const string& Member)
{
	FloatResult Result;
	if (Key.empty() || Member.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	_cmd.Command(RT_FLOAT, Result, &Result.val, "zscore %s %s", Key.c_str(), Member.c_str());
	return Result;
}

IntResult RedisClient::ZunionStore(const string& Dst, vector<string>& Keys, const string &Aggregate /*= "SUM"*/)
{
	IntResult Result;
	if (Dst.empty() || Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	vector<string> Cmd;
	Cmd.push_back("zunionstore");
	Cmd.push_back(Dst);
	Cmd.push_back(ToString(Keys.size()));
	Keys.push_back(Aggregate);
	_cmd.vCommand(RT_INTEGER, Cmd, Keys, Result, &Result.val);
	return Result;
}

IntResult RedisClient::ZunionStoreWeights(const string& Dst, vector<string>& Keys, const vector<float>& Weights, const string &Aggregate /*= "SUM"*/)
{
	IntResult Result;
	if (Dst.empty() || Keys.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
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
	_cmd.vCommand(RT_INTEGER, Cmd, Keys, Result, &Result.val);
	return Result;
}

redisReply* RedisClient::RawCommand(const char* Cmd, ...)
{
	redisContext* Ctx = nullptr;
	redisReply *reply = nullptr;
	// to do maxretry
	for (int i = 0; i<2; i++)
	{
		RedisCtxGuard CtxGuard(&_cmd.GetConnPool());
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
		if (reply)
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

redisReply* RedisClient::RawCommandv(const vector<string> &Cmd)
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
	// to do maxretry
	for (int i = 0; i<2; i++)
	{
		RedisCtxGuard CtxGuard(&_cmd.GetConnPool());
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
			break;
		}
		else
		{
			CtxGuard.GetConn()->SetStatus(CS_UNCONNECTED);
		}
	}
	return reply;
}