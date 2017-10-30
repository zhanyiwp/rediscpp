#include "RedisClient.h"

RedisClient::RedisClient(RedisOpt &Opt)
:_cmd(Opt)
{

}

RedisClient::~RedisClient()
{

}

int RedisClient::Get(const std::string& key, std::string& value)
{
	redisReply *reply = _cmd.Command("GET %s", key.c_str());
	if (NULL == reply)
	{
		return -1;
	}
	value.assign(reply->str, reply->len);
	return 0;
}