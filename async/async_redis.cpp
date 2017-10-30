#include "async_redis.h"


using namespace asyncredis;

int nb_redis::init(string &ip, int port, string &passwd,reply *r, struct ev_loop *loop)
{
	m_pcmd = new cmd();
	return m_pcmd->init(ip,port,passwd,r,loop);
}

int nb_redis::del(const vector<string>& keys,void *data)
{
	if(keys.empty())
	{
		return -1;
	}
	vector<string> cmd;
	cmd.push_back("del");
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::dump(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call dump %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "dump %s",key.c_str());
}

int nb_redis::exists(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call exists %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "exists %s",key.c_str());
}

int nb_redis::expire(const string& key, int seconds,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call expire %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "expire %s %d",key.c_str(),seconds);
}

int nb_redis::expireat(const string& key, int timestamp,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call expireat %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "expireat %s %u",key.c_str(),timestamp);
}

int nb_redis::keys(const string& pattern,void *data)
{
	if(pattern.empty())
	{
		return -1;
	}
	printf("call keys %s key \n",pattern.c_str());
	return m_pcmd->exec_command(em_slist_relpy,data,"keys %s",pattern.c_str());
}

int nb_redis::persist(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call persist %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "persist %s",key.c_str());
}

int nb_redis::pexpire(const string& key, int milliseconds,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call pexpire %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "pexpire %s %d",key.c_str(),milliseconds);
}

int nb_redis::pexpireat(const string& key, uint64_t mtimestamp,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call pexpireat %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "pexpireat %s %lu",key.c_str(),mtimestamp);
}

int nb_redis::pttl(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call pttl %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"pttl %s",key.c_str());
}

int nb_redis::randomkey(void *data)
{
	printf("call randomkey \n");
	return m_pcmd->exec_command(em_string_relpy,data,"randomkey");
}

int nb_redis::rename(const string& key, const string& newkey,void *data)
{
	if(key.empty() || newkey.empty())
	{
		return -1;
	}
	printf("call rename %s key \n",key.c_str());
	return m_pcmd->exec_command(em_status_reply,data,"rename %s %s",key.c_str(),newkey.c_str());
}

int nb_redis::renamenx(const string& key, const string& newkey,void *data)
{
	if(key.empty() || newkey.empty())
	{
		return -1;
	}
	printf("call renamenx %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"renamenx %s %s",key.c_str(),newkey.c_str());
}

int nb_redis::restore(const string& key, int ttl, const string& serialized_value,void *data,bool repalce /*= false*/)
{
	if(key.empty() || serialized_value.empty())
	{
		return -1;
	}
	printf("call restore %s key \n",key.c_str());
	if(repalce)
	{
		return m_pcmd->exec_command(em_status_reply,data,"restore %s %d %b replace",key.c_str(),ttl,serialized_value.c_str(),serialized_value.size());
	}
	return m_pcmd->exec_command(em_status_reply,data,"restore %s %d %b",key.c_str(),ttl,serialized_value.c_str(),serialized_value.size());
}

int nb_redis::ttl(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call ttl %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"ttl %s",key.c_str());
}

int nb_redis::type(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call type %s key \n",key.c_str());
	return m_pcmd->exec_command(em_type_relpy,data,"type %s",key.c_str());
}

int nb_redis::append(const string& key, const string& value,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call append %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"append %s %b",key.c_str(),value.c_str(),value.size());
}

int nb_redis::bitcount(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call bitcount %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"bitcount %s",key.c_str());
}

int nb_redis::bitcount(const string& key, int start, int end,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call bitcount %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"bitcount %s %d %d",key.c_str(),start,end);
}

int nb_redis::bitop(const string& op, const string& destkey, const std::vector<string>& keys,void *data)
{
	if(destkey.empty() || keys.empty())
	{
		return -1;
	}
	printf("call bitop %s key \n",destkey.c_str());
	vector<string> cmd;
	cmd.push_back("bitop");
	cmd.push_back(op);
	cmd.push_back(destkey);
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::bitpos(const string& key, int bit,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call bitpos %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"bitpos %s %d",key.c_str(),bit);
}

int nb_redis::bitpos(const string& key, int bit, int start,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call bitpos %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"bitpos %s %d %d",key.c_str(),bit,start);
}

