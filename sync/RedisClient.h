#include "RedisCmd.h"
#include <vector>
#include <map>

#pragma once

using namespace std;

enum expire_unit
{
	em_sec = 0,
	em_msec = 1
};

enum string_set_type
{
	em_set_nx = 0,
	em_set_xx = 1
};

enum list_insert_type
{
	em_insert_before = 0,
	em_insert_after = 1
};

class RedisClient
{
public:
	RedisClient(RedisOpt &Opt);
	~RedisClient();
	// del cmd 
	IntResult Del(const vector<string>& Keys);

	// dump cmd
	StringResult Dump(const string& Key);

	// exists cmd
	BoolResult Exists(const string& Key);

	// expire cmd 
	BoolResult Expire(const string& Key, uint32_t Seconds);

	// expireat cmd
	BoolResult ExpireAt(const string& Key, uint64_t Timestamp);

	// keys cmd
	StringArrayResult Keys(const string& Pattern);

	//BaseResult Migrate(const string& Host, const uint16_t Port, const string& Key, const string& Dest_db, uint32_t Timeout,bool copy = false, bool replace = false);
	//BaseResult Move(const string& Key, const string& Db);
	//BaseResult Object(const string& subcommand, const vector<string>& args);

	// persist cmd
	BoolResult Persist(const string& Key);

	// pexpire cmd
	BoolResult Pexpire(const string& Key, uint32_t MilliSec);

	// pexpireat cmd
	BoolResult Pexpireat(const string&Key, uint64_t Timestamp);

	// pttl cmd 
	IntResult PTTL(const string& Key);

	// randomkey cmd
	StringResult RandomKey();

	// rename cmd
	StatusResult Rename(const string& Key, const string& NewKey);

	// renamenx cmd
	BoolResult Renamenx(const string& Key, const string& NewKey);

	// restore cmd
	StatusResult Restore(const string& Key, int64_t TTL, const string& SerializedValue, bool Repalce = false);

	//StringArrayResult Sort(const string& Key);

	// ttl cmd
	IntResult TTL(const string& Key);

	// type cmd
	StringResult Type(const string& Key);

	// scan cmd
	//BaseResult Scan(const string& Key);

	/***********************string cmd*****************************/

	// append cmd 
	IntResult Append(const string& Key, const string& Value);

	// bitcount cmd
	IntResult BitCount(const string& Key);
	IntResult BitCount(const string& Key, int Start, int End);

	//bitfield
	//BaseResult BitField(const string& Key);

	// bitop cmd op must in {"AND","OR","XOR","NOT"} 
	IntResult BitOp(const string& Op, const string& DestKey, const vector<string>& Keys);
	IntResult BitOpAnd(const string& DestKey, const vector<string>& Keys);
	IntResult BitOpOr(const string& DestKey, const vector<string>& Keys);
	IntResult BitOpXor(const string& DestKey, const vector<string>& Keys);
	IntResult BitOpNot(const string& DestKey, const vector<string>& Keys);

	// bitpos cmd 
	//IntResult Bitpos(const string& Key, int Bit, int64_t& Pos, int Start = 0, int End = 0);

	// decr cmd 
	IntResult Decr(const string& Key);

	// decrby cmd
	IntResult Decrby(const string& Key, int64_t By);

	// get cmd
	StringResult Get(const string& Key);

	// getbit cmd
	IntResult GetBit(const string& Key, int Offset);

	// getrange cmd
	StringResult GetRange(const string& Key, int Start, int End);

	// getset cmd
	StringResult GetSet(const string& Key, const string& Value);

	// incr cmd 
	IntResult Incr(const string& Key);

	// incrby cmd 
	IntResult IncrBy(const string& Key, int64_t Incr);

	// incrbyfloat cmd
	FloatResult IncrByFloat(const string& Key, float Incr);

	// mget cmd
	StringArrayResult Mget(const vector<string>& Keys);

#if 1
	// mset cmd
	StatusResult Mset(const map<string, string>& KeyValues);

	// mset cmd
	BoolResult MsetNx(const map<string, string>& KeyValues);

	// psetex cmd
	StatusResult PsetEx(const string& Key, int64_t MilliSeconds, const string& Val);

