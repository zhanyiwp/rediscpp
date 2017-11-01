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

BoolResult RedisClient::Pexpire(const string& Key, uint32_t MilliSec)
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

BoolResult RedisClient::Pexpireat(const string&Key, uint64_t Timestamp)
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

BoolResult RedisClient::Renamenx(const string& Key, const string& NewKey)
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
	//to do 省掉这次复制
	vector<string> Cmd;
	Cmd.push_back(Op);
	Cmd.push_back(DestKey);
	vector<string>::const_iterator it = Keys.begin();
	for (; it != Keys.end(); ++it)
	{
		Cmd.push_back(*it);
	}
	_cmd.vCommand(RT_INTEGER, "bitop", Cmd, Result, &Result.val);
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

IntResult RedisClient::Decrby(const string& Key, int64_t By)
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

StringArrayResult RedisClient::Mget(const vector<string>& Keys)
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

#if 1
StatusResult RedisClient::Mset(const map<string, string>& KeyValues)
{
	StatusResult Result;
	if (KeyValues.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	
	// to do 省掉这次复制
	vector<string> Cmd;
	map<string, string>::const_iterator it = KeyValues.begin();
	for (; it != KeyValues.end(); ++it)
	{
		Cmd.push_back(it->first);
		Cmd.push_back(it->second);
	}
	_cmd.vCommand(RT_STATUS, "mget", Cmd, Result, &Result.val);
	return Result;
}

BoolResult RedisClient::MsetNx(const map<string, string>& KeyValues)
{
	BoolResult Result;
	if (KeyValues.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	// to do 省掉这次复制
	vector<string> Cmd;
	map<string, string>::const_iterator it = KeyValues.begin();
	for (; it != KeyValues.end(); ++it)
	{
		Cmd.push_back(it->first);
		Cmd.push_back(it->second);
	}
	_cmd.vCommand(RT_BOOL, "msetnx", Cmd, Result, &Result.val);
	return Result;
}

StatusResult RedisClient::PsetEx(const string& Key, int64_t MilliSeconds, const string& Val)
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

StatusResult RedisClient::SetEx(const string& Key, int Seconds, const string& Value)
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

BoolResult RedisClient::SetNx(const string& Key, const string& Value)
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

IntResult RedisClient::Strlen(const string& Key)
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

IntResult RedisClient::Hdel(const string& Key, const vector<string>& Fields)
{
	IntResult Result;
	if (Key.empty() || Fields.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	// to do 省掉复制
	vector<string> Cmd;
	Cmd.push_back(Key);
	vector<string>::const_iterator it = Fields.begin();
	for (; it != Fields.end(); ++it)
	{
		Cmd.push_back(*it);
	}
	_cmd.vCommand(RT_INTEGER, "hdel", Cmd, Result, &Result.val);
	return Result;
}

BoolResult RedisClient::Hexists(const string& Key, const string& Field)
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

StringResult RedisClient::Hget(const string& Key, const string& Field)
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

StringStringMapResult RedisClient::HgetAll(const string& Key)
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

IntResult RedisClient::HincrBy(const string& Key, const string& Field, int64_t Incr)
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

FloatResult RedisClient::HincrByFloat(const string& Key, const string& Field, float Incr)
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

StringArrayResult RedisClient::Hkeys(const string& Key)
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

IntResult RedisClient::Hlen(const string& Key)
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

StringArrayResult RedisClient::Hmget(const string& Key, const vector<string>& Fields)
{
	StringArrayResult Result;
	if (Key.empty() || Fields.empty())
	{
		Result.Set(CMD_OPERATE_FAILED, "Keys is empty");
		return Result;
	}
	// to do 省掉复制
	vector<string> Cmd;
	Cmd.push_back(Key);
	vector<string>::const_iterator it = Fields.begin();
	for (; it != Fields.end(); ++it)
	{
		Cmd.push_back(*it);
	}
	_cmd.vCommand(RT_STRING_ARRAY, "hmget", Cmd, Result, &Result.val);
	return Result;
}

int RedisClient::hmset(const string& key, const vector<pair<string, string> >& field_val, void *data)
{
	if (key.empty() || field_val.empty())
	{
		return -1;
	}
	printf("call hmset %s key \n", key.c_str());
	vector<string> cmd;
	cmd.push_back("hmset");
	cmd.push_back(key);
	vector<pair<string, string> >::const_iterator it = field_val.begin();
	for (; it != field_val.end(); ++it)
	{
		cmd.push_back(it->first);
		cmd.push_back(it->second);
	}
	return m_pcmd->exec_commandargv(em_status_reply, data, cmd);
}

int RedisClient::hset(const string& key, const string& field, const string& value, void *data)
{
	if (key.empty() || field.empty() || value.empty())
	{
		return -1;
	}
	printf("call hset %s key \n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "hset %s %s %b", key.c_str(), field.c_str(), value.c_str(), value.size());
}

int RedisClient::hsetnx(const string& key, const string& field, const string& value, void *data)
{
	if (key.empty() || field.empty() || value.empty())
	{
		return -1;
	}
	printf("call hsetnx %s key \n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "hsetnx %s %s %b", key.c_str(), field.c_str(), value.c_str(), value.size());
}

int RedisClient::hvals(const string& key, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call hvals %s key \n", key.c_str());
	return m_pcmd->exec_command(em_slist_relpy, data, "hvals %s", key.c_str());
}

int RedisClient::blpop(const vector<string>& keys, int timeout, void *data)
{
	if (keys.empty())
	{
		return -1;
	}
	printf("call blpop\n");
	vector<string> cmd;
	cmd.push_back("blpop");
	vector<string>::const_iterator it = keys.begin();
	for (; it != keys.end(); ++it)
	{
		cmd.push_back(*it);
	}
	cmd.push_back(tostring(timeout));
	return m_pcmd->exec_commandargv(em_ss_map_reply, data, cmd);
}

int RedisClient::brpop(const vector<string>& keys, int timeout, void *data)
{
	if (keys.empty())
	{
		return -1;
	}
	printf("call brpop\n");
	vector<string> cmd;
	cmd.push_back("brpop");
	vector<string>::const_iterator it = keys.begin();
	for (; it != keys.end(); ++it)
	{
		cmd.push_back(*it);
	}
	cmd.push_back(tostring(timeout));
	return m_pcmd->exec_commandargv(em_ss_map_reply, data, cmd);
}

int RedisClient::brpoplpush(const string& src, const string& dst, int timeout, void *data)
{
	if (src.empty() || dst.empty())
	{
		return -1;
	}
	printf("call brpoplpush %s key \n", src.c_str());
	return m_pcmd->exec_command(em_string_relpy, data, "brpoplpush %s %s %d", src.c_str(), dst.c_str(), timeout);
}

int RedisClient::lindex(const string& key, int64_t index, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call lindex %s key \n", key.c_str());
	return m_pcmd->exec_command(em_string_relpy, data, "lindex %s %lld", key.c_str(), index);
}

int RedisClient::linsert(const string& key, const list_insert_type type, const string& pivot, const string& value, void *data)
{
	if (key.empty() || pivot.empty() || value.empty())
	{
		return -1;
	}
	printf("call linsert %s key \n", key.c_str());
	string stype = (type == em_insert_before) ? "before" : "after";
	return m_pcmd->exec_command(em_integer_relpy, data, "linsert %s %s %s %b", key.c_str(), stype.c_str(), pivot.c_str(), value.c_str(), value.size());
}

int RedisClient::llen(const string& key, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call llen %s key \n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "llen %s", key.c_str());
}

int RedisClient::lpop(const string& key, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call lpop %s key \n", key.c_str());
	return m_pcmd->exec_command(em_string_relpy, data, "lpop %s", key.c_str());
}

int RedisClient::lpush(const string& key, const vector<string>& values, void *data)
{
	if (key.empty() || values.empty())
	{
		return -1;
	}
	printf("call lpush %s key \n", key.c_str());
	vector<string> cmd;
	cmd.push_back("lpush");
	cmd.push_back(key);
	vector<string>::const_iterator it = values.begin();
	for (; it != values.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy, data, cmd);
}

int RedisClient::lpushx(const string& key, const string& value, void *data)
{
	if (key.empty() || value.empty())
	{
		return -1;
	}
	printf("call lpushx %s key \n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "lpushx %s %b", key.c_str(), value.c_str(), value.size());
}

int RedisClient::lrange(const string& key, int64_t start, int64_t stop, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call lrange %s key \n", key.c_str());
	return m_pcmd->exec_command(em_slist_relpy, data, "lrange %s %lld %lld", key.c_str(), start, stop);
}

int RedisClient::lrem(const string& key, int count, const string& value, void *data)
{
	if (key.empty() || value.empty())
	{
		return -1;
	}
	printf("call lrem %s key \n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "lrem %s %d %b", key.c_str(), count, value.c_str(), value.size());
}

int RedisClient::lset(const string& key, int index, const string& value, void *data)
{
	if (key.empty() || value.empty())
	{
		return -1;
	}
	printf("call lset %s key \n", key.c_str());
	return m_pcmd->exec_command(em_status_reply, data, "lset %s %d %b", key.c_str(), index, value.c_str(), value.size());
}

int RedisClient::ltrim(const string& key, int start, int end, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call ltrim %s key \n", key.c_str());
	return m_pcmd->exec_command(em_status_reply, data, "ltrim %s %d %d", key.c_str(), start, end);
}

int RedisClient::rpop(const string& key, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call rpop %s key \n", key.c_str());
	return m_pcmd->exec_command(em_string_relpy, data, "rpop %s", key.c_str());
}

int RedisClient::rpoplpush(const string& src, const string& dst, void *data)
{
	if (src.empty() || dst.empty())
	{
		return -1;
	}
	printf("call rpoplpush %s key \n", src.c_str());
	return m_pcmd->exec_command(em_string_relpy, data, "rpoplpush %s %s", src.c_str(), dst.c_str());
}

int RedisClient::rpush(const string& key, const vector<string>& values, void *data)
{
	if (key.empty() || values.empty())
	{
		return -1;
	}
	printf("call rpush %s key \n", key.c_str());
	vector<string> cmd;
	cmd.push_back("rpush");
	cmd.push_back(key);
	vector<string>::const_iterator it = values.begin();
	for (; it != values.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy, data, cmd);
}

int RedisClient::rpushx(const string& key, const string& value, void *data)
{
	if (key.empty() || value.empty())
	{
		return -1;
	}
	printf("call rpushx %s key \n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "rpushx %s %b", key.c_str(), value.c_str(), value.size());
}

int RedisClient::sadd(const string& key, const vector<string>& members, void *data)
{
	if (key.empty() || members.empty())
	{
		return -1;
	}
	printf("call sadd %s key \n", key.c_str());
	vector<string> cmd;
	cmd.push_back("sadd");
	cmd.push_back(key);
	vector<string>::const_iterator it = members.begin();
	for (; it != members.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy, data, cmd);
}

int RedisClient::scard(const string& key, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call scard %s key \n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "scard %s", key.c_str());
}

int RedisClient::sdiff(const vector<string>& keys, void *data)
{
	if (keys.empty())
	{
		return -1;
	}
	printf("call sdiff \n");
	vector<string> cmd;
	cmd.push_back("sdiff");
	vector<string>::const_iterator it = keys.begin();
	for (; it != keys.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_slist_relpy, data, cmd);
}

int RedisClient::sdiffstore(const string& dst, const vector<string>& keys, void *data)
{
	if (dst.empty() || keys.empty())
	{
		return -1;
	}
	printf("call sdiffstore \n");
	vector<string> cmd;
	cmd.push_back("sdiffstore");
	cmd.push_back(dst);
	vector<string>::const_iterator it = keys.begin();
	for (; it != keys.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy, data, cmd);
}

int RedisClient::sinter(const vector<string>& keys, void *data)
{
	if (keys.empty())
	{
		return -1;
	}
	printf("call sinter \n");
	vector<string> cmd;
	cmd.push_back("sinter");
	vector<string>::const_iterator it = keys.begin();
	for (; it != keys.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_slist_relpy, data, cmd);
}

int RedisClient::sinterstore(const string& dst, const vector<string>& keys, void *data)
{
	if (dst.empty() || keys.empty())
	{
		return -1;
	}
	printf("call sinterstore \n");
	vector<string> cmd;
	cmd.push_back("sinterstore");
	cmd.push_back(dst);
	vector<string>::const_iterator it = keys.begin();
	for (; it != keys.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy, data, cmd);
}

int RedisClient::sismember(const string& key, const string& member, void *data)
{
	if (key.empty() || member.empty())
	{
		return -1;
	}
	printf("call sismember %s key \n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "sismember %s %s", key.c_str(), member.c_str());
}

int RedisClient::smembers(const string& key, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call smembers %s key \n", key.c_str());
	return m_pcmd->exec_command(em_slist_relpy, data, "smembers %s", key.c_str());
}

int RedisClient::smove(const string& src, const string& dst, const string& member, void *data)
{
	if (src.empty() || dst.empty() || member.empty())
	{
		return -1;
	}
	printf("call smove %s key \n", src.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "smove %s %s %s", src.c_str(), dst.c_str(), member.c_str());
}

int RedisClient::spop(const string& key, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call spop %s key \n", key.c_str());
	return m_pcmd->exec_command(em_string_relpy, data, "spop %s", key.c_str());
}

int RedisClient::srandmember(const string& key, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call srandmember %s key \n", key.c_str());
	return m_pcmd->exec_command(em_string_relpy, data, "srandmember %s", key.c_str());
}

int RedisClient::srandmember(const string& key, int count, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call srandmember %s %d \n", key.c_str(), count);
	return m_pcmd->exec_command(em_slist_relpy, data, "srandmember %s %d", key.c_str(), count);
}

int RedisClient::srem(const string& key, const vector<string>& members, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call srem %s key \n", key.c_str());
	vector<string> cmd;
	cmd.push_back("srem");
	cmd.push_back(key);
	vector<string>::const_iterator it = members.begin();
	for (; it != members.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy, data, cmd);
}

int RedisClient::sunion(const vector<string>& keys, void *data)
{
	if (keys.empty())
	{
		return -1;
	}
	printf("call sunion \n");
	vector<string> cmd;
	cmd.push_back("sunion");
	vector<string>::const_iterator it = keys.begin();
	for (; it != keys.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_slist_relpy, data, cmd);
}

int RedisClient::sunionstore(const string& dst, const vector<string>& keys, void *data)
{
	if (dst.empty() || keys.empty())
	{
		return -1;
	}
	printf("call sunionstore \n");
	vector<string> cmd;
	cmd.push_back("sunionstore");
	cmd.push_back(dst);
	vector<string>::const_iterator it = keys.begin();
	for (; it != keys.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy, data, cmd);
}

int RedisClient::zadd(const string& key, const vector<pair<float, string> >& score_mem, void *data)
{
	if (key.empty() || score_mem.empty())
	{
		return -1;
	}
	printf("call zadd %s key \n", key.c_str());
	vector<string> cmd;
	cmd.push_back("zadd");
	cmd.push_back(key);
	vector<pair<float, string> >::const_iterator it = score_mem.begin();
	for (; it != score_mem.end(); ++it)
	{
		cmd.push_back(tostring(it->first));
		cmd.push_back(it->second);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy, data, cmd);
}

int RedisClient::zcard(const string& key, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call zcard %s\n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "zcard %s", key.c_str());
}

int RedisClient::zcount(const string& key, const string& min, const string& max, void *data)
{
	if (key.empty() || min.empty() || max.empty())
	{
		return -1;
	}
	printf("call zcount %s\n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "zcount %s %s %s", key.c_str(), min.c_str(), max.c_str());
}

int RedisClient::zincrby(const string& key, const double incr, const string& member, void *data)
{
	if (key.empty() || member.empty())
	{
		return -1;
	}
	printf("call zincrby %s\n", key.c_str());
	return m_pcmd->exec_command(em_double_relpy, data, "zincrby %s %f %s", key.c_str(), incr, member.c_str());
}

int RedisClient::zrange(const string& key, int start, int end, void *data, bool withscores /*= false*/)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call zrange %s\n", key.c_str());
	if (withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply, data, "zrange %s %d %d %s", key.c_str(), start, end, "withscores");
	}
	return m_pcmd->exec_command(em_slist_relpy, data, "zrange %s %d %d", key.c_str(), start, end);
}


int RedisClient::zrangebyscore(const string& key, const string& min, const string& max, void *data, bool withscores /*= false*/)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call zrangebyscore %s\n", key.c_str());
	if (withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply, data, "zrangebyscore %s %s %s %s", key.c_str(), min.c_str(), max.c_str(), "withscores");
	}
	return m_pcmd->exec_command(em_slist_relpy, data, "zrangebyscore %s %s %s", key.c_str(), min.c_str(), max.c_str());
}

int RedisClient::zrangebyscore(const string& key, const string& min, const string& max, int offset, int count, void *data, bool withscores /*= false*/)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call zrangebyscore with limit %s\n", key.c_str());
	if (withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply, data, "zrangebyscore %s %s %s %s limit %d %d", key.c_str(), min.c_str(), max.c_str(), "withscores", offset, count);
	}
	return m_pcmd->exec_command(em_slist_relpy, data, "zrangebyscore %s %s %s limit %d %d", key.c_str(), min.c_str(), max.c_str(), offset, count);
}

int RedisClient::zrank(const string& key, const string& member, void *data)
{
	if (key.empty() || member.empty())
	{
		return -1;
	}
	printf("call zrank %s\n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "zrank %s %s", key.c_str(), member.c_str());
}

int RedisClient::zrem(const string& key, const vector<string>& members, void *data)
{
	if (key.empty() || members.empty())
	{
		return -1;
	}
	printf("call zrem %s key\n", key.c_str());
	vector<string> cmd;
	cmd.push_back("zrem");
	cmd.push_back(key);
	vector<string>::const_iterator it = members.begin();
	for (; it != members.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy, data, cmd);
}

int RedisClient::zremrangebyrank(const string& key, int start, int stop, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call zremrangebyrank %s\n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "zremrangebyrank %s %d %d", key.c_str(), start, stop);
}

int RedisClient::zremrangebyscore(const string& key, const string& min, const string& max, void *data)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call zremrangebyscore %s\n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "zremrangebyscore %s %s %s", key.c_str(), min.c_str(), max.c_str());
}

