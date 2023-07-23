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
	//��ֹ��������͸�ֵ
	

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