int nb_redis::bitpos(const string& key, int bit, int start, int end,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call bitpos %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"bitpos %s %d %d %d",key.c_str(),bit,start,end);
}

int nb_redis::decr(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call decr %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"decr %s",key.c_str());
}

int nb_redis::decrby(const string& key, int64_t val,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call decrby %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"decrby %s %lld",key.c_str(),val);
}

int nb_redis::get(const std::string& key, void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call get %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "get %s",key.c_str());		
}

int nb_redis::getbit(const string& key, int offset,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call getbit %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data,"getbit %s %d",key.c_str(),offset);
}

int nb_redis::getrange(const string& key, int start, int end,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call getrange %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "getrange %s %d %d",key.c_str(),start,end);
}

int nb_redis::getset(const string& key, const string& val,void *data)
{
	if(key.empty() || val.empty())
	{
		return -1;
	}
	printf("call getset %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "getset %s %b",key.c_str(),val.c_str(),val.size());
}

int nb_redis::incr(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call incr %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "incr %s",key.c_str());
}

int nb_redis::incrby(const string& key, int64_t incr,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call incrby %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "incrby %s %lld",key.c_str(),incr);
}

int nb_redis::incrbyfloat(const string& key, float incr,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call incrbyfloat %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "incrbyfloat %s %f",key.c_str(),incr);
}

int nb_redis::mget(const vector<string>& keys,void *data)
{
	if(keys.empty())
	{
		return -1;
	}
	vector<string> cmd;
	cmd.push_back("mget");
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_slist_relpy,data, cmd);
}

int nb_redis::mset(const vector<pair<string, string> >& key_vals,void *data)
{
	if(key_vals.empty())
	{
		return -1;
	}
	vector<string> cmd;
	cmd.push_back("mset");
	vector<pair<string, string> >::const_iterator it = key_vals.begin();
	for(;it != key_vals.end();++it)
	{
		cmd.push_back(it->first);
		cmd.push_back(it->second);
	}
	return m_pcmd->exec_commandargv(em_status_reply,data, cmd);
}

int nb_redis::msetnx(const vector<pair<string, string> >& key_vals,void *data)
{
	if(key_vals.empty())
	{
		return -1;
	}
	vector<string> cmd;
	cmd.push_back("msetnx");
	vector<pair<string, string> >::const_iterator it = key_vals.begin();
	for(;it != key_vals.end();++it)
	{
		cmd.push_back(it->first);
		cmd.push_back(it->second);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
	/*string cmd = "msetnx";
	vector<pair<string, string> >::const_iterator it = key_vals.begin();
	for(;it != key_vals.end();++it)
	{
		cmd = cmd + delimiter + quotation_mark + it->first + quotation_mark + delimiter + quotation_mark + it->second + quotation_mark;
	}
	return m_pcmd->exec_command(em_integer_relpy,data, cmd.c_str());*/
}

int nb_redis::psetex(const string& key, int milliseconds, const string& val,void *data)
{
	if(key.empty() || val.empty())
	{
		return -1;
	}
	printf("call psetex %s key \n",key.c_str());
	return m_pcmd->exec_command(em_status_reply,data, "psetex %s %d %b",key.c_str(),milliseconds,val.c_str(),val.size());
}

int nb_redis::set(const string& key, const string& value,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call set %s key \n",key.c_str());
	return m_pcmd->exec_command(em_status_reply,data, "set %s %b",key.c_str(),value.c_str(),value.size());
}

int nb_redis::set(const string& key, const string& value,expire_unit unit, int time,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call set %s key \n",key.c_str());
	string con;
	con = (unit == em_sec) ? "ex" : "px";
	return m_pcmd->exec_command(em_status_reply,data, "set %s %b %s %d",key.c_str(),value.c_str(),value.size(),con.c_str(),time);
}

int nb_redis::set(const string& key, const string& value,expire_unit unit, int time,string_set_type nx,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call set %s key \n",key.c_str());
	string con;
	con = (unit == em_sec) ? "ex" : "px";
	string excon;
	excon = (nx == em_set_nx) ? "nx" : "xx";
	return m_pcmd->exec_command(em_status_reply,data, "set %s %b %s %d %s",key.c_str(),value.c_str(),value.size(),con.c_str(),time,excon.c_str());
}

int nb_redis::setbit(const string& key, int offset,int value, void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call setbit %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "setbit %s %d %d",key.c_str(),offset,value);
}

