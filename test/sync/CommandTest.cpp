#include "RedisClient.h"
#include <iostream>
#include <unistd.h>

int main()
{
	RedisOpt Opt("192.168.1.222",20000);
	RedisClient Client(Opt);
	vector<string>Keys;
	Keys.push_back("zhanyitest");
	Keys.push_back("zhanyitest11");
	Keys.push_back("zhanyitest22");
	Keys.push_back("zhanyitest33");
	shared_ptr<IntResult> Result = Client.Del(Keys);
	if (Result->Success())
	{
		cout << "get result " << Result->GetVal() << endl;
	}
	else
	{
		cout << "get failed : " << Result->GetErr() << endl;
	}

	Client.Dump("zhanyitest");
	return 0;
}
