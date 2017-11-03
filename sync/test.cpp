#include "RedisClient.h"
#include <iostream>
#include <unistd.h>

int main()
{
	RedisOpt Opt("192.168.1.222",20000);
	RedisClient Client(Opt);
	for (;;)
	{
		shared_ptr<StringResult> Result1 = Client.Get("zhanyitet");
		if (Result1->Success())
		{
			cout << "get result " << Result1->GetVal() << endl;
		}
		else
		{
			cout << "get failed : " << Result1->GetErr() << endl;
		}
#if 1
		vector<string>Keys;
		Keys.push_back("zhanyitest");
		Keys.push_back("zhanyitest11");
		Keys.push_back("zhanyitest22");
		Keys.push_back("zhanyitest33");
		RedisPipeClient Pipe(&Client);
		vector<shared_ptr<StringResult>> Results(Keys.size());
		Pipe.Begin();
		for (size_t i = 0; i != Keys.size();i++)
		{
			Results[i] = Pipe.Get(Keys[i]);
		}
		int ret = Pipe.Exec();
		if (ret == 0)
		{
			cout << "pipe success " <<endl;
			for (auto i : Results)
			{
				if (i->Success())
				{
					cout << "get success " << i->GetVal() << endl;
				}
				else
				{
					cout << "get failed ret " << i->GetErr() << endl;
				}
			}
			cout << endl;
		}
		else
		{
			cout << "pipe failed ret " << ret << endl;
		}

		Pipe.Begin();
		for (size_t i = 0; i != Keys.size(); i++)
		{
			Results[i] = Pipe.Get(Keys[i]);
		}
		ret = Pipe.Exec();
		if (ret == 0)
		{
			cout << "another pipe success " << endl;
			for (auto i : Results)
			{
				if (i->Success())
				{
					cout << " another get success " << i->GetVal() << endl;
				}
				else
				{
					cout << "another get failed ret " << i->GetErr() << endl;
				}
			}
			cout << endl;
		}
		else
		{
			cout << "another pipe failed ret " << ret << endl;
		}
#endif
		sleep(3);
	}
	return 0;
}
