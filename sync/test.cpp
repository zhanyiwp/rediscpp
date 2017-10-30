#include "RedisClient.h"
#include <iostream>

int main()
{
	RedisOpt Opt;
	Opt._host = "192.168.1.222";
	Opt._port = 20000;
	RedisClient Client(Opt);
	string value;
	int ret = Client.Get("zhanyitet", value);
	if (0 == ret)
	{
		cout << "get result " << value << endl;
	}
	else
	{
		cout << "get failed ret " << ret << endl;
	}
	return 0;
}