int nb_redis::setex(const string& key, int seconds, const string& value,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call setex %s key \n",key.c_str());
	return m_pcmd->exec_command(em_status_reply,data, "setex %s %d %b",key.c_str(),seconds,value.c_str(),value.size());
}

int nb_redis::setnx(const string& key, const string& value,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call setnx %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "setnx %s %b",key.c_str(),value.c_str(),value.size());
}

int nb_redis::setrange(const string& key, int offset, const string& value,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call setrange %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "setrange %s %d %b",key.c_str(),offset,value.c_str(),value.size());
}

int nb_redis::strlen(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call strlen %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "strlen %s",key.c_str());
}

int nb_redis::hdel(const string& key, const vector<string>& fields,void *data)
{
	if(key.empty() || fields.empty())
	{
		return -1;
	}
	printf("call hdel %s key \n",key.c_str());
	vector<string> cmd;
	cmd.push_back("hdel");
	cmd.push_back(key);
	vector<string>::const_iterator it = fields.begin();
	for(;it != fields.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::hexists(const string& key, const string& field,void *data)
{
	if(key.empty() || field.empty())
	{
		return -1;
	}
	printf("call hexists %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "hexists %s %s",key.c_str(),field.c_str());
}

int nb_redis::hget(const string& key, const string& field,void *data)
{
	if(key.empty() || field.empty())
	{
		return -1;
	}
	printf("call hget %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "hget %s %s",key.c_str(),field.c_str());
}

int nb_redis::hgetall(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call hgetall %s key \n",key.c_str());
	return m_pcmd->exec_command(em_ss_map_reply,data, "hgetall %s",key.c_str());
}

int nb_redis::hincrby(const string& key, const string& field, int64_t incr,void *data)
{
	if(key.empty() || field.empty())
	{
		return -1;
	}
	printf("call hincrby %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "hincrby %s %s %ld",key.c_str(),field.c_str(),incr);
}

int nb_redis::hincrbyfloat(const string& key, const string& field, float incr,void *data)
{
	if(key.empty() || field.empty())
	{
		return -1;
	}
	printf("call hincrbyfloat %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "hincrbyfloat %s %s %f",key.c_str(),field.c_str(),incr);
}

int nb_redis::hkeys(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call hkeys %s key \n",key.c_str());
	return m_pcmd->exec_command(em_slist_relpy,data, "hkeys %s",key.c_str());
}

int nb_redis::hlen(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call hlen %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "hlen %s",key.c_str());
}

int nb_redis::hmget(const string& key, const vector<string>& fields,void *data)
{	
	if(key.empty() || fields.empty())
	{
		return -1;
	}
	printf("call hmget %s key \n",key.c_str());
	vector<string> cmd;
	cmd.push_back("hmget");
	cmd.push_back(key);
	vector<string>::const_iterator it = fields.begin();
	for(;it != fields.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_slist_relpy,data, cmd);
}

int nb_redis::hmset(const string& key, const vector<pair<string, string> >& field_val,void *data)
{
	if(key.empty() || field_val.empty())
	{
		return -1;
	}
	printf("call hmset %s key \n",key.c_str());
	vector<string> cmd;
	cmd.push_back("hmset");
	cmd.push_back(key);
	vector<pair<string, string> >::const_iterator it = field_val.begin();
	for(;it != field_val.end();++it)
	{
		cmd.push_back(it->first);
		cmd.push_back(it->second);
	}
	return m_pcmd->exec_commandargv(em_status_reply,data, cmd);
}

int nb_redis::hset(const string& key, const string& field, const string& value,void *data)
{
	if(key.empty() || field.empty() || value.empty())
	{
		return -1;
	}
	printf("call hset %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "hset %s %s %b",key.c_str(),field.c_str(),value.c_str(),value.size());
}

int nb_redis::hsetnx(const string& key, const string& field, const string& value,void *data)
{
	if(key.empty() || field.empty() || value.empty())
	{
		return -1;
	}
	printf("call hsetnx %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "hsetnx %s %s %b",key.c_str(),field.c_str(),value.c_str(),value.size());
}

int nb_redis::hvals(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call hvals %s key \n",key.c_str());
	return m_pcmd->exec_command(em_slist_relpy,data, "hvals %s",key.c_str());
}

int nb_redis::blpop(const vector<string>& keys, int timeout,void *data)
{
	if(keys.empty())
	{
		return -1;
	}
	printf("call blpop\n");
	vector<string> cmd;
	cmd.push_back("blpop");
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	cmd.push_back(tostring(timeout));
	return m_pcmd->exec_commandargv(em_ss_map_reply,data, cmd);
}

int nb_redis::brpop(const vector<string>& keys, int timeout,void *data)
{	
	if(keys.empty())
	{
		return -1;
	}
	printf("call brpop\n");
	vector<string> cmd;
	cmd.push_back("brpop");
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	cmd.push_back(tostring(timeout));
	return m_pcmd->exec_commandargv(em_ss_map_reply,data, cmd);
}

int nb_redis::brpoplpush(const string& src, const string& dst, int timeout,void *data)
{
	if(src.empty() || dst.empty())
	{
		return -1;
	}
	printf("call brpoplpush %s key \n",src.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "brpoplpush %s %s %d",src.c_str(),dst.c_str(),timeout);
}

int nb_redis::lindex(const string& key, int64_t index,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call lindex %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "lindex %s %lld",key.c_str(),index);
}

int nb_redis::linsert(const string& key, const list_insert_type type, const string& pivot, const string& value,void *data)
{
	if(key.empty() || pivot.empty() || value.empty())
	{
		return -1;
	}
	printf("call linsert %s key \n",key.c_str());
	string stype = (type == em_insert_before) ? "before" : "after";
	return m_pcmd->exec_command(em_integer_relpy,data, "linsert %s %s %s %b",key.c_str(),stype.c_str(),pivot.c_str(),value.c_str(),value.size());
}

int nb_redis::llen(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call llen %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "llen %s",key.c_str());
}

int nb_redis::lpop(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call lpop %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "lpop %s",key.c_str());
}

int nb_redis::lpush(const string& key, const vector<string>& values,void *data)
{
	if(key.empty() || values.empty())
	{
		return -1;
	}
	printf("call lpush %s key \n",key.c_str());
	vector<string> cmd;
	cmd.push_back("lpush");
	cmd.push_back(key);
	vector<string>::const_iterator it = values.begin();
	for(;it != values.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::lpushx(const string& key, const string& value,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call lpushx %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "lpushx %s %b",key.c_str(),value.c_str(),value.size());
}

int nb_redis::lrange(const string& key, int64_t start, int64_t stop,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call lrange %s key \n",key.c_str());
	return m_pcmd->exec_command(em_slist_relpy,data, "lrange %s %lld %lld",key.c_str(),start,stop);
}

int nb_redis::lrem(const string& key, int count, const string& value,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call lrem %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "lrem %s %d %b",key.c_str(),count,value.c_str(),value.size());
}

int nb_redis::lset(const string& key, int index, const string& value,void *data)
{
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call lset %s key \n",key.c_str());
	return m_pcmd->exec_command(em_status_reply,data, "lset %s %d %b",key.c_str(),index,value.c_str(),value.size());
}

int nb_redis::ltrim(const string& key, int start, int end,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call ltrim %s key \n",key.c_str());
	return m_pcmd->exec_command(em_status_reply,data, "ltrim %s %d %d",key.c_str(),start,end);
}

int nb_redis::rpop(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call rpop %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "rpop %s",key.c_str());
}

int nb_redis::rpoplpush(const string& src, const string& dst,void *data)
{
	if(src.empty() || dst.empty())
	{
		return -1;
	}
	printf("call rpoplpush %s key \n",src.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "rpoplpush %s %s",src.c_str(),dst.c_str());
}

int nb_redis::rpush(const string& key, const vector<string>& values,void *data)
{	
	if(key.empty() || values.empty())
	{
		return -1;
	}
	printf("call rpush %s key \n",key.c_str());
	vector<string> cmd;
	cmd.push_back("rpush");
	cmd.push_back(key);
	vector<string>::const_iterator it = values.begin();
	for(;it != values.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::rpushx(const string& key, const string& value,void *data)
{	
	if(key.empty() || value.empty())
	{
		return -1;
	}
	printf("call rpushx %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "rpushx %s %b",key.c_str(),value.c_str(),value.size());
}

int nb_redis::sadd(const string& key, const vector<string>& members,void *data)
{
	if(key.empty() || members.empty())
	{
		return -1;
	}
	printf("call sadd %s key \n",key.c_str());
	vector<string> cmd;
	cmd.push_back("sadd");
	cmd.push_back(key);
	vector<string>::const_iterator it = members.begin();
	for(;it != members.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::scard(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call scard %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "scard %s",key.c_str());
}

int nb_redis::sdiff(const vector<string>& keys,void *data)
{
	if(keys.empty())
	{
		return -1;
	}
	printf("call sdiff \n");
	vector<string> cmd;
	cmd.push_back("sdiff");
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_slist_relpy,data, cmd);
}

int nb_redis::sdiffstore(const string& dst, const vector<string>& keys,void *data)
{
	if(dst.empty() || keys.empty())
	{
		return -1;
	}
	printf("call sdiffstore \n");
	vector<string> cmd;
	cmd.push_back("sdiffstore");
	cmd.push_back(dst);
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::sinter(const vector<string>& keys,void *data)
{
	if(keys.empty())
	{
		return -1;
	}
	printf("call sinter \n");
	vector<string> cmd;
	cmd.push_back("sinter");
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_slist_relpy,data, cmd);
}

int nb_redis::sinterstore(const string& dst, const vector<string>& keys,void *data)
{
	if(dst.empty() || keys.empty())
	{
		return -1;
	}
	printf("call sinterstore \n");
	vector<string> cmd;
	cmd.push_back("sinterstore");
	cmd.push_back(dst);
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::sismember(const string& key, const string& member,void *data)
{
	if(key.empty() || member.empty())
	{
		return -1;
	}
	printf("call sismember %s key \n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "sismember %s %s",key.c_str(),member.c_str());
}

int nb_redis::smembers(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call smembers %s key \n",key.c_str());
	return m_pcmd->exec_command(em_slist_relpy,data, "smembers %s",key.c_str());
}

int nb_redis::smove(const string& src, const string& dst, const string& member,void *data)
{
	if(src.empty() || dst.empty() || member.empty())
	{
		return -1;
	}
	printf("call smove %s key \n",src.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "smove %s %s %s",src.c_str(),dst.c_str(),member.c_str());
}

int nb_redis::spop(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call spop %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "spop %s",key.c_str());
}

int nb_redis::srandmember(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call srandmember %s key \n",key.c_str());
	return m_pcmd->exec_command(em_string_relpy,data, "srandmember %s",key.c_str());
}

int nb_redis::srandmember(const string& key, int count,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call srandmember %s %d \n",key.c_str(),count);
	return m_pcmd->exec_command(em_slist_relpy,data, "srandmember %s %d",key.c_str(),count);
}

int nb_redis::srem(const string& key, const vector<string>& members,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call srem %s key \n",key.c_str());
	vector<string> cmd;
	cmd.push_back("srem");
	cmd.push_back(key);
	vector<string>::const_iterator it = members.begin();
	for(;it != members.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::sunion(const vector<string>& keys,void *data)
{
	if(keys.empty())
	{
		return -1;
	}
	printf("call sunion \n");
	vector<string> cmd;
	cmd.push_back("sunion");
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_slist_relpy,data, cmd);
}

int nb_redis::sunionstore(const string& dst, const vector<string>& keys,void *data)
{
	if(dst.empty() || keys.empty())
	{
		return -1;
	}
	printf("call sunionstore \n");
	vector<string> cmd;
	cmd.push_back("sunionstore");
	cmd.push_back(dst);
	vector<string>::const_iterator it = keys.begin();
	for(;it != keys.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::zadd(const string& key, const vector<pair<float, string> >& score_mem,void *data)
{
	if(key.empty() || score_mem.empty())
	{
		return -1;
	}
	printf("call zadd %s key \n",key.c_str());
	vector<string> cmd;
	cmd.push_back("zadd");
	cmd.push_back(key);
	vector<pair<float, string> >::const_iterator it = score_mem.begin();
	for(;it != score_mem.end();++it)
	{
		cmd.push_back(tostring(it->first));
		cmd.push_back(it->second);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::zcard(const string& key,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call zcard %s\n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "zcard %s",key.c_str());
}

int nb_redis::zcount(const string& key, const string& min, const string& max,void *data)
{
	if(key.empty() || min.empty() || max.empty())
	{
		return -1;
	}
	printf("call zcount %s\n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "zcount %s %s %s",key.c_str(),min.c_str(),max.c_str());
}

int nb_redis::zincrby(const string& key, const double incr, const string& member,void *data)
{
	if(key.empty() || member.empty())
	{
		return -1;
	}
	printf("call zincrby %s\n",key.c_str());
	return m_pcmd->exec_command(em_double_relpy,data, "zincrby %s %f %s",key.c_str(),incr,member.c_str());
}

int nb_redis::zrange(const string& key, int start, int end, void *data,bool withscores /*= false*/)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call zrange %s\n",key.c_str());
	if(withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply,data, "zrange %s %d %d %s",key.c_str(),start,end,"withscores");
	}
	return m_pcmd->exec_command(em_slist_relpy,data, "zrange %s %d %d",key.c_str(),start,end);
}


int nb_redis::zrangebyscore(const string& key,const string& min, const string& max ,void *data,bool withscores /*= false*/)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call zrangebyscore %s\n",key.c_str());
	if(withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply,data, "zrangebyscore %s %s %s %s",key.c_str(),min.c_str(),max.c_str(),"withscores");
	}
	return m_pcmd->exec_command(em_slist_relpy,data, "zrangebyscore %s %s %s",key.c_str(),min.c_str(),max.c_str());
}

int nb_redis::zrangebyscore(const string& key,const string& min, const string& max ,int offset,int count,void *data,bool withscores /*= false*/)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call zrangebyscore with limit %s\n",key.c_str());
	if(withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply,data, "zrangebyscore %s %s %s %s limit %d %d",key.c_str(),min.c_str(),max.c_str(),"withscores",offset,count);
	}
	return m_pcmd->exec_command(em_slist_relpy,data, "zrangebyscore %s %s %s limit %d %d",key.c_str(),min.c_str(),max.c_str(),offset,count);
}

int nb_redis::zrank(const string& key, const string& member,void *data)
{
	if(key.empty() || member.empty())
	{
		return -1;
	}
	printf("call zrank %s\n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "zrank %s %s",key.c_str(),member.c_str());	
}

int nb_redis::zrem(const string& key, const vector<string>& members,void *data)
{
	if(key.empty() || members.empty())
	{
		return -1;
	}
	printf("call zrem %s key\n",key.c_str());
	vector<string> cmd;
	cmd.push_back("zrem");
	cmd.push_back(key);
	vector<string>::const_iterator it = members.begin();
	for(;it != members.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_integer_relpy,data, cmd);
}

int nb_redis::zremrangebyrank(const string& key, int start, int stop,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call zremrangebyrank %s\n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "zremrangebyrank %s %d %d",key.c_str(),start,stop);	
}

int nb_redis::zremrangebyscore(const string& key, const string& min, const string& max,void *data)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call zremrangebyscore %s\n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "zremrangebyscore %s %s %s",key.c_str(),min.c_str(),max.c_str());
}

int nb_redis::zrevrange(const string& key, int start, int stop,void *data,bool withscores /*= false*/)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call zrevrange %s\n",key.c_str());
	if(withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply,data, "zrevrange %s %d %d %s",key.c_str(),start,stop,"withscores");
	}
	return m_pcmd->exec_command(em_slist_relpy,data, "zrevrange %s %d %d",key.c_str(),start,stop);
}

int nb_redis::zrevrangebyscore(const string& key,const string& min, const string& max ,void *data,bool withscores /*= false*/)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call zrevrangebyscore %s\n",key.c_str());
	if(withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply,data, "zrevrangebyscore %s %s %s %s",key.c_str(),min.c_str(),max.c_str(),"withscores");
	}
	return m_pcmd->exec_command(em_slist_relpy,data, "zrevrangebyscore %s %s %s",key.c_str(),min.c_str(),max.c_str());
}

