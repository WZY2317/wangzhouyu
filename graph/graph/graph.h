#pragma once
#include <vector>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <functional>
#include<iostream>
#include"unionSet.h"
using namespace std;
// weight
namespace matrix
{
	template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph
	{
		typedef Graph<V, W, MAX_W, Direction> Self;
	public:
		Graph() = default;

		// ͼ�Ĵ���
		// 1��IO����  -- ���������,oj�и��ʺ�
		// 2��ͼ�ṹ��ϵд���ļ�����ȡ�ļ�
		// 3���ֶ����ӱ�
		Graph(const V* a, size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertexs.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			_matrix.resize(n);
			for (size_t i = 0; i < _matrix.size(); ++i)
			{
				_matrix[i].resize(n, MAX_W);
			}
		}

		size_t GetVertexIndex(const V& v)
		{
			auto it = _indexMap.find(v);
			if (it != _indexMap.end())
			{
				return it->second;
			}
			else
			{
				//assert(false);
				cout << "�����ڶ���" << ":" << v << endl;
				throw invalid_argument("���㲻����");

				return -1;
			}
		}


		void _AddEdge(size_t srci, size_t dsti, const W& w)
		{
			_matrix[srci][dsti] = w;
			// ����ͼ
			if (Direction == false)
			{
				_matrix[dsti][srci] = w;
			}
		}

		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexIndex(src);
			size_t dsti = GetVertexIndex(dst);
			_AddEdge(srci, dsti, w);
		}

		void Print()
		{
			// ����
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				cout << "[" << i << "]" << "->" << _vertexs[i] << endl;
			}
			cout << endl;

			// ����
			// ���±�
			cout << "  ";
			for (int i = 0; i < _vertexs.size(); ++i)
			{
				//cout << i << " ";
				printf("%4d", i);
			}
			cout << endl;

			for (size_t i = 0; i < _matrix.size(); ++i)
			{
				cout << i << " "; // ���±�
				for (size_t j = 0; j < _matrix[i].size(); ++j)
				{
					//cout << _matrix[i][j] << " ";
					if (_matrix[i][j] == MAX_W)
					{
						//cout << "* ";
						printf("%4c", '*');
					}
					else
					{
						//cout << _matrix[i][j] << " ";
						printf("%4d", _matrix[i][j]);
					}
				}
				cout << endl;
			}
			cout << endl;

