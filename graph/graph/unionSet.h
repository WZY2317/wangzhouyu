#pragma once
#include<vector>
using namespace std;

class UnionFindSet
{
public:
	UnionFindSet(size_t n) :_ufs(n, -1)
	{

	}
	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if (root1 == root2)
		{
			return;
		}
		if (root1 > root2)
			swap(root1, root2);
		_ufs[root1] += _ufs[root2];
		_ufs[root2] = root1;
	}
	int FindRoot(int x)
	{
		int parent = x;
		while (_ufs[parent] >= 0)
		{
			parent = _ufs[parent];
		}
		//½øÐÐÑ¹Ëõ
		while (_ufs[x] >= 0)
		{
			int parents = _ufs[x];
			_ufs[x] = parent;
			x = parents;
		}
		return parent;
	}
	bool InSet(int x1, int x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	};
	size_t SetSize()
	{
		size_t size = 0;
		for (size_t i = 0; i < _ufs.size(); ++i)
		{
			if (_ufs[i] < 0)
				size++;
		}
		return size;
	}
private:
	vector<int> _ufs;

};
