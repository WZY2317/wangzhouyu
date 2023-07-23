#pragma once
#include<mutex>
using namespace std;
class singleInstance
{
public:
	singleInstance* getinstance()
	{
		return &instance;
	}
private:
	singleInstance(){};
	singleInstance(singleInstance const&)=delete;
	singleInstance& operator=(singleInstance const&) = delete;
	//防止拷贝构造和赋值
	

	static singleInstance instance;
};
class Singleton
{
public:
	Singleton* getInstance()
	{
		if (instance == nullptr)
		{
			mtx->lock();
			if (instance == nullptr)
			{
				
			}
		}
	}
private:
	static Singleton* instance;
	mutex* mtx;
};
