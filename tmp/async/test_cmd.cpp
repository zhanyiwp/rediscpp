/*
 * =====================================================================================
 *
 *       Filename:  test_cmd.cpp
 *
 *    Description:  命令测试 测试封装的每一个命令                                                                                                                                                          
 *
 *        Version:  1.0
 *        Created:  06/10/2017 02:45:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ZHANYI (ZY), zhanyiwp@163.com
 *   Organization:  ec
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "async_redis.h"
#include "async_reply.h"
#include "async_conn.h"
#include "async_cmd.h"

#include "ev.h"

using namespace asyncredis;

struct ev_loop *g_loop = EV_DEFAULT;

nb_redis redisclient;

class redis_reply_handler:public reply
{
    virtual void string_reply(reply_status result,const string &r, void *privdata)
    {
        if(REPLY_TYPE_OK == result)
        {
            printf("get %s %s privdata:%s\n",__func__,r.c_str(),(char*)privdata);
            //redisclient.restore("restore_test",0,r,(void *)"restore test");
            //redisclient.restore("restore_test",0,r,(void *)"restore true test",true);
        }
        else
        {
            string errinfo;
            int err = get_error_info(errinfo);
            printf("get %s err %d(%s) privdata:%s\n",__func__,err,errinfo.c_str(),(char*)privdata);
        }
    }
    virtual void status_reply(reply_status result, const bool r, void *privdata)
    {
        if(REPLY_TYPE_OK == result)
        {
            printf("get %s OK privdata:%s\n",__func__,(char*)privdata);
        }
        else
        {
            string errinfo;
            int err = get_error_info(errinfo);
            printf("get %s err %d(%s) privdata:%s\n",__func__,err,errinfo.c_str(),(char*)privdata);
        }
    }
	
    virtual void integer_reply(reply_status result, const int64_t r, void *privdata)
    {
        if(REPLY_TYPE_OK == result)
        {
            printf("get %s %ld privdata:%s\n",__func__,r,(char*)privdata);
        }
        else
        {
            string errinfo;
            int err = get_error_info(errinfo);
            printf("get %s err %d(%s) privdata:%s\n",__func__,err,errinfo.c_str(),(char*)privdata);
        }
    }
	
    virtual void double_reply(reply_status result, const double r, void *privdata)
    {
        if(REPLY_TYPE_OK == result)
        {
            printf("get %s %f privdata:%s\n",__func__,r,(char*)privdata);
        }
        else
        {
            string errinfo;
            int err = get_error_info(errinfo);
            printf("get %s err %d(%s) privdata:%s\n",__func__,err,errinfo.c_str(),(char*)privdata);
        }
    }

    virtual void string_list_reply(reply_status result, const vector<string> &r, void *privdata)
    {
        if(REPLY_TYPE_OK == result)
        {
            printf("get %s success size %lu privdata:%s\n",__func__,r.size(),(char*)privdata);
            vector<string>::const_iterator it = r.begin();
            for(;it != r.end();++it)
            {
                printf("%s\n",it->c_str());
            }
        }
        else
        {
            string errinfo;
            int err = get_error_info(errinfo);
            printf("get %s err %d(%s) privdata:%s\n",__func__,err,errinfo.c_str(),(char*)privdata);
        }
    }

	virtual void ss_map_reply(reply_status result, const map<string,string> &r, void *privdata)
    {
        if(REPLY_TYPE_OK == result)
        {
            printf("get %s success size %lu privdata:%s\n",__func__,r.size(),(char*)privdata);
            map<string,string>::const_iterator it = r.begin();
            for(;it != r.end();++it)
            {
                printf("%s %s\n",it->first.c_str(),it->second.c_str());
            }
        }
        else
        {
            string errinfo;
            int err = get_error_info(errinfo);
            printf("get %s err %d(%s) privdata:%s\n",__func__,err,errinfo.c_str(),(char*)privdata);
        }
    }

    virtual void sd_map_reply(reply_status result, const map<string,double> &r, void *privdata)
    {
        if(REPLY_TYPE_OK == result)
        {
            printf("get %s success size %lu privdata:%s\n",__func__,r.size(),(char*)privdata);
            map<string,double>::const_iterator it = r.begin();
            for(;it != r.end();++it)
            {
                printf("%s %f\n",it->first.c_str(),it->second);
            }
        }
        else
        {
            string errinfo;
            int err = get_error_info(errinfo);
            printf("get %s err %d(%s) privdata:%s\n",__func__,err,errinfo.c_str(),(char*)privdata);
        }
    }

    virtual void array_reply(reply_status result, const array_data &r, void *privdata)
    {
        if(REPLY_TYPE_OK == result)
        {
            printf("get %s success privdata:%s\n",__func__,(char*)privdata);
            array_data::const_iterator it = r.begin();
            for(;it != r.end();++it)
            {
                if(it->type == REDIS_REPLY_STRING || it->type == REDIS_REPLY_STATUS  || it->type == REDIS_REPLY_ERROR )
                {
                    printf("%s\n",it->str.c_str());
                }
                else if(it->type == REDIS_REPLY_INTEGER)
                {
                    printf("%ld\n",it->integer);
                }
                else if(it->type == REDIS_REPLY_NIL)
                {
                     printf("get nill result\n");
                }
            }
        }
        else
        {
            string errinfo;
            int err = get_error_info(errinfo);
            printf("get %s err %d(%s) privdata:%s\n",__func__,err,errinfo.c_str(),(char*)privdata);
        }
    }

    virtual void raw_reply(reply_status result,const redisReply *r, void *privdata)
    {
        printf("get %s success privdata:%s\n",__func__,(char*)privdata);
    }
};



void timeout_cb (EV_P_ ev_timer *w, int revents)
{
        /****************************key cmd test **********************/
       #if 1
        vector<string> k;
        k.push_back("del_test1");
        k.push_back("del_test2");
        k.push_back("del_test3");
        redisclient.del(k,(void *)"del test");
        redisclient.dump("dump_test",(void *)"dump test");
        redisclient.exists("exists_test",(void *)"exists test");
        redisclient.expire("expire_test",100,(void *)"expire test");
        redisclient.expireat("expire_test",time(NULL) + 100,(void *)"expireat test");
        redisclient.keys("zhanyi*",(void *)"keys test");
        redisclient.persist("expire_test",(void *)"persist test");
        redisclient.pexpire("expire_test",1000 * 100,(void *)"pexpire test");
        redisclient.pexpireat("expire_test",1555555555005,(void *)"pexpireat test");
        redisclient.pttl("expire_test",(void *)"pttl test");
        redisclient.rename("rename_test","rename_new",(void *)"rename test");
        redisclient.renamenx("rename_test","rename_new",(void *)"renamenx test");
        redisclient.dump("dump_test",(void *)"dump test");
        redisclient.restore("restore_test",0,"\x00\tdump_test\x06\x00+E\x95O\x82V\x16\xe7",(void *)"restore test");
        redisclient.restore("restore_test",0,"\x00\tdump_test\x06\x00+E\x95O\x82V\x16\xe7",(void *)"restore true test",true);
        redisclient.ttl("expire_test",(void *)"ttl test");
        redisclient.type("dump_test",(void *)"type test");


         /****************************string cmd test **********************/

         redisclient.append("append_test"," 123",(void *)"append test");
         redisclient.bitcount("append_test",(void *)"bitcount test");
         redisclient.bitcount("append_test",1,3,(void *)"bitcount with start test");
         vector<string> k1;
         k1.push_back("bitop_test1");
         k1.push_back("bitop_test2");
         k1.push_back("bitop_test3");
         redisclient.bitop("AND","bitop_test",k1,(void *)"bitcount test");
         redisclient.bitop("OR","bitop_test",k1,(void *)"bitcount test");
         redisclient.bitop("XOR","bitop_test",k1,(void *)"bitcount test");
         redisclient.bitop("NOT","bitop_test",k1,(void *)"bitcount test");
         redisclient.bitop("lalals","bitop_test",k,(void *)"bitcount test");
         redisclient.bitpos("append_test",1,(void *)"bitpos 1 test");
         redisclient.bitpos("append_test",0,(void *)"bitpos 0 test");
         redisclient.bitpos("append_test",1,1,3,(void *)"bitpos 1 1 3 test");
         redisclient.bitpos("append_test",0,1,3,(void *)"bitpos 0 1 3 test");
         redisclient.bitpos("append_test",2,(void *)"bitpos 2 test");
         redisclient.decr("decr_test",(void *)"decr  test");
         redisclient.decrby("decr_test",20,(void *)"decrby  test");
         redisclient.get("get_test",(void *)"get  test");
         redisclient.getbit("get_test",2,(void *)"getbit  test");
         redisclient.getrange("get_test",4,8,(void *)"getrange  test");
         redisclient.getset("get_test","33333333",(void *)"getset  test");
         redisclient.incr("decr_test",(void *)"incr  test");
         redisclient.incrby("decr_test",40,(void *)"incrby  test");  
         redisclient.incrbyfloat("decr_test",23.3,(void *)"incrbyfloat  test"); 
        
         vector<pair<string, string> >kv;
         pair<string, string> pair1;
         pair<string, string> pair2;
         pair<string, string> pair3;
         pair1 = make_pair("mset_test1", "mset_test1 value !!!!");
         pair2 = make_pair("mset_test2", "mset_test2 value !!!!");
         pair3 = make_pair("mset_test3", "mset_test3 value !!!!");
         kv.push_back(pair1);
         kv.push_back(pair2);
         kv.push_back(pair3);
         redisclient.mset(kv,(void *)"mset  test");
         vector<string> k2;
         k2.push_back("mset_test1");
         k2.push_back("mset_test2");
         k2.push_back("mset_test3");
         k2.push_back("mset_test4");
         redisclient.mget(k2,(void *)"mget test");
         redisclient.msetnx(kv,(void *)"msetnx  test");
         redisclient.psetex("psetex_test",1000*1000,"pset ex value",(void *)"psetex  test");
         redisclient.set("set test","set test value",(void *)"set 1000 test");
         redisclient.set("set test11","set test11 value",em_sec,1000,(void *)"set 1000 test");
         redisclient.set("set test22","set test22 value",em_sec,1000,em_set_nx,(void *)"set 1000 test");
         redisclient.setbit("setbit",2,1,(void *)"setbit  1 test");
         redisclient.setbit("setbit",2,0,(void *)"setbit  0 test");
         redisclient.setbit("setbit",2,2,(void *)"setbit  2 test");
         redisclient.setex("setex test",1000,"setex test value",(void *)"setex 1000 test");
         redisclient.setnx("setnx test","setnx test value",(void *)"setnx test");
         redisclient.setrange("setrange test",2,"setrange test 2",(void *)"setrange test");
         redisclient.strlen("strlen test",(void *)"strlen test");
       

         /****************************hash cmd test **********************/

         vector<pair<string, string> >kv1;
         pair<string, string> pair11;
         pair<string, string> pair22;
         pair<string, string> pair33;
         pair11 = make_pair("hash_test1", "hash_test1 value !!!!");
         pair22 = make_pair("hash_test2", "hash_test2 value !!!!");
         pair33 = make_pair("hash_test3", "hash_test3 value !!!!");
         kv1.push_back(pair11);
         kv1.push_back(pair22);
         kv1.push_back(pair33);
         redisclient.hmset("hash_test",kv1,(void *)"hmset test");
         redisclient.hset("hash_test","hash_test4","hash_test4 value !!!!",(void *)"hset test");
         redisclient.hsetnx("hash_test","hash_test5","hash_test5 value !!!!",(void *)"hsetnx test");
         redisclient.hexists("hash_test","hash_test1",(void *)"hexists test");
         redisclient.hget("hash_test","hash_test1",(void *)"hget test");
         redisclient.hincrby("hash_test","hash_test6",20,(void *)"hincrby test");
         redisclient.hincrbyfloat("hash_test","hash_test7",20.7,(void *)"hincrbyfloat test");
         redisclient.hgetall("hash_test",(void *)"hgetall test");
         redisclient.hkeys("hash_test",(void *)"hkeys test");
         redisclient.hvals("hash_test",(void *)"hvals test");
         redisclient.hlen("hash_test",(void *)"hlen test");
         vector<string> k3;
         k3.push_back("hash_test1");
         k3.push_back("hash_test2");
         k3.push_back("hash_test3");
         k3.push_back("hash_test4");
         redisclient.hdel("hash_test",k3,(void *)"hdel test");
         redisclient.hgetall("hash_test",(void *)"hgetall test");
        
       /****************************list cmd test **********************/
        vector<string> k4;
        k4.push_back("list_test1");
        k4.push_back("list_test2");
        k4.push_back("list_test3");
        k4.push_back("list_test4");
        redisclient.lpush("list_test",k4,(void *)"lpush test");
        redisclient.lpushx("list_test","list_test5",(void *)"lpushx test");
        redisclient.llen("list_test",(void *)"llen test");
        redisclient.lrange("list_test",0 ,-1,(void *)"lrange test");
        redisclient.lindex("list_test",6,(void *)"lindex test");
        redisclient.linsert("list_test",em_insert_before,"list_test4","list_test7",(void *)"linsert test");
        
        redisclient.lpop("list_test",(void *)"lpop test");
        redisclient.lrem("list_test",2,"list_test7",(void *)"lrem test");
        redisclient.lrem("list_test",-1,"list_test4",(void *)"lrem test");
        redisclient.lrem("list_test",0,"list_test5",(void *)"lrem test");
        redisclient.lrem("list_test1",0,"list_test5",(void *)"lrem test");
        redisclient.lset("list_test",2,"list_test99",(void *)"lset test");
        redisclient.lset("list_test",20,"list_test99",(void *)"lset test");
        redisclient.ltrim("list_test",0,3,(void *)"ltrim test");
        redisclient.rpop("list_test",(void *)"rpop test");
        vector<string> k5;
        k5.push_back("list_test1");
        k5.push_back("list_test2");
        k5.push_back("list_test3");
        k5.push_back("list_test4");
        redisclient.rpush("list_test2",k5,(void *)"rpush test");
        redisclient.rpushx("list_test2","list_test5",(void *)"rpushx test");
        redisclient.rpoplpush("list_test2","list_test3",(void *)"rpoplpush test");

        vector<string> k6;
        k6.push_back("list_test1");
        k6.push_back("list_test2");
        k6.push_back("list_test3");
        redisclient.blpop(k6,3,(void *)"blpop test");
        redisclient.get("get_test",(void *)"get  test");
        redisclient.brpop(k6,3,(void *)"blpop test");
        redisclient.brpoplpush("list_test2","list_test3",2,(void *)"rpoplpush test");
        
        /****************************set cmd test **********************/
        vector<string> k7;
        k7.push_back("set_test1_value");
        k7.push_back("set_test2_value");
        k7.push_back("set_test3_value");
        redisclient.sadd("set_test",k7,(void *)"sadd test");
        redisclient.scard("set_test",(void *)"scard test");
        redisclient.sismember("set_test","set_test3",(void *)"sismember test");
        redisclient.smembers("set_test",(void *)"smembers test");
        redisclient.spop("set_test",(void *)"spop test");
        redisclient.srandmember("set_test",(void *)"srandmember test");
        redisclient.srandmember("set_test",5,(void *)"srandmember count test");
        vector<string> k8;
        k8.push_back("set_test1_value");
        k8.push_back("set_test2_value");
        k8.push_back("set_test3_value");
        k8.push_back("set_test4_value");
        redisclient.srem("set_test",k8,(void *)"srem test");

        vector<string> k9;
        k9.push_back("set_test1");
        k9.push_back("set_test2");
        k9.push_back("set_test3");
        redisclient.sdiff(k9,(void *)"sdiff test");
        redisclient.sdiffstore("sdiff_test",k9,(void *)"sdiff test");
        redisclient.sinter(k9,(void *)"sinter test");
        redisclient.sinterstore("sinter_test",k9,(void *)"sinterstore test");
        redisclient.smove("set_test1","set_test4","set_test1_value",(void *)"smove test");
        redisclient.sunion(k9,(void *)"sunion test");
        redisclient.sunionstore("sunion_test",k9,(void *)"sunionstore test");
      

        /****************************sortset cmd test **********************/

        vector<pair<float, string> >kv2;
        pair<float, string> pair44;
        pair<float, string> pair55;
        pair<float, string> pair66;
        pair44 = make_pair(1.1, "zset_test1 value");
        pair55 = make_pair(4.8, "zset_test2 value");
        pair66 = make_pair(3.9, "zset_test3 value");
        kv2.push_back(pair44);
        kv2.push_back(pair55);
        kv2.push_back(pair66);
        redisclient.zadd("zset_test",kv2,(void *)"zadd test");
        redisclient.zcard("zset_test",(void *)"zcard test");
        redisclient.zincrby("zset_test",2.3,"zset_test1 value",(void *)"zincrby test");
        redisclient.zrange("zset_test",0,-1,(void *)"zrange test");
        redisclient.zrange("zset_test",0,-1,(void *)"zrange witch scores test",true);
        redisclient.zrangebyscore("zset_test","2","+inf",(void *)"zrangebyscore test");
        redisclient.zrangebyscore("zset_test","-inf","+inf",(void *)"zrangebyscore with scores test",true);
        redisclient.zrangebyscore("zset_test","-inf","+inf",1,3,(void *)"zrangebyscore limit test");
        redisclient.zrangebyscore("zset_test","-inf","+inf",3,3,(void *)"zrangebyscore limit with scores test",true);
        redisclient.zrank("zset_test","zset_test3 value",(void *)"zrank test");
        redisclient.zrank("zset_test","zset_test5 value",(void *)"zrank not exists test");
        
        redisclient.zrevrange("zset_test",0,-1,(void *)"zrevrange test");
        redisclient.zrevrange("zset_test",0,-1,(void *)"zrevrange witch scores test",true);
        redisclient.zrevrangebyscore("zset_test","2","+inf",(void *)"zrevrangebyscore test");
        redisclient.zrevrangebyscore("zset_test","-inf","+inf",(void *)"zrevrangebyscore with scores test",true);
        redisclient.zrevrangebyscore("zset_test","-inf","+inf",1,3,(void *)"zrevrangebyscore limit test");
        redisclient.zrevrangebyscore("zset_test","-inf","+inf",3,3,(void *)"zrevrangebyscore limit with scores test",true);
        redisclient.zrevrank("zset_test","zset_test3 value",(void *)"zrevrank test");
        redisclient.zrevrank("zset_test","zset_test5 value",(void *)"zrevrank not exists test");
        redisclient.zscore("zset_test","zset_test2 value",(void *)"zscore test");
        redisclient.zremrangebyrank("zset_test",0,1,(void *)"zremrangebyrank test");
        redisclient.zremrangebyscore("zset_test","3.6","+inf",(void *)"zremrangebyscore test");
        vector<string> k10;
        k10.push_back("zset_test1 value");
        k10.push_back("zset_test2 value");
        k10.push_back("zset_test3 value");
        k10.push_back("zset_test4 value");
        redisclient.zrem("zset_test",k10,(void *)"zrem test");
        redisclient.zincrby("zset_test",2.3,"zset_test1 value",(void *)"zincrby test");
        redisclient.zscore("zset_test","zset_test2 value",(void *)"zscore test");

        redisclient.raw_redis_cmd(em_string_relpy,(void*)"raw redis cmd test","get %s","zhanyitest");
        vector<string> k11;
        k11.push_back("mget");
        k11.push_back("zhanyi");
        k11.push_back("zhanyi test");
        redisclient.raw_redis_cmdargv(em_slist_relpy,k11,(void*)"raw redis argvcmd test");

        vector<string> k12;
        k12.push_back("zhanyitest1");
        k12.push_back("zhanyitest2");
        k12.push_back("zhanyitest3");
        redisclient.subscribe(k12,(void*)"subscribe test");

        vector<string> k13;
        k13.push_back("wx*");
        k13.push_back("nihao*");
        k13.push_back("women*");
        redisclient.psubscribe(k13,(void*)"psubscribe test");
        vector<string> k14;
        k14.push_back("zhanyitest2");
        vector<string> k15;
        k15.push_back("wx*");
        redisclient.punsubscribe(k15,(void*)"punsubscribe test");
        redisclient.unsubscribe(k14,(void*)"unsubscribe test");

        redisclient.pubsub_channels("",(void*)"pubsub_channels test");
        redisclient.pubsub_channels("zhanyitest*",(void*)"pubsub_channels test");
        vector<string> k16;
        k16.push_back("zhanyitest1");
        k16.push_back("zhanyitest2");
        k16.push_back("zhanyitest3");
        redisclient.pubsub_numsub(k16,(void*)"pubsub_numsub test");
        redisclient.pubsub_numpat((void*)"pubsub_numpat test");
        
        redisclient.raw_redis_cmd(em_array_reply,(void*)"raw redis argvcmd test","subscribe zhanyitest1 zhanyitest2 zhanyitest3");
        redisclient.raw_redis_cmd(em_array_reply,(void*)"raw redis argvcmd test","psubscribe wx* nihao* women*");
        
        //pubsub channels em_slist_relpy
        redisclient.raw_redis_cmd(em_slist_relpy,(void*)"raw redis argvcmd test","pubsub channels");
        
        //pubsub numsub em_array_reply
       redisclient.raw_redis_cmd(em_array_reply,(void*)"raw redis argvcmd test","pubsub numsub zhanyitest1 zhanyitest2 zhanyitest3");
        
        //pubsub numpat em_integer_relpy
        redisclient.raw_redis_cmd(em_integer_relpy,(void*)"raw redis argvcmd test","pubsub numpat");
        
        // publish em_integer_relpy
        redisclient.raw_redis_cmd(em_integer_relpy,(void*)"raw redis argvcmd test","publish zhanyitest2 fabuxiaoxila....");
        redisclient.raw_redis_cmd(em_integer_relpy,(void*)"raw redis argvcmd test","publish zhanyitest2 fabuxiaoxila222....");
        redisclient.raw_redis_cmd(em_integer_relpy,(void*)"raw redis argvcmd test","publish nihao212 fabuxiaoxila444444....");
        
        // punsubscribe 会在psubscribe中返回 unsubscribe会在 subscribe中返回 
        redisclient.raw_redis_cmd(em_integer_relpy,(void*)"raw redis argvcmd test","punsubscribe nihao*");
        redisclient.raw_redis_cmd(em_integer_relpy,(void*)"raw redis argvcmd test","unsubscribe zhanyitest2");
        
        #endif
        ev_break (EV_A_ EVBREAK_ONE);
}


int main()
{
    string ip = "127.0.0.1";
    int port = 6379;
    string passwd;

    redis_reply_handler* r = new redis_reply_handler();
    struct ev_loop *loop = EV_DEFAULT;
    ev_timer timeout_watcher;
    redisclient.init(ip, port, passwd, r, loop);
    // 等待连接成功
    ev_timer_init (&timeout_watcher, timeout_cb, 0.1, 0.);
    ev_timer_start (loop, &timeout_watcher);

    while(1)
    {
        ev_loop(loop, 0);
    }

    return 0;
}
