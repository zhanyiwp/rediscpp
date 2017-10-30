#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "hiredis/hiredis.h"
#include "hiredis/async.h"

#pragma once
using namespace std;

namespace asyncredis
{
	enum reply_status
	{
		REPLY_NIL=0,
		REPLY_TYPE_OK=1,
		REPLY_TYPE_NIL=2,
		REPLY_TYPE_ERR=3,
		REPLY_TYPE_FAIL=4,	// 返回结果为status类型的命令 执行结果不为OK时 返回这种错误
		REPLY_TYPE_INVALID=5
	};

	typedef struct _data_item_{
	int    type;
	int64_t integer;
	std::string str;
	
	_data_item_ & operator=(const _data_item_ &data) {
		type = data.type;
		integer = data.integer;
		str  = data.str;
		return *this;
	}
	}data_item;
	typedef std::vector<data_item>       array_data;

	class reply //结果处理类 使用者继承这个类来处理结果 
	{
		public:
			/***************************返回结果操作接口***************************************/
			virtual void status_reply(reply_status result, const bool r, void *privdata);
			virtual void integer_reply(reply_status result, const int64_t r, void *privdata);
			virtual void double_reply(reply_status result, const double r, void *privdata);
			virtual void string_reply(reply_status result, const string &r, void *privdata);
			virtual void string_list_reply(reply_status result, const vector<string> &r, void *privdata);
			virtual void ss_map_reply(reply_status result, const map<string,string> &r, void *privdata);
			virtual void sd_map_reply(reply_status result, const map<string,double> &r, void *privdata);
			virtual void array_reply(reply_status result, const array_data &r, void *privdata);	
			virtual void raw_reply(reply_status result,const redisReply *r, void *privdata);
		
			/***************************辅助函数 ***************************************/
			int get_error_info(string &errinfo);
			void set_error_info(int err,const string &errinfo);
		private:
			int _err;
			string _errinfo;
			
	};
}
