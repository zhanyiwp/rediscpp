#include "RedisClient.h"
#include <iostream>
#include <unistd.h>

int main()
{
	RedisOpt Opt("127.0.0.1",6379);
	RedisClient Client(Opt);
	string value;
	for (;;)
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
		sleep(3);
	}
	return 0;
}
