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
		
		for (auto i : SAResult->GetVal())
		{
			cout << "get stringarraytest_hash success " << i << endl;
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

		for (auto i : SSMResult->GetVal())
		{
			cout << "get stringarraytest_hash success key: " << i.first << "valuse: " << i.second << endl;
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

		for (auto i : SFMResult->GetVal())
		{
			cout << "get sfmtest_zset success key: " << i.first << "valuse: " << i.second << endl;
		}
	}
	else
	{
		cout << "get sfmtest_zset failed : " << SFMResult->GetErr() << endl;
	}

	//RawResult Test
	return 0;
}