int RedisClient::zrevrange(const string& key, int start, int stop, void *data, bool withscores /*= false*/)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call zrevrange %s\n", key.c_str());
	if (withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply, data, "zrevrange %s %d %d %s", key.c_str(), start, stop, "withscores");
	}
	return m_pcmd->exec_command(em_slist_relpy, data, "zrevrange %s %d %d", key.c_str(), start, stop);
}

int RedisClient::zrevrangebyscore(const string& key, const string& min, const string& max, void *data, bool withscores /*= false*/)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call zrevrangebyscore %s\n", key.c_str());
	if (withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply, data, "zrevrangebyscore %s %s %s %s", key.c_str(), min.c_str(), max.c_str(), "withscores");
	}
	return m_pcmd->exec_command(em_slist_relpy, data, "zrevrangebyscore %s %s %s", key.c_str(), min.c_str(), max.c_str());
}

int RedisClient::zrevrangebyscore(const string& key, const string& min, const string& max, int offset, int count, void *data, bool withscores /*= false*/)
{
	if (key.empty())
	{
		return -1;
	}
	printf("call zrevrangebyscore with limit %s\n", key.c_str());
	if (withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply, data, "zrevrangebyscore %s %s %s %s limit %d %d", key.c_str(), min.c_str(), max.c_str(), "withscores", offset, count);
	}
	return m_pcmd->exec_command(em_slist_relpy, data, "zrevrangebyscore %s %s %s limit %d %d", key.c_str(), min.c_str(), max.c_str(), offset, count);
}

