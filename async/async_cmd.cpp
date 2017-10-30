#include "async_cmd.h"
#include <strings.h>


using namespace asyncredis;

void status_callback(redisAsyncContext *c, void *r, void *privdata) 
{
    connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
        redisReply *rp = (redisReply *)r;
        reply_status ret = rcmd->check_reply_type(rp,REDIS_REPLY_STATUS);
		if(REPLY_TYPE_OK == ret)
		{
			p->status_reply(ret,true,privdata);
		}
		else
		{
			p->status_reply(ret,false,privdata);
		}
    }
}

void type_callback(redisAsyncContext *c, void *r, void *privdata)
{
	connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
        redisReply *rp = (redisReply *)r;
        reply_status ret = rcmd->check_reply_type(rp,REDIS_REPLY_STATUS,false);
		if(REPLY_TYPE_OK == ret)
		{
			p->string_reply(ret,rp->str,privdata);
		}
		else
		{
			p->string_reply(ret,"",privdata);
		}
    }
}

void integer_callback(redisAsyncContext *c, void *r, void *privdata) 
{
    connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
        redisReply *rp = (redisReply *)r;
		reply_status ret = rcmd->check_reply_type(rp,REDIS_REPLY_INTEGER);
		if(REPLY_TYPE_OK == ret)
		{
			//printf("privdata[%s]: %lld\n", (char*)privdata, rp->integer);
			p->integer_reply(ret,rp->integer,privdata);
		}
		else
		{
			p->integer_reply(ret,0,privdata);
		}
    }
}

void double_callback(redisAsyncContext *c, void *r, void *privdata)
{
	connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
        redisReply *rp = (redisReply *)r;
		reply_status ret = rcmd->check_reply_type(rp,REDIS_REPLY_STRING);
		if(REPLY_TYPE_OK == ret)
		{
			double r = atof(rp->str);
			p->double_reply(ret,r,privdata);
		}
		else
		{
			p->double_reply(ret,0,privdata);
		}
	}
}

void string_callback(redisAsyncContext *c, void *r, void *privdata) 
{
    connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
		
        redisReply *rp = (redisReply *)r;
		reply_status ret = rcmd->check_reply_type(rp,REDIS_REPLY_STRING);
		string s = rcmd->get_string_data();
		if(REPLY_TYPE_OK == ret)
		{
			s.assign(rp->str,rp->len);
			p->string_reply(ret,s,privdata);
		}
		else
		{
			s.clear();
			p->string_reply(ret,s,privdata);
		}
    }
}

void string_list_callback(redisAsyncContext *c, void *r, void *privdata) 
{
    connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
        redisReply *rp = (redisReply *)r;
		reply_status ret = rcmd->check_reply_type(rp,REDIS_REPLY_ARRAY);
		vector<string> vr = rcmd->get_list_data();
		vr.clear();
		if(REPLY_TYPE_OK == ret)
		{
			for(size_t i=0;i<rp->elements;i++)
			{
				if(rp->element[i]->type == REDIS_REPLY_STRING)
				{
					string res;
					res.assign(rp->element[i]->str,rp->element[i]->len);
					vr.push_back(res);
				}
				else if (rp->element[i]->type == REDIS_REPLY_NIL)
				{
					//空值
					vr.push_back("");
				}
				else
				{
					printf("there is something wrong!!! type %d \n",rp->element[i]->type);
				}
			}
			p->string_list_reply(ret,vr,privdata);
		}
		else
		{
			p->string_list_reply(ret,vr,privdata);
		}
    }
}

void ss_map_callback(redisAsyncContext *c, void *r, void *privdata)
{
	connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
        redisReply *rp = (redisReply *)r;
		reply_status ret = rcmd->check_reply_type(rp,REDIS_REPLY_ARRAY);
		map<string,string> mr = rcmd->get_ssmap_data();
		mr.clear();
		if(REPLY_TYPE_OK == ret)
		{
			string key,value;
			for(size_t i=0;i<rp->elements;i++)
			{
				if(i % 2 == 0) 
				{
					key.clear();
					if(rp->element[i]->type == REDIS_REPLY_STRING)
					{
						key.assign(rp->element[i]->str,rp->element[i]->len);
					}
					else
					{
						printf("there is something wrong %u %d!!!\n",i,rp->element[i]->type);
					}
				}
				else
				{
					value.clear();
					if(rp->element[i]->type == REDIS_REPLY_STRING)
					{
						value.assign(rp->element[i]->str,rp->element[i]->len);
					}
					if(!key.empty())
						mr[key]=value;
				}
			}
			p->ss_map_reply(ret,mr,privdata);
		}
		else
		{
			p->ss_map_reply(ret,mr,privdata);
		}
	}
}

void sd_map_callbak(redisAsyncContext *c, void *r, void *privdata)
{
	connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
        redisReply *rp = (redisReply *)r;
		reply_status ret = rcmd->check_reply_type(rp,REDIS_REPLY_ARRAY);
		map<string,double> mr = rcmd->get_sdmap_data();
		mr.clear();
		if(REPLY_TYPE_OK == ret)
		{
			double score;
			string value;
			for(size_t i=0;i<rp->elements;i++)
			{
				if(i % 2 != 0) 
				{
					if(rp->element[i-1]->type == REDIS_REPLY_STRING && rp->element[i]->type == REDIS_REPLY_STRING)
					{
						score = atof(rp->element[i]->str);
						value.assign(rp->element[i-1]->str,rp->element[i-1]->len);
						mr[value]=score;
					}
					else
					{
						printf("there is something wrong %lu %d %d!!!\n",i,rp->element[i-1]->type,rp->element[i]->type);
					}
				}
			}
			p->sd_map_reply(ret,mr,privdata);
		}
		else
		{
			p->sd_map_reply(ret,mr,privdata);
		}
	}
}

