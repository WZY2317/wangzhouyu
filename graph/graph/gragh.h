#pragma once
#include<vector>
#include<map>
#include<iostream>
using namespace std;
namespace matrix
{
	template<class V, class W, W MAX_W = _MAX_INT_DIG, bool Direction = false>
	class Graph
	{
	public:
		Graph(const V* a, size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				_vertexs.push_back(a[i]);
				_indexMap[a[i]] = i;
			}
			_matrix.resize(n);
			for (size_t i = 0; i < _matrix.size(); i++)
			{
				_matrix[i].resize(n, MAX_W);
			}
		}
		size_t GetVertexIndex(const V& v)
		{
			//获取顶点的下标
			auto it = _indexMap.find(v);
			if (it != _indexMap.end())
				return it->second;
			else
			{
				//assert(false);
				//throw invalid
				return -1;
			}
		}
		void AddEdge(const V& src,const V& dst,const W& w)
		{
			size_t srci = GetVertexIndex(src);
			size_t dsti = GetVertexIndex(dst);
			_matrix[srci][dsti] = w;
			if (Direction == false)
			{
				_matrix[srci][dsti] = w;
				_matrix[dsti][srci] = w;
			}
		}
		void Print()
		{
			// 打印顶点和下标映射关系
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				cout << _vertexs[i] << "-" << i << " ";
				
			}
			cout << endl << endl;
			cout << " ";
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				cout << i << " ";
			}
			cout << endl;
			// 打印矩阵
			for (size_t i = 0; i < _matrix.size(); ++i)
			{
				cout << i << " ";
				for (size_t j = 0; j < _matrix[i].size(); ++j)
				{
					if (_matrix[i][j] != MAX_W)
						cout << _matrix[i][j] << " ";
					else
						cout << "#" << " ";
				}
				cout << endl;
			}
			cout << endl << endl;
			// 打印所有的边
			for (size_t i = 0; i < _matrix.size(); ++i)
			{
				for (size_t j = 0; j < _matrix[i].size(); ++j)
				{
					if (i < j && _matrix[i][j] != MAX_W)
					{
						cout << _vertexs[i] << "-" << _vertexs[j] << ":" <<
							_matrix[i][j] << endl;
					}
				}
			}
		}
	
	private:
		vector<V> _vertexs;
		map<V, int> _indexMap;
		vector<vector<W>> _matrix;
	};

	
}
void TestGraph()
{
	matrix::Graph<char, int, INT_MAX, true> g("0123", 4);
	g.AddEdge('0', '1', 1);
	g.AddEdge('0', '3', 4);
	g.AddEdge('1', '3', 2);
	g.AddEdge('1', '2', 9);
	g.AddEdge('2', '3', 8);
	g.AddEdge('2', '1', 5);
	g.AddEdge('2', '0', 3);
	g.AddEdge('3', '2', 6);
	g.Print();
	
}