int RedisClient::zrevrank(const string& key, const string& member, void *data)
{
	if (key.empty() || member.empty())
	{
		return -1;
	}
	printf("call zrevrank %s\n", key.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "zrevrank %s %s", key.c_str(), member.c_str());
}

int RedisClient::zscore(const string& key, const string& member, void *data)
{
	if (key.empty() || member.empty())
	{
		return -1;
	}
	printf("call zscore %s\n", key.c_str());
	return m_pcmd->exec_command(em_double_relpy, data, "zscore %s %s", key.c_str(), member.c_str());
}

int RedisClient::publish(const string& channel, const string& message, void *data)
{
	if (channel.empty() || message.empty())
	{
		return -1;
	}
	printf("call publish %s %s\n", channel.c_str(), message.c_str());
	return m_pcmd->exec_command(em_integer_relpy, data, "publish %s %b", channel.c_str(), message.c_str(), message.size());
}

int RedisClient::psubscribe(const vector<string>& pattern, void *data)
{
	if (pattern.empty())
	{
		return -1;
	}
	printf("call psubscribe \n");
	vector<string> cmd;
	cmd.push_back("psubscribe");
	vector<string>::const_iterator it = pattern.begin();
	for (; it != pattern.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply, data, cmd);
}

int RedisClient::subscribe(const vector<string>& channels, void *data)
{
	if (channels.empty())
	{
		return -1;
	}
	printf("call subscribe \n");
	vector<string> cmd;
	cmd.push_back("subscribe");
	vector<string>::const_iterator it = channels.begin();
	for (; it != channels.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply, data, cmd);
}