int nb_redis::zrevrangebyscore(const string& key,const string& min, const string& max ,int offset,int count,void *data,bool withscores /*= false*/)
{
	if(key.empty())
	{
		return -1;
	}
	printf("call zrevrangebyscore with limit %s\n",key.c_str());
	if(withscores)
	{
		// to do sd_map_reply
		return m_pcmd->exec_command(em_sd_map_reply,data, "zrevrangebyscore %s %s %s %s limit %d %d",key.c_str(),min.c_str(),max.c_str(),"withscores",offset,count);
	}
	return m_pcmd->exec_command(em_slist_relpy,data, "zrevrangebyscore %s %s %s limit %d %d",key.c_str(),min.c_str(),max.c_str(),offset,count);
}

int nb_redis::zrevrank(const string& key, const string& member,void *data)
{
	if(key.empty() || member.empty())
	{
		return -1;
	}
	printf("call zrevrank %s\n",key.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "zrevrank %s %s",key.c_str(),member.c_str());	
}

int nb_redis::zscore(const string& key, const string& member,void *data)
{
	if(key.empty() || member.empty())
	{
		return -1;
	}
	printf("call zscore %s\n",key.c_str());
	return m_pcmd->exec_command(em_double_relpy,data, "zscore %s %s",key.c_str(),member.c_str());
}