			for (size_t i = 0; i < _matrix.size(); ++i)
			{
				for (size_t j = 0; j < _matrix[i].size(); ++j)
				{
					if (i < j && _matrix[i][j] != MAX_W)
					{
						cout << _vertexs[i] << "->" << _vertexs[j] << ":" << _matrix[i][j] << endl;
					}
				}
			}

		}

		//void BFS(const V& src)
		//{
		//	size_t srci = GetVertexIndex(src);

		//	// ���кͱ������
		//	queue<int> q;
		//	vector<bool> visited(_vertexs.size(), false);

		//	q.push(srci);
		//	visited[srci] = true;

		//	size_t n = _vertexs.size();
		//	while (!q.empty())
		//	{
		//		int front = q.front();
		//		q.pop();
		//		cout << front <<":"<<_vertexs[front] << endl;
		//		// ��front������ڽӶ��������
		//		for (size_t i = 0; i < n; ++i)
		//		{
		//			if (_matrix[front][i] != MAX_W)
		//			{
		//				if (visited[i] == false)
		//				{
		//					q.push(i);
		//					visited[i] = true;
		//				}
		//			}
		//		}
		//	}

		//	cout << endl;
		//}

		void BFS(const V& src)
		{
			size_t srci = GetVertexIndex(src);

			// ���кͱ������
			queue<int> q;
			vector<bool> visited(_vertexs.size(), false);

			q.push(srci);
			visited[srci] = true;
			int levelSize = 1;

			size_t n = _vertexs.size();
			while (!q.empty())
			{
				// һ��һ���
				for (int i = 0; i < levelSize; ++i)
				{
					int front = q.front();
					q.pop();
					cout << front << ":" << _vertexs[front] << " ";
					// ��front������ڽӶ��������
					for (size_t i = 0; i < n; ++i)
					{
						if (_matrix[front][i] != MAX_W)
						{
							if (visited[i] == false)
							{
								q.push(i);
								visited[i] = true;
							}
						}
					}
				}
				cout << endl;

				levelSize = q.size();
			}

			cout << endl;
		}

		void _DFS(size_t srci, vector<bool>& visited)
		{
			cout << srci << ":" << _vertexs[srci] << endl;
			visited[srci] = true;

			// ��һ��srci���ڵ�û�з��ʹ��ĵ㣬ȥ����ȱ���
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				if (_matrix[srci][i] != MAX_W && visited[i] == false)
				{
					_DFS(i, visited);
				}
			}

		}

		void DFS(const V& src)
		{
			size_t srci = GetVertexIndex(src);
			vector<bool> visited(_vertexs.size(), false);

			_DFS(srci, visited);
		}
		struct Edge
		{
		public:
			size_t _srci;
			size_t _dsti;
			W _w;
			Edge( size_t srci,size_t dsti,W w )
				:_srci(_srci)
				,_dsti(_dsti)
				,_w(w)
			{

			}
			bool operator>(const Edge& e1) const
			{
				return _w > e1._w;
			}
		};

		W Kruskal(Self& minTree)
		{
			int n = _matrix.size();

			minTree._indexMap = _indexMap;
			minTree._vertexs = _vertexs;
			minTree._matrix.resize(n);
			//需要进行初始化要不然就会造成越界
			for (size_t i = 0; i < n; ++i)
			{
				minTree._matrix[i].resize(n, MAX_W);
			}
			
			priority_queue<Edge, vector<Edge>, greater<Edge>> minq;
			for (size_t i = 0; i < n; i++)
			{
				for (size_t j = 0; j < n; j++)
				{
					if (_matrix[i][j] != MAX_W)
					{
						minq.push(Edge(i,j, _matrix[i][j]));
					}
				}
			}
			//选出n-1条边;
			UnionFindSet ufs(n);
			int size = 0;
			W totalW = W();
			while (!minq.empty())
			{
				Edge min = minq.top();
				minq.pop();
				if (!ufs.InSet(min._dsti,min._srci))
				{
					minTree._AddEdge(min._dsti, min._srci, min._w);
					ufs.Union(min._srci, min._dsti);
					size++;
					totalW += min._w;
				}
			}
			if (size == n - 1)
			{
				return totalW;
			}
			else
				return W();

		}

		W Prim(Self& minTree, const W& src)
		{
			size_t srci = GetVertexIndex(src);
			size_t n = _vertexs.size();

			minTree._vertexs = _vertexs;
			minTree._indexMap = _indexMap;
			minTree._matrix.resize(n);
			for (size_t i = 0; i < n; ++i)
			{
				minTree._matrix[i].resize(n, MAX_W);
			}

			/*set<int> X;
			set<int> Y;
			X.insert(srci);
			for (size_t i = 0; i < n; ++i)
			{
				if (i != srci)
				{
					Y.insert(i);
				}
			}*/

			vector<bool> X(n, false);
			vector<bool> Y(n, true);
			X[srci] = true;
			Y[srci] = false;

			// ��X->Y���������ӵı�����ѡ����С�ı�
			priority_queue<Edge, vector<Edge>, greater<Edge>> minq;
			// �Ȱ�srci���ӵı����ӵ�������
			for (size_t i = 0; i < n; ++i)
			{
				if (_matrix[srci][i] != MAX_W)
				{
					minq.push(Edge(srci, i, _matrix[srci][i]));
				}
			}

			cout << "Prim��ʼѡ��" << endl;
			size_t size = 0;
			W totalW = W();
			while (!minq.empty())
			{
				Edge min = minq.top();
				minq.pop();

				// ��С�ߵ�Ŀ���Ҳ��X���ϣ��򹹳ɻ�
				if (X[min._dsti])
				{
					//cout << "���ɻ�:";
					//cout << _vertexs[min._srci] << "->" << _vertexs[min._dsti] << ":" << min._w << endl;
				}
				else
				{
					minTree._AddEdge(min._srci, min._dsti, min._w);
					//cout << _vertexs[min._srci] << "->" << _vertexs[min._dsti] << ":" << min._w << endl;
					X[min._dsti] = true;
					Y[min._dsti] = false;
					++size;
					totalW += min._w;
					if (size == n - 1)
						break;

					for (size_t i = 0; i < n; ++i)
					{
						if (_matrix[min._dsti][i] != MAX_W && Y[i])
						{
							minq.push(Edge(min._dsti, i, _matrix[min._dsti][i]));
						}
					}
				}
			}

			if (size == n - 1)
			{
				return totalW;
			}
			else
			{
				return W();
			}
		}

		void PrintShortPath(const V& src, const vector<W>& dist, const vector<int>& pPath)
		{
			size_t srci = GetVertexIndex(src);
			size_t n = _vertexs.size();
			for (size_t i = 0; i < n; ++i)
			{
				if (i != srci)
				{
					// �ҳ�i�����·��
					vector<int> path;
					size_t parenti = i;
					while (parenti != srci)
					{
						path.push_back(parenti);
						parenti = pPath[parenti];
					}
					path.push_back(srci);
					reverse(path.begin(), path.end());

					for (auto index : path)
					{
						cout << _vertexs[index] << "->";
					}
					cout << dist[i] << endl;
				}
			}
		}

		void Dijkstra(const V& src, vector<W>& dist, vector<int>& pPath)
		{
			size_t srci = GetVertexIndex(src);
			size_t n = _vertexs.size();
			dist.resize(n, MAX_W);
			pPath.resize(n, -1);

			dist[srci] = 0;
			pPath[srci] = srci;

			// �Ѿ�ȷ�����·���Ķ��㼯��
			vector<bool> S(n, false);

			for (size_t j = 0; j < n; ++j)
			{
				// ѡ���·�������Ҳ���S��������·��
				int u = 0;
				W min = MAX_W;
				for (size_t i = 0; i < n; ++i)
				{
					if (S[i] == false && dist[i] < min)
					{
						u = i;
						min = dist[i];
					}
				}

				S[u] = true;
				// �ɳڸ���u���Ӷ���v  srci->u + u->v <  srci->v  ����
				for (size_t v = 0; v < n; ++v)
				{
					if (S[v] == false && _matrix[u][v] != MAX_W
						&& dist[u] + _matrix[u][v] < dist[v])
					{
						dist[v] = dist[u] + _matrix[u][v];
						pPath[v] = u;
					}
				}
			}
		}

	private:
		vector<V> _vertexs;			// ���㼯��
		map<V, int> _indexMap;		// ����ӳ���±�
		vector<vector<W>> _matrix;  // �ڽӾ���
	};

	void TestGraph1()
	{
		Graph<char, int, INT_MAX, true> g("0123", 4);
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

	void TestBDFS()
	{
		string a[] = { "����", "����", "����", "����", "����" };
		Graph<string, int> g1(a, sizeof(a) / sizeof(string));
		g1.AddEdge("����", "����", 100);
		g1.AddEdge("����", "����", 200);
		g1.AddEdge("����", "����", 30);
		g1.AddEdge("����", "����", 30);
		g1.Print();

		g1.BFS("����");
		g1.DFS("����");
	}

	void TestGraphMinTree()
	{
		const char str[] = "abcdefghi";
		Graph<char, int> g(str, strlen(str));
		g.AddEdge('a', 'b', 4);
		g.AddEdge('a', 'h', 8);
		//g.AddEdge('a', 'h', 9);
		g.AddEdge('b', 'c', 8);
		g.AddEdge('b', 'h', 11);
		g.AddEdge('c', 'i', 2);
		g.AddEdge('c', 'f', 4);
		g.AddEdge('c', 'd', 7);
		g.AddEdge('d', 'f', 14);
		g.AddEdge('d', 'e', 9);
		g.AddEdge('e', 'f', 10);
		g.AddEdge('f', 'g', 2);
		g.AddEdge('g', 'h', 1);
		g.AddEdge('g', 'i', 6);
		g.AddEdge('h', 'i', 7);

		Graph<char, int> kminTree;
		cout << "Kruskal:" << g.Kruskal(kminTree) << endl;
		kminTree.Print();
		cout << endl << endl;

		Graph<char, int> pminTree;
		cout << "Prim:" << g.Prim(pminTree, 'a') << endl;
		pminTree.Print();
		cout << endl;

		for (size_t i = 0; i < strlen(str); ++i)
		{
			cout << "Prim:" << g.Prim(pminTree, str[i]) << endl;
		}
	}

	void TestGraphDijkstra()
	{
		/*const char* str = "syztx";
		Graph<char, int, INT_MAX, true> g(str, strlen(str));
		g.AddEdge('s', 't', 10);
		g.AddEdge('s', 'y', 5);
		g.AddEdge('y', 't', 3);
		g.AddEdge('y', 'x', 9);
		g.AddEdge('y', 'z', 2);
		g.AddEdge('z', 's', 7);
		g.AddEdge('z', 'x', 6);
		g.AddEdge('t', 'y', 2);
		g.AddEdge('t', 'x', 1);
		g.AddEdge('x', 'z', 4);

		vector<int> dist;
		vector<int> parentPath;
		g.Dijkstra('s', dist, parentPath);
		g.PrintShortPath('s', dist, parentPath);*/

		// ͼ�д��и�Ȩ·��ʱ��̰�Ĳ�����ʧЧ�ˡ�
		// ���Խ�����Կ���s->t->y֮������·��û���³���
		const char* str = "sytx";
		Graph<char, int, INT_MAX, true> g(str, strlen(str));
		g.AddEdge('s', 't', 10);
		g.AddEdge('s', 'y', 5);
		g.AddEdge('t', 'y', -7);
		g.AddEdge('y', 'x', 3);
		vector<int> dist;
		vector<int> parentPath;
		g.Dijkstra('s', dist, parentPath);
		g.PrintShortPath('s', dist, parentPath);
	}
}


