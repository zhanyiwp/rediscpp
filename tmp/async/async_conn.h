#include <stdint.h>
#include <stdio.h>
#include <string>
#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libev.h"
#include "ev.h"

#pragma once

using namespace std;
//连接管理类 负责连接的建立和重连 判断连接状态等待
/* to do 
* 优化 维护一个连接队列，原因如下：
*1.虽然hiredis 异步api本身有维护一个连接队列，但是如果连接丢失,重连后队列中的请求就丢了。
*2.如果连接异常断开，已请求的未回答那些命令可能会永远收不到回调,如果自己维护一个队列的话，连接重建后 可以提供重试的机会，也可以提供超时的能力
*/
namespace asyncredis
{
	enum conn_state
	{
		em_UNCONNECTED=0,
		em_CONNECTING=1,
		em_CONNECTED=2,
		em_AUTHENTICATION=3
	};
	class connection 
	{
		public:
			connection();
			~connection();
			int init(string &ip, int port, string &passwd, struct ev_loop *loop);
			int disconnect();
			int on_connect(redisAsyncContext *c, int status);
			int on_auth(redisAsyncContext *c, void *r, void *privdata);
			int on_disconnect(redisAsyncContext *c, int status);
			bool valid_conn()
			{
				if((_auth && _conn_state > em_CONNECTED) || _conn_state > em_CONNECTING)
					return true;
				return false;
			}
			int try_connect();
			redisAsyncContext* get_redis_cx() const{return prc;}
		private:
			int connect();
			int auth();
		private:
			string _ip;
			int _port;
			string _password;
			struct ev_loop* ploop;
			redisAsyncContext* prc;
			conn_state _conn_state;
			bool _auth;
	};
}
