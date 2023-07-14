#include"sort.h"
int main()
{
	std::vector<int> v = { 5,6,7,3,0,4,1,11,10 };
	sort solution;
	/*solution.BubbleSort(v, v.size());
	solution.InsertSort(v, v.size());
	solution.InsertSort0(v, v.size());
	solution.shellSort(v, v.size());*/
	//solution.halfInsertSort(v, v.size());
	//solution.selectsort(v, v.size());
	//solution.heapSort(v, v.size());
	//solution.quickSort(v, 0, v.size()-1);
	solution.quickSortNonR(v, 0, v.size() - 1);
}
