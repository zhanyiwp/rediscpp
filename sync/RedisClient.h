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
	BoolResult PExpire(const string& Key, uint32_t MilliSec);

	// pexpireat cmd
	BoolResult PExpireAt(const string&Key, uint64_t Timestamp);

	// pttl cmd 
	IntResult PTTL(const string& Key);

	// randomkey cmd
	StringResult RandomKey();

	// rename cmd
	StatusResult Rename(const string& Key, const string& NewKey);

	// renamenx cmd
	BoolResult RenameNX(const string& Key, const string& NewKey);

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
	IntResult DecrBy(const string& Key, int64_t By);

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
	StringArrayResult MGet(const vector<string>& Keys);

	// mset cmd
	StatusResult MSet(const vector<pair<string, string> >& KeyValues);

	// mset cmd
	BoolResult MSetNX(const vector<pair<string, string> >& KeyValues);

	// psetex cmd
	StatusResult PSetEX(const string& Key, int64_t MilliSeconds, const string& Val);

	// set cmd
	StatusResult Set(const string& Key, const string& Value);
	StatusResult Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time);
	StatusResult Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time, string_set_type Type);

	// setbit 
	IntResult SetBit(const string& Key, uint32_t Offset, int64_t NewBitValue);

	// setex 
	StatusResult SetEX(const string& Key, int Seconds, const string& Value);

	// setnx
	BoolResult SetNX(const string& Key, const string& Value);

	//setrange cmd 
	IntResult SetRange(const string& Key, uint32_t Offset, const string& Value);

	//strlen cmd 
	IntResult StrLen(const string& Key);

	/***********************hash cmd*****************************/

	//hdel cmd
	IntResult HDel(const string& Key, const vector<string>& Fields);

	//hexists cmd
	BoolResult HExists(const string& Key, const string& Field);

	// hget cmd 
	StringResult HGet(const string& Key, const string& Field);

	// hgetall cmd
	StringStringMapResult HGetAll(const string& Key);

	//hincrby cmd
	IntResult HIncrBy(const string& Key, const string& Field, int64_t Incr);

	//hincrbyfloat cmd 
	FloatResult HIncrByFloat(const string& Key, const string& Field, float Incr);

	//hkeys cmd 
	StringArrayResult HKeys(const string& Key);

	//hlen cmd
	IntResult HLen(const string& Key);

	//hmget cmd 
	StringArrayResult HMGet(const string& Key, const vector<string>& Fields);

	//int Hscan(const string& Key, int64_t cursor,void *data) [match pattern] [count count]

	//hmset cmd 
	StatusResult HMSet(const string& Key, const vector<pair<string, string> >& FieldVal);
	//StatusResult Hmset(const string& Key, const vector<pair<string, string> >& FieldVal);

	//hset cmd
	BoolResult HSet(const string& Key, const string& Field, const string& Value);

	//hsetnx cmd
	BoolResult HSetNX(const string& Key, const string& Field, const string& Value);

	//hstrlen cmd
	IntResult HStrLen(const string& Key, const string& Field);

	//hvals cmd
	StringArrayResult HVals(const string& Key);

	/***********************list cmd*****************************/

	//blpop cmd 
	StringArrayResult BLPop(vector<string>& Keys, int Timeout);

	//brpop cmd
	StringArrayResult BRPop(vector<string>& Keys, int Timeout);

	//brpoplpush cmd
	StringArrayResult BRPopLPush(const string& Src, const string& Dst, int Timeout);

	//lindex cmd
	StringResult LIndex(const string& Key, int64_t index);

	//linsert cmd 
	IntResult LInsert(const string& Key, const list_insert_type Type, const string& Pivot, const string& Value);
	IntResult LInsertBefore(const string& Key, const string& Pivot, const string& Value);
	IntResult LInsertAfter(const string& Key, const string& Pivot, const string& Value);

	//llen cmd
	IntResult LLen(const string& Key);

	//lpop cmd
	StringResult LPop(const string& Key);

	//lpush cmd 
	IntResult LPush(const string& Key, const vector<string>& Values);

	//lpushx cmd
	IntResult LPushX(const string& Key, const string& Value);

	//lrange cmd
	StringArrayResult LRange(const string& Key, int64_t Start, int64_t Stop);

	//lpushx cmd
	IntResult LRem(const string& Key, int64_t Count, const string& Value);

	//lset cmd
	StatusResult LSet(const string& Key, int64_t Index, const string& Value);

	//ltrim cmd
	StatusResult LTrim(const string& Key, int64_t Start, int64_t End);

	//rpop cmd
	StringResult RPop(const string& Key);

	//rpoplpush cmd
	StringResult RPopLPush(const string& Src, const string& Dst);

	//rpush cmd 
	IntResult RPush(const string& Key, const vector<string>& Values);

	//rpushx cmd
	IntResult RPushX(const string& Key, const string& Value);

	/***********************set cmd*****************************/

	//sadd cmd
	IntResult SAdd(const string& Key, const vector<string>& Members);

	//sadd cmd
	IntResult SCard(const string& Key);

	//sdiff cmd 
	StringArrayResult SDiff(const vector<string>& Keys);

	//sdiffstore cmd
	IntResult SDiffStore(const string& Dst, const vector<string>& Keys);

	//sinter cmd
	StringArrayResult SInter(const vector<string>& Keys);

	//sinterstore cmd
	IntResult SInterStore(const string& Dst, const vector<string>& Keys);

	//sismember cmd
	BoolResult SIsMember(const string& Key, const string& Member);

	//smembers cmd
	StringArrayResult SMembers(const string& Key);

	//smove cmd 
	BoolResult SMove(const string& Src, const string& Dst, const string& Member);

	//spop cmd
	StringResult SPop(const string& Key);
	StringArrayResult SPopN(const string& Key, int64_t Count);

	//srandmember cmd
	StringResult SRandMember(const string& Key);
	StringArrayResult SRandMemberN(const string& Key, int64_t Count);

	//srem cmd
	IntResult SRem(const string& Key, const vector<string>& Members);

	//int Sscan(const string &Key,int64_t cursor) [match pattern] [count count]

	//sunion cmd 
	StringArrayResult SUnion(const vector<string>& Keys);

	//sunionstore cmd
	IntResult SUnionStore(const string& Dst, const vector<string>& Keys);

	/***********************zset cmd*****************************/

	//zadd cmd
	IntResult ZAdd(const string& Key, const vector<pair<float, string> >& ScoreMem);
	IntResult ZAddNX(const string& Key, const vector<pair<float, string> >& ScoreMem);
	IntResult ZAddXX(const string& Key, const vector<pair<float, string> >& ScoreMem);
	IntResult ZAddCh(const string& Key, const vector<pair<float, string> >& ScoreMem);
	IntResult ZAddNXCh(const string& Key, const vector<pair<float, string> >& ScoreMem);
	IntResult ZAddXXCh(const string& Key, const vector<pair<float, string> >& ScoreMem);

	//zcard cmd
	IntResult ZCard(const string& Key);

	//zcount cmd  min and max must can convert to float
	IntResult ZCount(const string& Key, const string& Min, const string& Max);

	//zincrby cmd
	FloatResult ZincrBy(const string& Key, const float Incr, const string& Member);

	//IntResult ZinterStore();

	//zlexcount cmd
	IntResult ZlexCount(const string& Key, const string& Min, const string& Max);

	//zrange cmd 
	StringArrayResult ZRange(const string& Key, int64_t Start, int64_t End);
	StringFloatMapResult ZRangeWithScores(const string& Key, int64_t Start, int64_t End);
	 
	//zrangebylex cmd
	StringArrayResult ZRangeByLex(const string& Key, const string& Min, const string& Max);
	StringArrayResult ZRangeByLex(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);

	//zrangebyscore cmd
	StringArrayResult ZRangeByScore(const string& Key, const string& Min, const string& Max);
	StringArrayResult ZRangeByScore(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);
	StringFloatMapResult ZRangeByScoreWithScores(const string& Key, const string& Min, const string& Max);
	StringFloatMapResult ZRangeByScoreWithScores(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);

	//zrank cmd
	IntResult ZRank(const string& Key, const string& Member);

	//zrem cmd
	IntResult ZRem(const string& Key, const vector<string>& Members);

	//zremrangebylex
	IntResult ZRemRangeByLex(const string& Key, const string& Min, const string& Max);

	//zremrangebyrank cmd
	IntResult ZRemRangeByRank(const string& Key, int64_t Start, int64_t End);

	//zremrangebyscore cmd  min and max must can convert to float
	IntResult ZRemRangeByScore(const string& Key, const string& Min, const string& Max);

	//zrevrange cmd
	StringArrayResult ZRevRange(const string& Key, int64_t Start, int64_t End);
	StringFloatMapResult ZRevRangeWithScores(const string& Key, int64_t Start, int64_t End);

	//zrevrangebylex cmd
	StringArrayResult ZRevRangeByLex(const string& Key, const string& Min, const string& Max);
	StringArrayResult ZRevRangeByLex(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);

	//zrevrangebyscore cmd
	StringArrayResult ZRevRangeByScore(const string& Key, const string& Min, const string& Max);
	StringArrayResult ZRevRangeByScore(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);
	StringFloatMapResult ZRevRangeByScoreWithScores(const string& Key, const string& Min, const string& Max);
	StringFloatMapResult ZRevRangeByScoreWithScores(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);

	//zrevrank cmd
	IntResult ZRevRank(const string& Key, const string& Member);

	//int Zscan(const string &Key,int64_t cursor) [match pattern] [count count]

	//zscore cmd
	FloatResult Zscore(const string& Key, const string& Member);

	IntResult ZunionStore(const string& Dst, vector<string>& Keys, const string &Aggregate="SUM");
	IntResult ZunionStoreWeights(const string& Dst, vector<string>& Keys, const vector<float>& Weights, const string &Aggregate="SUM");

	/***********************pub/sub cmd *****************************/

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

	/***********************raw redis cmd *****************************/
	//直接执行redis命令 当上述封装的命令不能满足要求时 可以使用这些接口执行特定redis命令,一般不使用
	redisReply *RawCommand(const char* cmd, ...);
	redisReply *RawCommandv(const vector<string> &Cmd);

private:
	RedisCmd _cmd;
};