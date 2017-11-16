#include "RedisClient.h"
#include <iostream>
#include <unistd.h>

int main()
{
	RedisOpt Opt("192.168.1.222", 20000);
	RedisClient Client(Opt);
	
	//BoolResult Test
	shared_ptr<BoolResult> BResutl = Client.Exists("booltestkey");
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
	shared_ptr<StatusResult> SResutl = Client.Set("settest", "set test value");
	if (SResutl->OK())
	{

		cout << "settest success" << endl;
	}
	else
	{
		cout << "booltestkey is not exists" << endl;
	}

	//StringResult Test
	shared_ptr<StringResult> StrResutl = Client.Get("settest");
	if (StrResutl->Success())
	{

		cout << "get success " << StrResutl->GetVal()<< endl;
	}
	else
	{
		cout << "get failed : " << StrResutl->GetErr() << endl;
	}
	
	//IntResult Test
	shared_ptr<IntResult> IResult = Client.TTL("ttltest");
	if (IResult->Success())
	{
		cout << "get ttl " << static_cast<int>(IResult->GetVal()) << endl;
	}
	else
	{
		cout << "get ttl failed : " << IResult->GetErr() << endl;
	}
	
	//StringArrayResult Test
	shared_ptr<StringArrayResult> SAResult = Client.HKeys("stringarraytest_hash");
	if (SAResult->Success())
	{
		
		//for (auto i : SAResult->GetVal())
		vector<string> res = SAResult->GetVal();
		for (vector<string>::iterator it = res.begin(); it != res.end();it++)
		{
			cout << "get stringarraytest_hash success " << *it << endl;
		}
	}
	else
	{
		cout << "get stringarraytest_hash failed : " << SAResult->GetErr() << endl;
	}
	
	//FloatResult Test
	shared_ptr<FloatResult> FResutl = Client.IncrByFloat("incrfloattest",1.1);
	if (FResutl->Success())
	{

		cout << "incrfloattest success " << FResutl->GetVal() << endl;
	}
	else
	{
		cout << "incrfloattest failed : " << FResutl->GetErr() << endl;
	}

	//StringStringMapResult Test
	shared_ptr<StringStringMapResult> SSMResult = Client.HGetAll("stringarraytest_hash");
	if (SSMResult->Success())
	{
		map<string, string> val = SSMResult->GetVal();
		for (map<string, string>::iterator it = val.begin(); it != val.end(); it++)
		//for (auto i : SSMResult->GetVal())
		{
			cout << "get stringarraytest_hash success key: " << it->first << "valuse: " << it->second << endl;
		}
	}
	else
	{
		cout << "get stringarraytest_hash failed : " << SSMResult->GetErr() << endl;
	}
	
	//StringFloatMapResult Test
	shared_ptr<StringFloatMapResult> SFMResult = Client.ZRangeWithScores("sfmtest_zset", 0, -1);
	if (SFMResult->Success())
	{
		map<string, float> val = SFMResult->GetVal();
		//for (auto i : SFMResult->GetVal())
		for (map<string, float>::iterator it = val.begin(); it != val.end(); it++)
		{
			cout << "get sfmtest_zset success key: " << it->first << "valuse: " << it->second << endl;
		}
	}
	else
	{
		cout << "get sfmtest_zset failed : " << SFMResult->GetErr() << endl;
	}

	//RawResult Test
	{
		shared_ptr<RawResult> RawResutl = Client.RawCommand("get %s", "zhanyitest");
		if (RawResutl->Success())
		{
			redisReply *Reply = RawResutl->GetVal()->GetReply();
			cout << "RawResutl test success " << string(Reply->str) << endl;
		}
		else
		{
			cout << "RawResutl failed : " << RawResutl->GetErr() << endl;
		}
	}

	{
		vector<string>Keys;
		Keys.push_back("mget");
		Keys.push_back("zhanyitest");
		Keys.push_back("zhanyitest11");
		Keys.push_back("zhanyitest22");
		Keys.push_back("zhanyitest33");
		shared_ptr<RawResult> RawResutl = Client.RawCommandv(Keys);
		if (RawResutl->Success())
		{
			redisReply *Reply = RawResutl->GetVal()->GetReply();
			for (size_t i = 0; i < Reply->elements; i++)
			{
				string s(Reply->element[i]->str, Reply->element[i]->len);
				cout << "RawResutl test success " << s << endl;
			}
		}
		else
		{
			cout << "RawResutl failed : " << RawResutl->GetErr() << endl;
		}
	}

	// pipeline test
	RedisPipeClient Pipe(&Client);
	vector<string>Keys;
	Keys.push_back("mget");
	Keys.push_back("zhanyitest");
	Keys.push_back("zhanyitest11");
	Keys.push_back("zhanyitest22");
	Keys.push_back("zhanyitest33");
	vector<shared_ptr<StringResult> > Results(Keys.size());
	Pipe.Begin();
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
	cout << "end-------------: " << endl;
	return 0;
}
