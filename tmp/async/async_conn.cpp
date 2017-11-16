#include "async_conn.h"
#include <strings.h>
#include <string.h>


using namespace asyncredis;

void auth_callback(redisAsyncContext *c, void *r, void *privdata) 
{
    connection *pconn = (connection *)c->data;
    pconn->on_auth(c, r, privdata);
}

void connect_callback(const redisAsyncContext *c, int status) 
{
    connection *pconn = (connection *)c->data;
    pconn->on_connect((redisAsyncContext *)c, status);
}

void disconnect_callback(const redisAsyncContext *c, int status) 
{
    connection *pconn = (connection *)c->data;
    pconn->on_disconnect((redisAsyncContext *)c, status);
}


connection::connection()
:_ip("")
,_port(0)
,_password("")
,ploop(NULL)
,prc(NULL)
,_conn_state(em_UNCONNECTED)
,_auth(false)
{
}

connection::~connection()
{
    disconnect();
}


int connection::init(string &ip, int port, string &passwd, struct ev_loop *loop)
{
    _ip = ip;
    _port = port;
    _password= passwd;
    ploop = loop;
    if(!_password.empty())
    {
        _auth = true;
    }
    return connect();
}

int connection::connect()
{
    prc = redisAsyncConnect(_ip.c_str(), _port);
    _conn_state = em_CONNECTING;
    if (prc->err)
    {
	    _conn_state = em_UNCONNECTED;
        printf("%s init failed %s \n", __func__,prc->err);
        return -1;
    }

    prc->data = this;

    redisLibevAttach(ploop, prc); 
    redisAsyncSetConnectCallback(prc, connect_callback);
    redisAsyncSetDisconnectCallback(prc, disconnect_callback);
    return 0;
}

int connection::try_connect()
{
    return (em_UNCONNECTED == _conn_state) ? connect():0;
}

int connection::disconnect()
{
    _conn_state = em_UNCONNECTED;
    redisAsyncDisconnect(prc);
    return 0;
}

int connection::auth()
{
    string auth_cmd = string("auth ") + _password;
    return redisAsyncCommand(prc, auth_callback, NULL, auth_cmd.c_str());
}


int connection::on_auth(redisAsyncContext *c, void *r, void *privdata)
{
        redisReply *rp = (redisReply *)r;
        if(rp && rp->type == REDIS_REPLY_STATUS && strcasecmp(rp->str,"OK") == 0)
        {
            _conn_state = em_AUTHENTICATION;
            printf("auth success!!\n");
        }
        else if(rp && rp->type == REDIS_REPLY_ERROR && strstr(rp->str, "ERR Client sent AUTH, but no password is set"))
        {
            _conn_state = em_AUTHENTICATION;
            printf("pass password but redis not need passwrd .auth success !!\n");
        }
        else
        {
            printf("error auth failed!!!!!!!!\n");
        }
        return 0;
}


int connection::on_connect(redisAsyncContext *c, int status)
{
	if (status != REDIS_OK)
	{
		printf("on connect redis , exists error: %s\n", c->errstr);
		return -1;
	}
	printf("connect redis success auth %d !!!\n",_auth);
	_conn_state = em_CONNECTED;
    if(_auth)
    {
        if(auth() != REDIS_OK)
        {
            disconnect();
            return -1;
        }
    }
	return 0;
}

int connection::on_disconnect(redisAsyncContext *c, int status)
{
    if (status != REDIS_OK)
	{
		printf("disconnect redis error: %s\n", c->errstr);
	}
	printf("disconnect redis success\n");
    // to do 如果一直连不上
    connect();
	return 0;
}
