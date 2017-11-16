#include "RedisClient.h"
#include <iostream>
#include <unistd.h>
#include <chrono>
#include<thread>

void test(RedisClient *Client)
{
	//BoolResult Test
	RedisPipeClient Pipe(Client);
	while(1)
	{
		shared_ptr<BoolResult> BResutl = Client->Exists("booltestkey");
		if (BResutl->Success())
		{
			if (BResutl->TRUE())
			{
				cout << "booltestkey is exists"<< endl;
			}
			else
			{
				cout << "booltestkey is not exists" << endl;
			}
		}	
		else
		{
			cout << "exec cmd failed becase: " << BResutl->GetVal() << endl;
		}
		
		//StatusResult Test
		shared_ptr<StatusResult> SResutl = Client->Set("settest", "set test value");
		if (SResutl->OK())
		{

			cout << "settest success" << endl;
		}
		else
		{
			cout << "settest failed : " << SResutl->GetErr() << endl;
		}

		//StringResult Test
		shared_ptr<StringResult> StrResutl = Client->Get("settest");
		if (StrResutl->Success())
		{

			cout << "get success " << StrResutl->GetVal()<< endl;
		}
		else
		{
			cout << "get failed : " << StrResutl->GetErr() << endl;
		}
		// pipeline test
		//RedisPipeClient Pipe(Client);
		vector<string>Keys;
		Keys.push_back("zhanyitest");
		Keys.push_back("zhanyitest11");
		Keys.push_back("zhanyitest22");
		Keys.push_back("zhanyitest33");
		vector<shared_ptr<StringResult> > Results(Keys.size());
		//Pipe.Begin();
		for (size_t i = 0; i != Keys.size(); i++)
		{
			Results[i] = Pipe.Get(Keys[i]);
		}
		int ret = Pipe.Exec();
		if (ret == 0)
		{
			cout << "pipe success " << endl;
			//for (auto i : Results)
			for (vector<shared_ptr<StringResult> >::iterator it = Results.begin(); it != Results.end(); it++)
			{
				if (it->get()->Success())
				{
					cout << "get success " << it->get()->GetVal() << endl;
				}
				else
				{
					cout << "get failed ret " << it->get()->GetErr() << endl;
				}
			}
			cout << endl;
		}
		else
		{
			cout << "pipe failed ret " << ret << endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	cout << "end-------------: " << endl;
}

int main()
{
	RedisOpt Opt("192.168.1.222", 20000);
	RedisClient Client(Opt);
	std::thread t1(&test,&Client);
	std::thread t2(&test,&Client);
	std::thread t3(&test,&Client);
	std::thread t4(&test,&Client);
	std::thread t5(&test,&Client);
	std::thread t6(&test,&Client);
	std::thread t7(&test,&Client);
	std::thread t8(&test,&Client);
	std::thread t9(&test,&Client);
	std::thread t10(&test,&Client);
	std::thread t11(&test,&Client);
	std::thread t12(&test,&Client);
	
	while(1)
	{
		std::this_thread::sleep_for(std::chrono::seconds(100));
	}
	return 0;
}
