#pragma once
namespace ss 
{

	template<class T>
	class share_ptr
	{
	private:
		T* _ptr;
		int* pcount;
	public:
		share_ptr() :_ptr(nullptr)
			, pcount(new int(1))
		{

		}
		share_ptr(const share_ptr& sp)
			:_ptr(sp._ptr)
			,pcount(sp.pcount)
		{			
		}
		share_ptr<T>& operator=(const share_ptr<T>& sp)
		{
			if (sp._ptr != this->_ptr)
			{
				this->_ptr = sp._ptr;
				this->pcount = sp.pcount;
				*pcount++;
			}
			return *this;
		}
		void Release()
		{
			if (--(*pcount) == 0 && _ptr)
			{
				delete(_ptr);
				_ptr = nullptr;
				delete(_pcount);
				pcount = nullptr;
			}
		}
		~share_ptr()
		{
			Release();
		}
	};
}


