#include <vector>
#include <string>
#include <sstream>
#include "async_cmd.h"
#include "async_reply.h"

#pragma once 

using namespace std;

namespace asyncredis
{
	//clinet redis操作接口类 提供对外访问 可以继承reply类来处理执行结果
	enum expire_unit
	{
		em_sec=0,
		em_msec=1
	};

	enum string_set_type
	{
		em_set_nx=0,
		em_set_xx=1
	};
	
	enum list_insert_type
	{
    		em_insert_before = 0,
    		em_insert_after  = 1
	};

	template<class T>
	std::string tostring(const T &t) 
	{
		ostringstream oss;
		oss << t;
		return oss.str();
	}

	class nb_redis 
	{
		public:
			/**
			* @brief init 
			* @param [in]	ip		redis ip
			* @param [in]	port		redis port
			* @param [in]	passwd		redis password 不为空时,表示需要进行redis认证,如果该值非空,但是redis没有开启认证,会忽略传入的值正常建立连接
			* @param [in]	reply_handler	注册结果处理类
			* @param [in]	loop		循环ev_loop 	
			* return 成功时返回0 失败返回小于0 
			* Note:如果是多线程 请确保每一个线程一个独立的nb_redis实例和reply_handler实例 
			*/
			int init(string &ip, int port, string &passwd,reply *reply_handler, struct ev_loop *loop);
			
			/**
			* @brief redis cmd 封装
			* @param [in]	key	需要操作的key
			* @param [in]	data	用户数据,reply类的回调处理函数返回该参数	
			* return 成功加入发送队列时返回0 失败返回小于0 
			* Note: 执行结果通过reply::xxxxxx_reply回调传递
			*/

			/***********************key cmd*****************************/

			// del cmd callback:integer_reply 
			int del(const vector<string>& keys,void *data);

			// dump cmd callback:string_reply 
			int dump(const string& key,void *data);

			// exists cmd callback:integer_reply 
			int exists(const string& key,void *data);

			// expire cmd callback:integer_reply 
			int expire(const string& key, int seconds,void *data);
			
			// expireat cmd callback:integer_reply
			int expireat(const string& key, int timestamp,void *data);
			
			// keys cmd callback:string_list_reply // 
			int keys(const string& pattern,void *data);
			
			//int migrate(const string& host, int port, const string& key, const string& dest_db, int timeout,void *data,bool copy = false, bool replace = false);
			//int move(const string& key, const string& db,void *data);
			//int object(const string& subcommand, const vector<string>& args,void *data);
			
			// persist cmd callback:integer_reply
			int persist(const string& key,void *data);
		
			// pexpire cmd callback:integer_reply
			int pexpire(const string& key, int milliseconds,void *data);
			
			// pexpireat cmd callback:integer_reply
			int pexpireat(const string& key, uint64_t mtimestamp,void *data);
			
			// pttl cmd callback:integer_reply
			int pttl(const string& key,void *data);
			
			// pttl cmd callback:string_reply
			int randomkey(void *data);
			
			// rename cmd callback:status_reply
			int rename(const string& key, const string& newkey,void *data);
			
			// renamenx cmd callback:integer_reply
			int renamenx(const string& key, const string& newkey,void *data);
			
			// restore cmd callback:status_reply
			int restore(const string& key, int ttl, const string& serialized_value,void *data,bool repalce = false);
			
			//int sort(const string& key,void *data);
			
			// ttl cmd callback:integer_reply
			int ttl(const string& key,void *data);
			
			// type cmd callback:string_reply
			int type(const string& key,void *data);
			
			//int scan(const string& key,void *data);
			
			/***********************string cmd*****************************/
			
			// append cmd callback:integer_reply
			int append(const string& key, const string& value,void *data);
			
			// bitcount cmd callback:integer_reply
			int bitcount(const string& key,void *data);
			int bitcount(const string& key, int start, int end,void *data);
			
			//int bitfield(const string& key,void *data);
			