int nb_redis::publish(const string& channel, const string& message,void *data)
{
	if(channel.empty() || message.empty())
	{
		return -1;
	}
	printf("call publish %s %s\n",channel.c_str(),message.c_str());
	return m_pcmd->exec_command(em_integer_relpy,data, "publish %s %b",channel.c_str(),message.c_str(),message.size());
}

int nb_redis::psubscribe(const vector<string>& pattern,void *data)
{
	if(pattern.empty())
	{
		return -1;
	}
	printf("call psubscribe \n");
	vector<string> cmd;
	cmd.push_back("psubscribe");
	vector<string>::const_iterator it = pattern.begin();
	for(;it != pattern.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply,data, cmd);
}

int nb_redis::subscribe(const vector<string>& channels,void *data)
{
	if(channels.empty())
	{
		return -1;
	}
	printf("call subscribe \n");
	vector<string> cmd;
	cmd.push_back("subscribe");
	vector<string>::const_iterator it = channels.begin();
	for(;it != channels.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply,data, cmd);
}

int nb_redis::punsubscribe(const vector<string>& pattern,void *data)
{
	printf("call punsubscribe \n");
	vector<string> cmd;
	cmd.push_back("punsubscribe");
	vector<string>::const_iterator it = pattern.begin();
	for(;it != pattern.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply,data, cmd);
}

