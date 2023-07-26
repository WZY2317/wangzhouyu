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
				instance = new Singleton();
				return instance;
			}
			mtx->unlock();
		}
		return instance;
	}
	class CGarbo {
	public:
		~CGarbo()
		{
			if (Singleton::instance)
			{
				delete instance;
			}
		}
	};
	static CGarbo garbo;
private:
	Singleton() {};
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static Singleton* instance;
	static mutex* mtx;
};
