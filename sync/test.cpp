#include "RedisClient.h"
#include <iostream>
#include <unistd.h>

int main()
{
	RedisOpt Opt("192.168.1.222",20000);
	RedisClient Client(Opt);
	for (;;)
	{

		StringResult Result = Client.Get("zhanyitet");
		if (Result.Success())
		{
			cout << "get result " << Result.GetVal() << endl;
		}
		else
		{
			cout << "get failed : " << Result.GetErr() << endl;
		}
		
		IntResult Result1 = Client.TTL("zhanyitet");
		if (Result1.Success())
		{
			cout << "get ttl success " << (int)Result1.GetVal() << endl;
		}
		else
		{
			cout << "get ttl failed ret " << Result.GetErr() << endl;
		}
		vector<string>Keys;
		Keys.push_back("zhanyitest");
		Keys.push_back("zhanyitest11");
		Keys.push_back("zhanyitest22");
		Keys.push_back("zhanyitest33");
		StringArrayResult ResultA = Client.MGet(Keys);
		if (ResultA.Success())
		{
			cout << "Mget  success ";
			for (auto i : ResultA.GetVal())
			{
				cout << i << " " ;
			}
			cout << endl;
		}
		else
		{
			cout << "Mget failed ret " << Result.GetErr() << endl;
		}
		sleep(3);
	}
	return 0;
}