int RedisClient::punsubscribe(const vector<string>& pattern, void *data)
{
	printf("call punsubscribe \n");
	vector<string> cmd;
	cmd.push_back("punsubscribe");
	vector<string>::const_iterator it = pattern.begin();
	for (; it != pattern.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply, data, cmd);
}

int RedisClient::unsubscribe(const vector<string>& pattern, void *data)
{
	printf("call unsubscribe \n");
	vector<string> cmd;
	cmd.push_back("unsubscribe");
	vector<string>::const_iterator it = pattern.begin();
	for (; it != pattern.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply, data, cmd);
}

int RedisClient::pubsub_channels(const string& channel, void *data)
{
	printf("call pubsub_channels %s\n", channel.c_str());
	if (channel.empty())
	{
		return m_pcmd->exec_command(em_slist_relpy, data, "pubsub channels");
	}
	return m_pcmd->exec_command(em_slist_relpy, data, "pubsub channels %s", channel.c_str());
}

int RedisClient::pubsub_numsub(const vector<string>& channels, void *data)
{
	printf("call pubsub_numsub\n");
	vector<string> cmd;
	cmd.push_back("pubsub");
	cmd.push_back("numsub");
	vector<string>::const_iterator it = channels.begin();
	for (; it != channels.end(); ++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply, data, cmd);
}

int RedisClient::pubsub_numpat(void *data)
{
	printf("call pubsub_numpat \n");
	return m_pcmd->exec_command(em_integer_relpy, data, "pubsub numpat");
}

int RedisClient::raw_redis_cmd(reply_type type, void *data, const char* cmd, ...)
{
	redisCallbackFn *fn = m_pcmd->get_callback(type);
	if (!fn)
	{
		printf("unknow reply type %d\n", type);
		return -1;
	}
	connection *pconn = m_pcmd->get_conn();
	if (!pconn)
	{
		printf("get connection failed \n");
		return -1;
	}
	if (!pconn->valid_conn()) //连接无效
	{
		printf("connection invalid \n");
		pconn->try_connect();
		return -1;
	}
	redisAsyncContext* ac = pconn->get_redis_cx();
	va_list ap;
	int status;
	va_start(ap, cmd);
	status = redisvAsyncCommand(ac, fn, data, cmd, ap);
	va_end(ap);
	return status;
}

int RedisClient::raw_redis_cmdargv(reply_type type, const vector<string> &cmd, void *data)
{
	return m_pcmd->exec_commandargv(type, data, cmd);
}
#endif