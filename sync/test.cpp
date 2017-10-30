#include "RedisClient.h"
#include <iostream>

int main()
{
	RedisOpt Opt("192.168.1.222",20000);
	RedisClient Client(Opt);
	string value;
	for (int i = 0; i < 2; i++)
	{

		int ret = Client.Get("zhanyitet", value);
		if (0 == ret)
		{
			cout << "get result " << value << endl;
		}
		else
		{
			cout << "get failed ret " << ret << endl;
		}
	}
	return 0;
}