int nb_redis::unsubscribe(const vector<string>& pattern,void *data)
{
	printf("call unsubscribe \n");
	vector<string> cmd;
	cmd.push_back("unsubscribe");
	vector<string>::const_iterator it = pattern.begin();
	for(;it != pattern.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply,data, cmd);
}

int nb_redis::pubsub_channels(const string& channel,void *data)
{
	printf("call pubsub_channels %s\n",channel.c_str());
	if(channel.empty())
	{
		return m_pcmd->exec_command(em_slist_relpy,data, "pubsub channels");
	}
	return m_pcmd->exec_command(em_slist_relpy,data, "pubsub channels %s",channel.c_str());
}

int nb_redis::pubsub_numsub(const vector<string>& channels,void *data)
{
	printf("call pubsub_numsub\n");
	vector<string> cmd;
	cmd.push_back("pubsub");
	cmd.push_back("numsub");
	vector<string>::const_iterator it = channels.begin();
	for(;it != channels.end();++it)
	{
		cmd.push_back(*it);
	}
	return m_pcmd->exec_commandargv(em_array_reply,data, cmd);
}

int nb_redis::pubsub_numpat(void *data)
{
	printf("call pubsub_numpat \n");
	return m_pcmd->exec_command(em_integer_relpy,data, "pubsub numpat");
}

int nb_redis::raw_redis_cmd(reply_type type,void *data,const char* cmd,...)
{
	redisCallbackFn *fn = m_pcmd->get_callback(type);
	if(!fn)
	{
		printf("unknow reply type %d\n",type);
		return -1;
	}
	connection *pconn = m_pcmd->get_conn();
	if(!pconn)
	{
		printf("get connection failed \n");
		return -1;	
	}
	if(!pconn->valid_conn()) //连接无效
	{
		printf("connection invalid \n");
		pconn->try_connect();
		return -1;
	}
	redisAsyncContext* ac = pconn->get_redis_cx();
	va_list ap;
	int status;
	va_start(ap,cmd);
	status = redisvAsyncCommand(ac,fn,data,cmd,ap);
	va_end(ap);
	return status;
}

int nb_redis::raw_redis_cmdargv(reply_type type,const vector<string> &cmd,void *data)
{	
	return m_pcmd->exec_commandargv(type,data, cmd);
}