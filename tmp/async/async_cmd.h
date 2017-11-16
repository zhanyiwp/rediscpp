//#include "base_type.h"
#include "async_conn.h"
#include "async_reply.h"

#pragma once

#define member_offsetof(Type, Member) ( (size_t)( &(((Type*)8)->Member) ) - 8 )

void status_callback(redisAsyncContext *c, void *r, void *privdata);
void type_callback(redisAsyncContext *c, void *r, void *privdata);
void integer_callback(redisAsyncContext *c, void *r, void *privdata);
void double_callback(redisAsyncContext *c, void *r, void *privdata);
void string_callback(redisAsyncContext *c, void *r, void *privdata);
void string_list_callback(redisAsyncContext *c, void *r, void *privdata);
void ss_map_callback(redisAsyncContext *c, void *r, void *privdata);
void sd_map_callbak(redisAsyncContext *c, void *r, void *privdata);
void array_callback(redisAsyncContext *c, void *r, void *privdata);
void redis_reply_callback(redisAsyncContext *c, void *r, void *privdata);

namespace asyncredis
{
	enum reply_type
	{
		em_status_reply =0,	//status_reply
		em_type_relpy =1,	//status_reply for type cmd
		em_integer_relpy=2,	//integer_reply
		em_double_relpy=3,	//double_reply
		em_string_relpy=4,	// string_reply
		em_slist_relpy=5,	// string_list_reply
		em_ss_map_reply=6,	// ss_map_reply
		em_sd_map_reply=7,	// sd_map_reply
		em_array_reply=8,	// array_reply  
		em_raw_reply=9		// raw_reply 
	};

	class cmd
	{
		public:
			static cmd* get_instance_via_cmd(connection* conn) 
			{ 
				return reinterpret_cast<cmd*>(reinterpret_cast<uint8_t*>(conn)-member_offsetof(cmd, m_conn));
			}

			int init(string &ip, int port, string &passwd, reply* r, struct ev_loop *loop);
			int exec_command(reply_type type,void *data, const char *cmd, ...);
			int exec_commandargv(reply_type type,void *data, const vector<string> &v);
			redisCallbackFn *get_callback(reply_type type);

			inline reply *get_reply() const{return m_reply;}

			inline connection *get_conn(){return &m_conn;}

			reply_status check_reply_type(redisReply *r,int type,bool must_ok = true);
			inline const array_data& get_array_data() const{return m_ar;}
			inline const string& get_string_data() const{return m_sr;}
			inline const vector<string>& get_list_data() const{return m_vr;}
			inline const map<string,string>& get_ssmap_data() const{return m_msr;}
			inline const map<string,double>& get_sdmap_data() const{return m_mdr;}
		private:
			connection m_conn;
			reply *m_reply;
			array_data m_ar;
			string m_sr;
			vector<string> m_vr;
			map<string,string> m_msr;
			map<string,double> m_mdr;

	};
}
