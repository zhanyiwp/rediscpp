#include "RedisCmd.h"

#pragma once

using namespace std;

class RedisClient
{
public:
	RedisClient(RedisOpt &Opt);
	~RedisClient();

	 /* GET*/  
	int Get(const std::string& key, std::string& value);
	
private:
	RedisCmd _cmd;
};