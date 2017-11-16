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

class IRedisClient
{
public:
	IRedisClient();
	~IRedisClient();
	// del cmd 
	shared_ptr<IntResult> Del(const vector<string>& Keys);

	// dump cmd
	shared_ptr<StringResult> Dump(const string& Key);

	// exists cmd
	shared_ptr<BoolResult> Exists(const string& Key);

	// expire cmd 
	shared_ptr<BoolResult> Expire(const string& Key, uint32_t Seconds);

	// expireat cmd
	shared_ptr<BoolResult> ExpireAt(const string& Key, uint64_t Timestamp);

	// keys cmd
	shared_ptr<StringArrayResult> Keys(const string& Pattern);

	//BaseResult Migrate(const string& Host, const uint16_t Port, const string& Key, const string& Dest_db, uint32_t Timeout,bool copy = false, bool replace = false);
	//BaseResult Move(const string& Key, const string& Db);
	//BaseResult Object(const string& subcommand, const vector<string>& args);

	// persist cmd
	shared_ptr<BoolResult> Persist(const string& Key);

	// pexpire cmd
	shared_ptr<BoolResult> PExpire(const string& Key, uint32_t MilliSec);

	// pexpireat cmd
	shared_ptr<BoolResult> PExpireAt(const string&Key, uint64_t Timestamp);

	// pttl cmd 
	shared_ptr<IntResult> PTTL(const string& Key);

	// randomkey cmd
	shared_ptr<StringResult> RandomKey();

	// rename cmd
	shared_ptr<StatusResult> Rename(const string& Key, const string& NewKey);

	// renamenx cmd
	shared_ptr<BoolResult> RenameNX(const string& Key, const string& NewKey);

	// restore cmd
	shared_ptr<StatusResult> Restore(const string& Key, int64_t TTL, const string& SerializedValue, bool Repalce = false);

	//shared_ptr<StringArrayResult> Sort(const string& Key);

	// ttl cmd
	shared_ptr<IntResult> TTL(const string& Key);

	// type cmd
	shared_ptr<StringResult> Type(const string& Key);

	// scan cmd
	//BaseResult Scan(const string& Key);

	/***********************string cmd*****************************/

	// append cmd 
	shared_ptr<IntResult> Append(const string& Key, const string& Value);

	// bitcount cmd
	shared_ptr<IntResult> BitCount(const string& Key);
	shared_ptr<IntResult> BitCount(const string& Key, int Start, int End);

	//bitfield
	//BaseResult BitField(const string& Key);

	// bitop cmd op must in {"AND","OR","XOR","NOT"} 
	shared_ptr<IntResult> BitOp(const string& Op, const string& DestKey, const vector<string>& Keys);
	shared_ptr<IntResult> BitOpAnd(const string& DestKey, const vector<string>& Keys);
	shared_ptr<IntResult> BitOpOr(const string& DestKey, const vector<string>& Keys);
	shared_ptr<IntResult> BitOpXor(const string& DestKey, const vector<string>& Keys);
	shared_ptr<IntResult> BitOpNot(const string& DestKey, const vector<string>& Keys);

	// bitpos cmd 
	//shared_ptr<IntResult> Bitpos(const string& Key, int Bit, int64_t& Pos, int Start = 0, int End = 0);

	// decr cmd 
	shared_ptr<IntResult> Decr(const string& Key);

	// decrby cmd
	shared_ptr<IntResult> DecrBy(const string& Key, int64_t By);

	// get cmd
	shared_ptr<StringResult> Get(const string& Key);

	// getbit cmd
	shared_ptr<IntResult> GetBit(const string& Key, int Offset);

	// getrange cmd
	shared_ptr<StringResult> GetRange(const string& Key, int Start, int End);

	// getset cmd
	shared_ptr<StringResult> GetSet(const string& Key, const string& Value);

	// incr cmd 
	shared_ptr<IntResult> Incr(const string& Key);

	// incrby cmd 
	shared_ptr<IntResult> IncrBy(const string& Key, int64_t Incr);

	// incrbyfloat cmd
	shared_ptr<FloatResult> IncrByFloat(const string& Key, float Incr);

