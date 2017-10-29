基于hiredis封装的异步redis client 接口 
#########################################################################
组织结构:
async_redis.h-------------redis操作接口类 提供对外访问,封装redis所支持的各种命令
async_conn.h--------------连接管理类,负责连接的建立和重连 判断连接状态等
async_cmd.h---------------命令执行类，将命令异步发送到redis执行
async_reply.h-------------结果处理类，redis执行的结果通过该类异步回调，使用者通过继承该类来处理命令结果

#########################################################################
使用方法:
1.继承reply类来处理命令结果,根据redis命令结果支持多种类型结果
2.实例化client类并调用init进行初始化。init原型为
int init(string &ip, int port, string &passwd,reply *reply_handler, struct ev_loop *loop);
参数reply_handler传递实际结果处理类指针
3.调用具体命令函数执行具体命令，每个命令函数都可以传入一个用户数据参数，该数据会在结果回调时携带。用户数据最常见的作用可能就是用于将命令和结果进行对应，以便进行后续逻辑。
#########################################################################
example

//继承reply类以处理结果
class redis_reply_handler:public reply
{
    virtual void string_reply(reply_status result,const string &r, void *privdata)
    {
        if(REPLY_TYPE_OK == result)
        {
            printf("get %s success %s \n",__func__,r.c_str());
        }
        else
        {
            string errinfo;
            int err = get_error_info(errinfo);
            printf("get %s err %d(%s)\n",__func__,err,errinfo.c_str());
        }
    }
};

// 实例化reply类
redis_reply_handler* r = new redis_reply_handler();

//初始化
string ip = "192.168.1.118";
int port = 20000;
string passwd;
struct ev_loop *loop = EV_DEFAULT;
redisclient.init(ip, port, passwd, r, loop);

//执行命令
redisclient.set("my_test","test value",(void *)"set test");
redisclient.get("my_test",(void *)"get test"); 

//事件循环
while(1)
{
    ev_loop(loop, 0);
}

完整例子参考 test/redis_async/

// to do 
// 1.基于C++11封装 简化回调
// 2.连接队列优化
// 3.集成同步封装