namespace link_table
{
	template<class W>
	struct Edge
	{
		//int _srci;
		int _dsti;  // Ŀ�����±�
		W _w;		// Ȩֵ
		Edge<W>* _next;

		Edge(int dsti, const W& w)
			:_dsti(dsti)
			, _w(w)
			, _next(nullptr)
		{}
	};

	template<class V, class W, bool Direction = false>
	class Graph
	{
		typedef Edge<W> Edge;
	public:
		Graph(const V* a, size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertexs.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			_tables.resize(n, nullptr);
		}

		size_t GetVertexIndex(const V& v)
		{
			auto it = _indexMap.find(v);
			if (it != _indexMap.end())
			{
				return it->second;
			}
			else
			{
				//assert(false);
				throw invalid_argument("���㲻����");

				return -1;
			}
		}

		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexIndex(src);
			size_t dsti = GetVertexIndex(dst);

			// 1->2
			Edge* eg = new Edge(dsti, w);
			eg->_next = _tables[srci];
			_tables[srci] = eg;

			// 2->1
			if (Direction == false)
			{
				Edge* eg = new Edge(srci, w);
				eg->_next = _tables[dsti];
				_tables[dsti] = eg;
			}
		}

		void Print()
		{
			// ����
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				cout << "[" << i << "]" << "->" << _vertexs[i] << endl;
			}
			cout << endl;

