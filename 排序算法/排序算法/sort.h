#pragma once
#include<vector>
#include <iostream>
#include<stack>
void printV(std::vector<int> V)
{
	for (auto e : V)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}
class area
{
private:
	int _left;
	int _right;
public:
	area(int left,int right)
	{
		_left = left;
		_right = right;
	}
};
class sort
{
public:
	
	static void BubbleSort(std::vector<int> V,int Vsize)
	{
		for (int endi = Vsize - 1; endi > 1; endi--)
		{
			for (int i = 0; i < endi; i++)
			{
				if (V[i] > V[i + 1])
					std::swap(V[i], V[i + 1]);
			}
		}
		
		printV(V);
	}
	//O(n^2)
	static void selectSort(std::vector<int> V, int Vsize)
	{
		std::vector<int> res;
		int MinNum = INT_MAX;
		int MinNumindex = 0;
		int i = 0;
		for (int begini = 0; begini < Vsize - 1; begini++)
		{
			for ( i = begini; i < Vsize; i++)
			{
				
				if (V[i] < MinNum)
				{
					 MinNumindex = i;
					 MinNum = V[i];
				}
			
			}
			std::swap(V[begini], V[MinNumindex]);
			MinNum = INT_MAX;
		}
		printV(V);
		//O(n^2)
	
	}
	static void InsertSort0(std::vector<int> V, int Vsize)
	{
		int i = 0;
		while (i<Vsize-1)
		{
			int end = i;
			int x = V[i + 1];
			while (end >= 0)
			{
				if (V[end] > x)
				{
					V[end + 1] = V[end];
					end--;
				}
				else
				{
					break;
				}
			}
			V[end + 1] = x;
			i++;
		}
		printV(V);

		//先写单趟
		
	}
	static void halfInsertSort(std::vector<int> arr, int size)
	{
		int i, j, low, high, mid;
		for (int i = 1; i <= size; i++)
		{
			int key = arr[i];
			
			low = 0;
			high = i - 1;
			
			while (low <= high)
			{
				 mid = (low + high) / 2;
				if (arr[0] > arr[mid])
				{
					low = mid + 1;
				}
				if (arr[0] < arr[mid])
				{
					high = mid - 1;
				}
				
			}
			for (j = i - 1; j >= high + 1; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[high + 1] = arr[0];
		}
	}
	static void shellSort(std::vector<int> arr, int size)
	{

		int gap = size;
		while (gap > 1)
		{
			gap /= 2;
			
			{
				for (int i = 0; i < size - gap; i += gap)
				{
					int end = i;
					int x = arr[end + gap];
					while (end > 0)
					{
						if (arr[end] > x)
						{
							arr[end + gap] = arr[end];
							end -= gap;
						}
						else
							break;
					}
					arr[end + gap] = x;
				}
			}
		}
		
		
		
	}
	static void selectsort(std::vector<int> arr, int size)
	{
		int begin = 0, end = size - 1;
		while (begin < end)
		{
			int mini = begin, maxi = begin;
			for (int i = begin; i <= end; i++)
			{
				if (arr[i] > arr[maxi])
				{
					maxi = i;
				}
				if (arr[i] < arr[mini])
				{
					mini = i;	
				}
			} 
			std::swap(arr[begin], arr[mini]);
			if (begin == maxi)
			{
				maxi = mini;
			}
			std::swap(arr[end], arr[maxi]);
			begin++;
			end--;
		}
		printV(arr);
		
	}
	static void heapSort(std::vector<int> arr, int size)
	{
		int n = size;
		for (int end = (n - 1 - 1) / 2; end >= 0; end--)
		{
			downAdjust(arr, n, end);
		}
		//建立大根堆
		for (int i = n - 1; i > 0; i--)
		{
			std::swap(arr[i], arr[0]);
			downAdjust(arr, i, 0);
		}//进行调整
		printV(arr);
	}
	static void downAdjust(std::vector<int>& arr, int size,int i)
	{
		int parent = i;
		int child = 2 * i + 1;
		while (child < size)
		{
			if (arr[child] < arr[child + 1] && child + 1 < size)
				child++;
			if (arr[parent] < arr[child])
			{
				std::swap(arr[parent], arr[child]);
				parent = child;
				child = child * 2 + 1;

			}
			else
				break;
		}
		

	}
	static void quickSort(std::vector<int>& arr,int left,int right)
	{
		if (left > right)
			return;
		int index = partionSort(arr, left, right);
		quickSort(arr,0, index - 1);
		quickSort(arr, index + 1, right);
		printV(arr);
	}
	static int partionSort(std::vector<int>& arr,int left,int right)
	{
		int pivot = left;
		int key = arr[pivot];
		
		while (left<right)
		{
			while (left<right && arr[right]>=key)
			
				right--;
			
			arr[left] = arr[right];
			while (left < right && arr[left] <= key)
				left++;
			arr[right] = arr[left];
			
		}
		arr[left] = key;
		return left;
		

	}
	static void quickSortNonR(std::vector<int>& arr, int left, int right)
	{
		
		std::stack<int> st;
		st.push(left); 
		st.push(right);
		while (!st.empty())
		{
			int end = st.top();
			st.pop();
			int begin = st.top();
			st.pop();
			int keyindex = partionSort(arr, begin, end);
			if (keyindex + 1 < end)
			{
				st.push(keyindex + 1);
				st.push(end);
			}
			if (keyindex - 1 > begin)
			{	
				st.push(begin);
				st.push(keyindex - 1);
				
			}
		}
		//printV(arr);

	}
	static void merge(std::vector<int>& arr,int left,int right,int mid)
	{
		std::vector<int> another(0,arr.size());
		for (int i = left; i <= right; i++)
		{
			another[i] = arr[i];
		}
		//比较b左右两段的元素把小的复制到arr中
		for (int i = left, j = mid + 1,k=i; i <= mid, j <= right; k++)
		{
			if (another[i] > another[j])
				arr[k] = another[j++];
			else
				arr[k] = another[i++];
		}
		while (i <= mid)
		{
			arr[k++] = another[i++];
		}
		while (j <= high)
		{
			arr[k++] = another[j++];
		}

	}
	static void mergeSort(std::vector<int>& arr, int left, int right);
	{
		if (left > right)
			return;
		else
		{
			int mid = (left + right) / 2;
			mergeSort(arr, left, mid);//左边有序
			mergeSort(arr, mid + 1, right);//右边有序
			merge(arr, left, right, mid);//归并
		}
	}
	static void mergeSortNonR(std::vector<int>& arr, int left, int right)
	{
		std::stack<int> st;
		int mid = (left + right) / 2;
		st.push(left);
		st.push(right);
		while (!st.empty())
		{
			if (left < mid&& mid + 1 < right)
			{
				st.push(left);
				st.push(mid);
				st.push(mid + 1);
				st.push(right);
			
			}
			
			else if (left + 1 == mid&&mid+1=right)
			{
				merge(ar, left, mid);
				merge(arr, mid + 1, right);
				st.pop();
				st.pop();
				st.pop();
				st.pop();

			}
			
			

		}
	}
	
 };