void array_callback(redisAsyncContext *c, void *r, void *privdata) 
{
    connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
        redisReply *rp = (redisReply *)r;
		reply_status ret = rcmd->check_reply_type(rp,REDIS_REPLY_ARRAY);
		array_data ar = rcmd->get_array_data();
		ar.clear();
		if(REPLY_TYPE_OK == ret)
		{
			for(size_t i=0;i<rp->elements;i++)
			{
				 data_item data;
				 data.type = rp->element[i]->type;
				 if(data.type == REDIS_REPLY_INTEGER)
				 	data.integer = rp->element[i]->integer;
				 if(rp->element[i]->len > 0)
				 {
				 	data.str.assign(rp->element[i]->str,rp->element[i]->len);
					data.integer = 0;
				 }
				 ar.push_back(data);
			}
			p->array_reply(ret,ar,privdata);
		}
		else
		{
			p->array_reply(ret,ar,privdata);
		}
    }
}

void redis_reply_callback(redisAsyncContext *c, void *r, void *privdata)
{
	connection *conn = (connection *)c->data;
    cmd* rcmd = cmd::get_instance_via_cmd(conn);
    reply *p =  rcmd->get_reply();
    if(p)
    {
        redisReply *rp = (redisReply *)r;
		p->raw_reply(REPLY_TYPE_OK,rp,privdata);
    }
}

int cmd::init(string &ip, int port, string &passwd, reply* r, struct ev_loop *loop)
{
	m_reply= r; 
	return m_conn.init(ip,port,passwd,loop);
}

int cmd::exec_command(reply_type type,void *data, const char *cmd, ...)
{
	redisCallbackFn *fn = get_callback(type);
	if(!fn)
	{
		printf("unknow reply type %d\n",type);
		return -1;
	}
	if(!m_conn.valid_conn()) //连接无效
	{
		printf("call connection invalid \n");
		m_conn.try_connect();
		return -1;
	}
	redisAsyncContext* ac = m_conn.get_redis_cx();
	va_list ap;
    int status;
    va_start(ap,cmd);
    status = redisvAsyncCommand(ac,fn,data,cmd,ap);
    va_end(ap);
	return status;
}

int cmd::exec_commandargv(reply_type type,void *data, const vector<string> &v)
{
	redisCallbackFn *fn = get_callback(type);
	if(!fn)
	{
		printf("unknow reply type %d\n",type);
		return -1;
	}
	if(!m_conn.valid_conn()) //连接无效
	{
		printf("call connection invalid \n");
		m_conn.try_connect();
		return -1;
	}
	vector<const char *> argv( v.size() );
    vector<size_t> argvlen( v.size() );
    unsigned int j = 0;
    for ( vector<string>::const_iterator it = v.begin(); it != v.end(); ++it, ++j ) 
	{
        argv[j] = it->c_str();
		argvlen[j] = it->size();
    }
	redisAsyncContext* ac = m_conn.get_redis_cx();
    return redisAsyncCommandArgv(ac,fn,data, argv.size(), &(argv[0]), &(argvlen[0]));
}

redisCallbackFn* cmd::get_callback(reply_type type)
{
	redisCallbackFn *fn = NULL;
	switch(type)
	{
		case em_status_reply:fn = status_callback;break;
		case em_type_relpy:fn = type_callback;break;
		case em_integer_relpy:fn = integer_callback;break;
		case em_double_relpy:fn = double_callback;break;
		case em_string_relpy:fn = string_callback;break;
		case em_slist_relpy:fn = string_list_callback;break;
		case em_ss_map_reply:fn = ss_map_callback;break;
		case em_sd_map_reply:fn = sd_map_callbak;break;
		case em_array_reply:fn = array_callback;break;
		case em_raw_reply:fn = redis_reply_callback;break;
		default:break;
	}
	return fn;
}

reply_status cmd::check_reply_type(redisReply *r,int type,bool must_ok /*= true*/)
{
	 // to do err deal
	reply_status ret ;
	if (r == NULL)
	{
		printf("reply is null\n");
		ret = REPLY_NIL;
		m_reply->set_error_info(ret,"reply is null");
	}
	else if(r->type == REDIS_REPLY_NIL)
	{
		ret = REPLY_TYPE_NIL;
		m_reply->set_error_info(ret,"there no reply");
	}
	else if(r->type == REDIS_REPLY_ERROR)
	{
		ret = REPLY_TYPE_ERR;
		m_reply->set_error_info(ret,r->str);
	}
	else if(r->type != type)
	{
		ret = REPLY_TYPE_INVALID;
		char err[256]={0};
		sprintf(err,"reply type is invalid expect type %d but actual type %d",type,r->type);
		m_reply->set_error_info(ret,string(err));
	}
	else if(r->type == REDIS_REPLY_STRING || r->type == REDIS_REPLY_INTEGER || r->type == REDIS_REPLY_ARRAY)
	{
		ret = REPLY_TYPE_OK;
	}
	else if(r->type == REDIS_REPLY_STATUS )
	{
		if(must_ok)
		{
			bool ok = strcasecmp(r->str,"OK") == 0 ? true:false;
			if(ok)
			{
				ret = REPLY_TYPE_OK;
			}
			else
			{
				ret = REPLY_TYPE_FAIL;
				m_reply->set_error_info(ret,r->str);
			}
		}
		else
		{
			ret = REPLY_TYPE_OK;
		}
	}
	else
	{
		ret = REPLY_TYPE_INVALID;
		m_reply->set_error_info(ret,"reply type invalid");
	}

	return ret;
}