			// bitop cmd callback:integer_reply. op must in {"AND","OR","XOR","NOT"} 
			int bitop(const string& op, const string& destkey, const vector<string>& keys,void *data);
			//int bitop_and(const string& destkey, const vector<string>& keys,void *data);
			//int bitop_or(const string& destkey, const vector<string>& keys,void *data);
			//int bitop_xor(const string& destkey, const vector<string>& keys,void *data);
			//int bitop_not(const string& destkey, const string& keys,void *data);
			
			// bitpos cmd callback:integer_reply
			int bitpos(const string& key, int bit,void *data);
  			int bitpos(const string& key, int bit, int start,void *data);
  			int bitpos(const string& key, int bit, int start, int end,void *data);
			
			// decr cmd callback:integer_reply
			int decr(const string& key,void *data);

			// decrby cmd callback:integer_reply
			int decrby(const string& key, int64_t val,void *data);
			
			// get cmd callback:string_reply
			int get(const string& key, void *data);
			
			// getbit cmd callback:integer_reply
			int getbit(const string& key, int offset,void *data);
			
			// getrange cmd callback:string_reply
			int getrange(const string& key, int start, int end,void *data);
			
			// getset cmd callback:string_reply
			int getset(const string& key, const string& val,void *data);
			
			// incr cmd callback:integer_reply
			int incr(const string& key,void *data);
			
			// incrby cmd callback:integer_reply
			int incrby(const string& key, int64_t incr,void *data);
  			
			// incrbyfloat cmd callback:string_reply
			int incrbyfloat(const string& key, float incr,void *data);
			
			// mget cmd callback:string_list_reply // 
			int mget(const vector<string>& keys,void *data);
			
			// mset cmd callback:status_reply
			int mset(const vector<pair<string, string> >& key_vals,void *data);
			
			// mset cmd callback:integer_reply
			int msetnx(const vector<pair<string, string> >& key_vals,void *data);
			
			// psetex cmd callback:status_reply
			int psetex(const string& key, int milliseconds, const string& val,void *data);
			
			// set cmd callback:status_reply
			int set(const string& key, const string& value,void *data);
			int set(const string& key, const string& value,expire_unit unit, int time,void *data);
			int set(const string& key, const string& value,expire_unit unit, int time,string_set_type nx,void *data);

			// setbit cmd callback:integer_reply
			int setbit(const string& key, int offset, int value, void *data);
			
			// setex cmd callback:status_reply
			int setex(const string& key, int seconds, const string& value,void *data);
			
			// setnx cmd callback:integer_reply
			int setnx(const string& key, const string& value,void *data);
			
			//setrange cmd callback:integer_reply
			int setrange(const string& key, int offset, const string& value,void *data);
			
			//strlen cmd callback:integer_reply
			int strlen(const string& key,void *data);
			
			/***********************hash cmd*****************************/
		
			//hdel cmd callback:integer_reply
			int hdel(const string& key, const vector<string>& fields,void *data);
		
			//hexists cmd callback:integer_reply
			int hexists(const string& key, const string& field,void *data);
		
			// hget cmd callback:string_reply
			int hget(const string& key, const string& field,void *data);
		
			// hgetall cmd callback:ss_map_reply 
			int hgetall(const string& key,void *data);
		
			//hincrby cmd callback:integer_reply
			int hincrby(const string& key, const string& field, int64_t incr,void *data);
		
			//hincrbyfloat cmd callback:string_reply
			int hincrbyfloat(const string& key, const string& field, float incr,void *data);
		
			//hkeys cmd callback:string_list_reply 
			int hkeys(const string& key,void *data);
		
			//hlen cmd callback:integer_reply
			int hlen(const string& key,void *data);
		
			//hmget cmd callback:string_list_reply 
			int hmget(const string& key, const vector<string>& fields,void *data);
		
			//int hscan(const string& key, int64_t cursor,void *data) [match pattern] [count count]

			//hmset cmd callback:status_reply 
			int hmset(const string& key, const vector<pair<string, string> >& field_val,void *data);
		
			//hset cmd callback:integer_reply
			int hset(const string& key, const string& field, const string& value,void *data);
		
