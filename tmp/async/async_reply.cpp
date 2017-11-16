#include "async_reply.h"
#include <strings.h>

using namespace asyncredis;

void reply::status_reply(reply_status result, const bool r, void *privdata)
{

}

void reply::integer_reply(reply_status result, const int64_t r, void *privdata)
{
	
}

void reply::double_reply(reply_status result, const double r, void *privdata)
{

}

void reply::string_reply(reply_status result, const string &r, void *privdata)
{

}

void reply::string_list_reply(reply_status result, const vector<string> &r, void *privdata)
{

}

void reply::ss_map_reply(reply_status result, const map<string,string> &r, void *privdata)
{

}

void reply::sd_map_reply(reply_status result, const map<string,double> &r, void *privdata)
{

}

void reply::array_reply(reply_status result, const array_data &r, void *privdata)
{

}

void reply::raw_reply(reply_status result,const redisReply *r, void *privdata)
{

}

void reply::set_error_info(int err,const string &errinfo)
{
	_err = err;
	_errinfo = errinfo;
}

int reply::get_error_info(string &errinfo)
{
	errinfo = _errinfo;
	return _err;
}