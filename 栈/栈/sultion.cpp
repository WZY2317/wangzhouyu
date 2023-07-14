#include<stack>
#include<queue>
#include<string>

class sultion {
	struct node {
		int i;
		int value;
	};
	static int que03(int x,int n)
	{
		std::stack<node> st;
		int value1 = 1, value2 = 2 * x;
		for (int i = n; i >= 2; i++)
		{
			node n;
			n.i = i;
			st.push(n);
		}//»Î’ª
		while (!st.empty())
		{
			st.top().value = 2 * x * value2 - 2 * (st.top().i - 1) * value1;
			value1 = value2;
			value2 = st.top().value;
			st.pop();
		}
		if (n == 0)
			return value1;
		return value2;

	}
	static void ques04()
	{
		std::queue<std::string> q;
		std::queue<std::string> busq;
		std::queue<std::string> structq;
		int i = 0, j = 0;
		while (q.size() < 10)
		{
			if (!busq.empty() && busq.size() != 4)
			{
				busq.push("bus");
			}
			if (busq.size() >= 4 && !structq.empty()&& q.size() < 10)
			{
				int cnt = 0;
				while (!busq.empty())
				{
					cnt++;
					q.push("bus");
					busq.pop();
					if (cnt == 4)
						break;
				}
				q.push("stuck");
				structq.pop();
			}
			else if (busq.size() < 4)
			{
				int cnt = 0;
				while (cnt!=4)
				{
					cnt++;
					if (!busq.empty())
					{
						q.push("bus");
						busq.pop();
					}
					else if (!structq.empty())
					{
						q.push("stuck");
						structq.pop();
					}
					if (cnt == 4)
						break;
				}
			}
		}
	}
};