			//hsetnx cmd callback:integer_reply
			int hsetnx(const string& key, const string& field, const string& value,void *data);
		
			//int hstrlen(const string& key, const string& field,void *data);
			
			//hvals cmd callback:string_list_reply 
			int hvals(const string& key,void *data);

			/***********************list cmd*****************************/

			//blpop cmd callback:ss_map_reply 
			int blpop(const vector<string>& keys, int timeout,void *data);
  		
			//brpop cmd callback:ss_map_reply 
		  	int brpop(const vector<string>& keys, int timeout,void *data);
  		
			//brpoplpush cmd callback:string_reply
		  	int brpoplpush(const string& src, const string& dst, int timeout,void *data);
		
			//lindex cmd callback:string_reply
			int lindex(const string& key, int64_t index,void *data);
		
			//linsert cmd callback:integer_reply
			int linsert(const string& key, const list_insert_type type, const string& pivot, const string& value,void *data);
		
			//llen cmd callback:integer_reply
			int llen(const string& key,void *data);
		
			//lpop cmd callback:string_reply
			int lpop(const string& key,void *data);
		
			//lpush cmd callback:integer_reply
			int lpush(const string& key, const vector<string>& values,void *data);
			
			//lpushx cmd callback:integer_reply
			int lpushx(const string& key, const string& value,void *data);
		
			//lrange cmd callback:string_list_reply 
			int lrange(const string& key, int64_t start, int64_t stop,void *data);
		
			//lpushx cmd callback:integer_reply
			int lrem(const string& key, int count, const string& value,void *data);
		
			//lset cmd callback:status_reply
			int lset(const string& key, int index, const string& value,void *data);
		
			//ltrim cmd callback:status_reply
			int ltrim(const string& key, int start, int end,void *data);
		
			//rpop cmd callback:sting_reply
			int rpop(const string& key,void *data);
		
			//rpoplpush cmd callback:sting_reply
			int rpoplpush(const string& src, const string& dst,void *data);
		
			//rpush cmd callback:integer_reply
			int rpush(const string& key, const vector<string>& values,void *data);
			
			//rpushx cmd callback:integer_reply
			int rpushx(const string& key, const string& value,void *data);

			/***********************set cmd*****************************/
		
			//sadd cmd callback:integer_reply
			int sadd(const string& key, const vector<string>& members,void *data);
		
			//sadd cmd callback:integer_reply
			int scard(const string& key,void *data);
		
			//sdiff cmd callback:string_list_reply 
			int sdiff(const vector<string>& keys,void *data);
		
			//sdiffstore cmd callback:integer_reply
			int sdiffstore(const string& dst, const vector<string>& keys,void *data);
		
			//sinter cmd callback:string_list_reply 
			int sinter(const vector<string>& keys,void *data);
		
			//sinterstore cmd callback:integer_reply
			int sinterstore(const string& dst, const vector<string>& keys,void *data);
		
			//sismember cmd callback:integer_reply
			int sismember(const string& key, const string& member,void *data);
		
			//smembers cmd callback:string_list_reply 
			int smembers(const string& key,void *data);
		
			//smove cmd callback:integer_reply
			int smove(const string& src, const string& dst, const string& member,void *data);
		
			//spop cmd callback:string_reply
			int spop(const string& key,void *data);
			//int spop(const string& key, int count,void *data);
		
			//srandmember cmd callback:string_reply
			int srandmember(const string& key,void *data);
			
			//srandmember cmd callback:string_list_reply 
			int srandmember(const string& key, int count,void *data);
		
			//srem cmd callback:integer_reply
			int srem(const string& key, const vector<string>& members,void *data);
		
			//int sscan(const string &key,int64_t cursor) [match pattern] [count count]
		
			//sunion cmd callback:string_list_reply 
			int sunion(const vector<string>& keys,void *data);
		
			//sunionstore cmd callback:integer_reply
			int sunionstore(const string& dst, const vector<string>& keys,void *data);

			/***********************zset cmd*****************************/
		