	// set cmd
	StatusResult Set(const string& Key, const string& Value);
	StatusResult Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time);
	StatusResult Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time, string_set_type Type);

	// setbit 
	IntResult SetBit(const string& Key, uint32_t Offset, int64_t NewBitValue);

	// setex 
	StatusResult SetEx(const string& Key, int Seconds, const string& Value);

	// setnx
	BoolResult SetNx(const string& Key, const string& Value);

	//setrange cmd 
	IntResult SetRange(const string& Key, uint32_t Offset, const string& Value);

	//strlen cmd 
	IntResult Strlen(const string& Key);

	/***********************hash cmd*****************************/

	//hdel cmd
	IntResult Hdel(const string& Key, const vector<string>& Fields);

	//hexists cmd
	BoolResult Hexists(const string& Key, const string& Field);

	// hget cmd 
	StringResult Hget(const string& Key, const string& Field);

	// hgetall cmd
	StringStringMapResult HgetAll(const string& Key);

	//hincrby cmd
	IntResult HincrBy(const string& Key, const string& Field, int64_t Incr);

	//hincrbyfloat cmd 
	FloatResult HincrByFloat(const string& Key, const string& Field, float Incr);

	//hkeys cmd 
	StringArrayResult Hkeys(const string& Key);

	//hlen cmd
	IntResult Hlen(const string& Key);

	//hmget cmd 
	StringArrayResult Hmget(const string& Key, const vector<string>& Fields);

	//int Hscan(const string& Key, int64_t cursor,void *data) [match pattern] [count count]

	//hmset cmd 
	int Hmset(const string& Key, const vector<pair<string, string> >& FieldVal);
	int Hmset(const string& Key, const map<string, string>& FieldVal);

	//hset cmd
	int Hset(const string& Key, const string& Field, const string& Value);

	//hsetnx cmd
	int HsetNx(const string& Key, const string& Field, const string& Value);

	//hstrlen cmd
	int Hstrlen(const string& Key, const string& Field, int64_t& Len);

	//hvals cmd
	int Hvals(const string& Key, vector<string> &Values);

	/***********************list cmd*****************************/

	//blpop cmd 
	int Blpop(const vector<string>& Keys, int Timeout, map<string, string>& Result);

	//brpop cmd
	int Brpop(const vector<string>& Keys, int Timeout, map<string, string>& Result);

	//brpoplpush cmd
	int BrpopLpush(const string& Src, const string& Dst, int Timeout, pair<string, float>& Result);

	//lindex cmd
	int Lindex(const string& Key, int64_t index, string &Value);

	//linsert cmd 
	int Linsert(const string& Key, const list_insert_type Type, const string& Pivot, const string& Value);

	//llen cmd
	int Llen(const string& Key, int64_t& Len);

	//lpop cmd
	int Lpop(const string& Key, string& Value);

	//lpush cmd 
	int Lpush(const string& Key, const vector<string>& Values, int64_t& Len);

	//lpushx cmd
	int Lpushx(const string& Key, const string& Value, int64_t& Len);

	//lrange cmd
	int Lrange(const string& Key, int64_t Start, int64_t Stop, vector<string>& Values);

	//lpushx cmd
	int Lrem(const string& Key, int Count, const string& Value, int64_t &RemNum);

	// to do 
	//lset cmd callback:status_reply
	int Lset(const string& Key, int index, const string& value, void *data);

	//ltrim cmd callback:status_reply
	int Ltrim(const string& Key, int start, int end, void *data);

	//rpop cmd callback:sting_reply
	int Rpop(const string& Key, void *data);

	//rpoplpush cmd callback:sting_reply
	int RpopLpush(const string& src, const string& dst, void *data);

	//rpush cmd callback:integer_reply
	int Rpush(const string& Key, const vector<string>& values, void *data);

	//rpushx cmd callback:integer_reply
	int Rpushx(const string& Key, const string& value, void *data);

	/***********************set cmd*****************************/

	//sadd cmd callback:integer_reply
	int Sadd(const string& Key, const vector<string>& members, void *data);

	//sadd cmd callback:integer_reply
	int Scard(const string& Key, void *data);

	//sdiff cmd callback:string_list_reply 
	int Sdiff(const vector<string>& keys, void *data);

	//sdiffstore cmd callback:integer_reply
	int SdiffStore(const string& dst, const vector<string>& keys, void *data);

	//sinter cmd callback:string_list_reply 
	int Sinter(const vector<string>& keys, void *data);

	//sinterstore cmd callback:integer_reply
	int SinterStore(const string& dst, const vector<string>& keys, void *data);

	//sismember cmd callback:integer_reply
	int Sismember(const string& Key, const string& member, void *data);

	//smembers cmd callback:string_list_reply 
	int Smembers(const string& Key, void *data);

	//smove cmd callback:integer_reply
	int Smove(const string& src, const string& dst, const string& member, void *data);

	//spop cmd callback:string_reply
	int Spop(const string& Key, void *data);
	//int spop(const string& Key, int count,void *data);

	//srandmember cmd callback:string_reply
	int SrandMember(const string& Key, void *data);

	//srandmember cmd callback:string_list_reply 
	int SrandMember(const string& Key, int count, void *data);

	//srem cmd callback:integer_reply
	int Srem(const string& Key, const vector<string>& members, void *data);

	//int Sscan(const string &Key,int64_t cursor) [match pattern] [count count]

	//sunion cmd callback:string_list_reply 
	int Sunion(const vector<string>& keys, void *data);

	//sunionstore cmd callback:integer_reply
	int SunionStore(const string& dst, const vector<string>& keys, void *data);

	/***********************zset cmd*****************************/

	//zadd cmd callback:integer_reply
	int Zadd(const string& Key, const vector<pair<float, string> >& score_mem, void *data);

	//zcard cmd callback:integer_reply
	int Zcard(const string& Key, void *data);

	//zcount cmd callback:integer_reply.  min and max must can convert to float
	int Zcount(const string& Key, const string& min, const string& max, void *data);

	//zincrby cmd callback:double_reply
	int ZincrBy(const string& Key, const double incr, const string& member, void *data);

	//int ZinterStore();
	//int ZlexCount(const string& Key, const string& min, const string& max,void *data);

	//zrange cmd.  callback:string_list_reply. if withscores is true callback:sd_map_reply 
	int Zrange(const string& Key, int start, int end, void *data, bool withscores = false);

	//int ZrangeByLex(const string& Key, const string& min, const string& max,void *data) [limit offset count]

	//zrangebyscore cmd.zrangebyscore callback:string_list_reply. if withscores is true callback:sd_map_reply 
	int ZrangeByScore(const string& Key, const string& min, const string& max, void *data, bool withscores = false);
	int ZrangeByScore(const string& Key, const string& min, const string& max, int offset, int count, void *data, bool withscores = false);

	//zrank cmd callback:integer_reply.
	int Zrank(const string& Key, const string& member, void *data);

	//zrem cmd callback:integer_reply.
	int Zrem(const string& Key, const vector<string>& members, void *data);

	//int ZremRangeByLex(const string& Key, const string& min, const string& max,void *data);

	//zremrangebyrank cmd callback:integer_reply.
	int ZremRangeByRank(const string& Key, int start, int stop, void *data);

	//zremrangebyscore cmd callback:integer_reply. min and max must can convert to float
	int ZremRangeByScore(const string& Key, const string& min, const string& max, void *data);

	//zrevrange cmd. zrange callback:string_list_reply. if withscores is true callback:sd_map_reply 
	int Zrevrange(const string& Key, int start, int stop, void *data, bool withscores = false);

	//int ZrevrangeByLex(const string& Key, const string& min, const string& max,void *data) [limit offset count]

	//zrangebyscore cmd.zrangebyscore callback:string_list_reply. if withscores is true callback:sd_map_reply 
	int ZrevRangeByScore(const string& Key, const string& min, const string& max, void *data, bool withscores = false);
	int ZrevRangeByScore(const string& Key, const string& min, const string& max, int offset, int count, void *data, bool withscores = false);

	//zrevrank cmd callback:integer_reply.
	int ZrevRank(const string& Key, const string& member, void *data);

	//int Zscan(const string &Key,int64_t cursor) [match pattern] [count count]

	//zscore cmd callback:double_reply. // 
	int Zscore(const string& Key, const string& member, void *data);

	//int ZunionStore();

	/***********************pub/sub cmd *****************************/

	//publish cmd callback:integer_reply
	//int publish(const string& channel, const string& message, void *data);

	//psubscribe cmd callback:array_reply
	//int psubscribe(const vector<string>& pattern, void *data);

	//subscribe cmd callback:array_reply
	//int subscribe(const vector<string>& channels, void *data);

	//punsubscribe cmd.callback:array_reply  reply in psubscribe`s callback
	//int punsubscribe(const vector<string>& pattern, void *data);

	//unsubscribe cmd.callback:array_reply reply in subscribe`s callback
	//int unsubscribe(const vector<string>& channels, void *data);

	// pubsub channels callback:string_list_reply
	//int pubsub_channels(const string& channel, void *data);

	//pubsub numsub cmd.callback:array_reply
	//int pubsub_numsub(const vector<string>& channels, void *data);

	//pubsub numpat cmd callback:integer_reply
	//int pubsub_numpat(void *data);

	/***********************transaction cmd *****************************/
	// discard  cmd
	// exec cmd    
	// mutil cmd    
	// unwatch  cmd
	// watch  cmd  

	/***********************script cmd **********************************/

	//EVALSHA
	//SCRIPT EXISTS
	//SCRIPT FLUSH
	//SCRIPT KILL
	//SCRIPT LOAD

	/***********************connection cmd *****************************/
	//AUTH
	//ECHO
	//PING
	//QUIT
	//SELECT

	/***********************server cmd *****************************/
#endif
private:
	RedisCmd _cmd;
};