			for (size_t i = 0; i < _tables.size(); ++i)
			{
				cout << _vertexs[i] << "[" << i << "]->";
				Edge* cur = _tables[i];
				while (cur)
				{
					cout << "[" << _vertexs[cur->_dsti] << ":" << cur->_dsti << ":" << cur->_w << "]->";
					cur = cur->_next;
				}
				cout << "nullptr" << endl;
			}
		}

	private:
		vector<V> _vertexs;			// ���㼯��
		map<V, int> _indexMap;		// ����ӳ���±�
		vector<Edge*> _tables;		// �ڽӱ�
	};

	void TestGraph1()
	{
		/*Graph<char, int, true> g("0123", 4);
		g.AddEdge('0', '1', 1);
		g.AddEdge('0', '3', 4);
		g.AddEdge('1', '3', 2);
		g.AddEdge('1', '2', 9);
		g.AddEdge('2', '3', 8);
		g.AddEdge('2', '1', 5);
		g.AddEdge('2', '0', 3);
		g.AddEdge('3', '2', 6);

		g.Print();*/

		string a[] = { "����", "����", "����", "����" };
		Graph<string, int, true> g1(a, 4);
		g1.AddEdge("����", "����", 100);
		g1.AddEdge("����", "����", 200);
		g1.AddEdge("����", "����", 30);
		g1.Print();
	}
}