	// mget cmd
	shared_ptr<StringArrayResult> MGet(const vector<string>& Keys);

	// mset cmd
	shared_ptr<StatusResult> MSet(const vector<pair<string, string> >& KeyValues);

	// mset cmd
	shared_ptr<BoolResult> MSetNX(const vector<pair<string, string> >& KeyValues);

	// psetex cmd
	shared_ptr<StatusResult> PSetEX(const string& Key, int64_t MilliSeconds, const string& Val);

	// set cmd
	shared_ptr<StatusResult> Set(const string& Key, const string& Value);
	shared_ptr<StatusResult> Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time);
	shared_ptr<StatusResult> Set(const string& Key, const string& Value, expire_unit Unit, int64_t Time, string_set_type Type);

	// setbit 
	shared_ptr<IntResult> SetBit(const string& Key, uint32_t Offset, int64_t NewBitValue);

	// setex 
	shared_ptr<StatusResult> SetEX(const string& Key, int Seconds, const string& Value);

	// setnx
	shared_ptr<BoolResult> SetNX(const string& Key, const string& Value);

	//setrange cmd 
	shared_ptr<IntResult> SetRange(const string& Key, uint32_t Offset, const string& Value);

	//strlen cmd 
	shared_ptr<IntResult> StrLen(const string& Key);

	/***********************hash cmd*****************************/

	//hdel cmd
	shared_ptr<IntResult> HDel(const string& Key, const vector<string>& Fields);

	//hexists cmd
	shared_ptr<BoolResult> HExists(const string& Key, const string& Field);

	// hget cmd 
	shared_ptr<StringResult> HGet(const string& Key, const string& Field);

	// hgetall cmd
	shared_ptr<StringStringMapResult> HGetAll(const string& Key);

	//hincrby cmd
	shared_ptr<IntResult> HIncrBy(const string& Key, const string& Field, int64_t Incr);

	//hincrbyfloat cmd 
	shared_ptr<FloatResult> HIncrByFloat(const string& Key, const string& Field, float Incr);

	//hkeys cmd 
	shared_ptr<StringArrayResult> HKeys(const string& Key);

	//hlen cmd
	shared_ptr<IntResult> HLen(const string& Key);

	//hmget cmd 
	shared_ptr<StringArrayResult> HMGet(const string& Key, const vector<string>& Fields);

	//int Hscan(const string& Key, int64_t cursor,void *data) [match pattern] [count count]

	//hmset cmd 
	shared_ptr<StatusResult> HMSet(const string& Key, const vector<pair<string, string> >& FieldVal);
	//shared_ptr<StatusResult> Hmset(const string& Key, const vector<pair<string, string> >& FieldVal);

	//hset cmd
	shared_ptr<BoolResult> HSet(const string& Key, const string& Field, const string& Value);

	//hsetnx cmd
	shared_ptr<BoolResult> HSetNX(const string& Key, const string& Field, const string& Value);

	//hstrlen cmd
	shared_ptr<IntResult> HStrLen(const string& Key, const string& Field);

	//hvals cmd
	shared_ptr<StringArrayResult> HVals(const string& Key);

	/***********************list cmd*****************************/

	//blpop cmd 
	shared_ptr<StringArrayResult> BLPop(vector<string>& Keys, int Timeout);

	//brpop cmd
	shared_ptr<StringArrayResult> BRPop(vector<string>& Keys, int Timeout);

	//brpoplpush cmd
	shared_ptr<StringArrayResult> BRPopLPush(const string& Src, const string& Dst, int Timeout);

	//lindex cmd
	shared_ptr<StringResult> LIndex(const string& Key, int64_t index);

	//linsert cmd 
	shared_ptr<IntResult> LInsert(const string& Key, const list_insert_type Type, const string& Pivot, const string& Value);
	shared_ptr<IntResult> LInsertBefore(const string& Key, const string& Pivot, const string& Value);
	shared_ptr<IntResult> LInsertAfter(const string& Key, const string& Pivot, const string& Value);

	//llen cmd
	shared_ptr<IntResult> LLen(const string& Key);

	//lpop cmd
	shared_ptr<StringResult> LPop(const string& Key);

	//lpush cmd 
	shared_ptr<IntResult> LPush(const string& Key, const vector<string>& Values);

	//lpushx cmd
	shared_ptr<IntResult> LPushX(const string& Key, const string& Value);

	//lrange cmd
	shared_ptr<StringArrayResult> LRange(const string& Key, int64_t Start, int64_t Stop);

	//lpushx cmd
	shared_ptr<IntResult> LRem(const string& Key, int64_t Count, const string& Value);

	//lset cmd
	shared_ptr<StatusResult> LSet(const string& Key, int64_t Index, const string& Value);

	//ltrim cmd
	shared_ptr<StatusResult> LTrim(const string& Key, int64_t Start, int64_t End);

	//rpop cmd
	shared_ptr<StringResult> RPop(const string& Key);

	//rpoplpush cmd
	shared_ptr<StringResult> RPopLPush(const string& Src, const string& Dst);

	//rpush cmd 
	shared_ptr<IntResult> RPush(const string& Key, const vector<string>& Values);

	//rpushx cmd
	shared_ptr<IntResult> RPushX(const string& Key, const string& Value);

	/***********************set cmd*****************************/

	//sadd cmd
	shared_ptr<IntResult> SAdd(const string& Key, const vector<string>& Members);

	//sadd cmd
	shared_ptr<IntResult> SCard(const string& Key);

	//sdiff cmd 
	shared_ptr<StringArrayResult> SDiff(const vector<string>& Keys);

	//sdiffstore cmd
	shared_ptr<IntResult> SDiffStore(const string& Dst, const vector<string>& Keys);

	//sinter cmd
	shared_ptr<StringArrayResult> SInter(const vector<string>& Keys);

	//sinterstore cmd
	shared_ptr<IntResult> SInterStore(const string& Dst, const vector<string>& Keys);

	//sismember cmd
	shared_ptr<BoolResult> SIsMember(const string& Key, const string& Member);

	//smembers cmd
	shared_ptr<StringArrayResult> SMembers(const string& Key);

	//smove cmd 
	shared_ptr<BoolResult> SMove(const string& Src, const string& Dst, const string& Member);

	//spop cmd
	shared_ptr<StringResult> SPop(const string& Key);
	shared_ptr<StringArrayResult> SPopN(const string& Key, int64_t Count);

	//srandmember cmd
	shared_ptr<StringResult> SRandMember(const string& Key);
	shared_ptr<StringArrayResult> SRandMemberN(const string& Key, int64_t Count);

	//srem cmd
	shared_ptr<IntResult> SRem(const string& Key, const vector<string>& Members);

	//int Sscan(const string &Key,int64_t cursor) [match pattern] [count count]

	//sunion cmd 
	shared_ptr<StringArrayResult> SUnion(const vector<string>& Keys);

	//sunionstore cmd
	shared_ptr<IntResult> SUnionStore(const string& Dst, const vector<string>& Keys);

	/***********************zset cmd*****************************/

	//zadd cmd
	shared_ptr<IntResult> ZAdd(const string& Key, const vector<pair<float, string> >& ScoreMem);
	shared_ptr<IntResult> ZAddNX(const string& Key, const vector<pair<float, string> >& ScoreMem);
	shared_ptr<IntResult> ZAddXX(const string& Key, const vector<pair<float, string> >& ScoreMem);
	shared_ptr<IntResult> ZAddCh(const string& Key, const vector<pair<float, string> >& ScoreMem);
	shared_ptr<IntResult> ZAddNXCh(const string& Key, const vector<pair<float, string> >& ScoreMem);
	shared_ptr<IntResult> ZAddXXCh(const string& Key, const vector<pair<float, string> >& ScoreMem);

	//zcard cmd
	shared_ptr<IntResult> ZCard(const string& Key);

	//zcount cmd  min and max must can convert to float
	shared_ptr<IntResult> ZCount(const string& Key, const string& Min, const string& Max);

	//zincrby cmd
	shared_ptr<FloatResult> ZincrBy(const string& Key, const float Incr, const string& Member);

	//shared_ptr<IntResult> ZinterStore();

	//zlexcount cmd
	shared_ptr<IntResult> ZlexCount(const string& Key, const string& Min, const string& Max);

	//zrange cmd 
	shared_ptr<StringArrayResult> ZRange(const string& Key, int64_t Start, int64_t End);
	shared_ptr<StringFloatMapResult> ZRangeWithScores(const string& Key, int64_t Start, int64_t End);
	 
	//zrangebylex cmd
	shared_ptr<StringArrayResult> ZRangeByLex(const string& Key, const string& Min, const string& Max);
	shared_ptr<StringArrayResult> ZRangeByLex(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);

	//zrangebyscore cmd
	shared_ptr<StringArrayResult> ZRangeByScore(const string& Key, const string& Min, const string& Max);
	shared_ptr<StringArrayResult> ZRangeByScore(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);
	shared_ptr<StringFloatMapResult> ZRangeByScoreWithScores(const string& Key, const string& Min, const string& Max);
	shared_ptr<StringFloatMapResult> ZRangeByScoreWithScores(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);

	//zrank cmd
	shared_ptr<IntResult> ZRank(const string& Key, const string& Member);

	//zrem cmd
	shared_ptr<IntResult> ZRem(const string& Key, const vector<string>& Members);

	//zremrangebylex
	shared_ptr<IntResult> ZRemRangeByLex(const string& Key, const string& Min, const string& Max);

	//zremrangebyrank cmd
	shared_ptr<IntResult> ZRemRangeByRank(const string& Key, int64_t Start, int64_t End);

	//zremrangebyscore cmd  min and max must can convert to float
	shared_ptr<IntResult> ZRemRangeByScore(const string& Key, const string& Min, const string& Max);

	//zrevrange cmd
	shared_ptr<StringArrayResult> ZRevRange(const string& Key, int64_t Start, int64_t End);
	shared_ptr<StringFloatMapResult> ZRevRangeWithScores(const string& Key, int64_t Start, int64_t End);

	//zrevrangebylex cmd
	shared_ptr<StringArrayResult> ZRevRangeByLex(const string& Key, const string& Min, const string& Max);
	shared_ptr<StringArrayResult> ZRevRangeByLex(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);

	//zrevrangebyscore cmd
	shared_ptr<StringArrayResult> ZRevRangeByScore(const string& Key, const string& Min, const string& Max);
	shared_ptr<StringArrayResult> ZRevRangeByScore(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);
	shared_ptr<StringFloatMapResult> ZRevRangeByScoreWithScores(const string& Key, const string& Min, const string& Max);
	shared_ptr<StringFloatMapResult> ZRevRangeByScoreWithScores(const string& Key, const string& Min, const string& Max, int64_t Offset, int64_t Count);

	//zrevrank cmd
	shared_ptr<IntResult> ZRevRank(const string& Key, const string& Member);

	//int Zscan(const string &Key,int64_t cursor) [match pattern] [count count]

	//zscore cmd
	shared_ptr<FloatResult> Zscore(const string& Key, const string& Member);

	shared_ptr<IntResult> ZunionStore(const string& Dst, vector<string>& Keys, const string &Aggregate="SUM");
	shared_ptr<IntResult> ZunionStoreWeights(const string& Dst, vector<string>& Keys, const vector<float>& Weights, const string &Aggregate="SUM");

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
	shared_ptr<RawResult> RawCommand(const char* cmd, ...);
	shared_ptr<RawResult> RawCommandv(const vector<string> &Cmd);

protected:
	RedisCmd *_cmd;
};

class RedisPipeClient;
class RedisClient :public IRedisClient
{
	friend RedisPipeClient;
public:
	explicit RedisClient(RedisOpt &Opt);
	~RedisClient();
};


// 不是多线程安全
class RedisPipeClient :public IRedisClient
{
public:
	explicit RedisPipeClient(RedisClient *Client);
	~RedisPipeClient();
	//void Begin();
	int Exec();
};

// to do 
class RedisScript
{
public:
	explicit RedisScript(RedisClient *Client, string &Script);
	~RedisScript();
	int Eval();
	int EvalSha();
	int Load();
	int Exists();
	int Run();
private:
	string _script;
};