			//zadd cmd callback:integer_reply
			int zadd(const string& key, const vector<pair<float, string> >& score_mem,void *data);
			
			//zcard cmd callback:integer_reply
			int zcard(const string& key,void *data);
	
			//zcount cmd callback:integer_reply.  min and max must can convert to float
			int zcount(const string& key, const string& min, const string& max,void *data);
		
			//zcard cmd callback:double_reply
			int zincrby(const string& key, const double incr, const string& member,void *data);
			
			//int zinterstore();
			//int zlexcount(const string& key, const string& min, const string& max,void *data);
		
			//zrange cmd.  callback:string_list_reply. if withscores is true callback:sd_map_reply 
			int zrange(const string& key, int start, int end, void *data,bool withscores = false);

			//int zrangebylex(const string& key, const string& min, const string& max,void *data) [limit offset count]
			
			//zrangebyscore cmd.zrangebyscore callback:string_list_reply. if withscores is true callback:sd_map_reply 
			int zrangebyscore(const string& key,const string& min, const string& max ,void *data,bool withscores = false);
			int zrangebyscore(const string& key,const string& min, const string& max ,int offset,int count,void *data,bool withscores = false);
		
			//zrank cmd callback:integer_reply.
			int zrank(const string& key, const string& member,void *data);
		
			//zrem cmd callback:integer_reply.
			int zrem(const string& key, const vector<string>& members,void *data);
		
			//int zremrangebylex(const string& key, const string& min, const string& max,void *data);
		
			//zremrangebyrank cmd callback:integer_reply.
			int zremrangebyrank(const string& key, int start, int stop,void *data);
		
			//zremrangebyscore cmd callback:integer_reply. min and max must can convert to float
			int zremrangebyscore(const string& key, const string& min, const string& max,void *data);
		
			//zrevrange cmd. zrange callback:string_list_reply. if withscores is true callback:sd_map_reply 
			int zrevrange(const string& key, int start, int stop,void *data,bool withscores = false);
			
			//int zrevrangebylex(const string& key, const string& min, const string& max,void *data) [limit offset count]

			//zrangebyscore cmd.zrangebyscore callback:string_list_reply. if withscores is true callback:sd_map_reply 
			int zrevrangebyscore(const string& key,const string& min, const string& max ,void *data,bool withscores = false);
			int zrevrangebyscore(const string& key,const string& min, const string& max ,int offset,int count,void *data,bool withscores = false);
		
			//zrevrank cmd callback:integer_reply.
			int zrevrank(const string& key, const string& member,void *data);
		
			//int zscan(const string &key,int64_t cursor) [match pattern] [count count]
		
			//zscore cmd callback:double_reply. // 
			int zscore(const string& key, const string& member,void *data);

			//int zunionstore();

			/***********************pub/sub redis cmd *****************************/

			//publish cmd callback:integer_reply
			int publish(const string& channel, const string& message,void *data);

			//psubscribe cmd callback:array_reply
			int psubscribe(const vector<string>& pattern,void *data);

			//subscribe cmd callback:array_reply
			int subscribe(const vector<string>& channels,void *data);

			//punsubscribe cmd.callback:array_reply  reply in psubscribe`s callback
			int punsubscribe(const vector<string>& pattern,void *data);

			//unsubscribe cmd.callback:array_reply reply in subscribe`s callback
			int unsubscribe(const vector<string>& channels,void *data);

			// pubsub channels callback:string_list_reply
			int pubsub_channels(const string& channel,void *data);

			//pubsub numsub cmd.callback:array_reply
			int pubsub_numsub(const vector<string>& channels,void *data);

			//pubsub numpat cmd callback:integer_reply
			int pubsub_numpat(void *data);

			/***********************raw redis cmd *****************************/
			//直接执行redis命令 当上述封装的命令不能满足要求时 可以使用这些接口执行特定redis命令
			
			int raw_redis_cmd(reply_type type,void *data,const char* cmd,...);
			int raw_redis_cmdargv(reply_type type,const vector<string> &cmd,void *data);
			
		private:
			cmd *m_pcmd;
	};
	
}