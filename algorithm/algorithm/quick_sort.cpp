#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include "partition.h"

namespace autumnlight {

// quick sort 递归实现版本
template<typename T>
void quick_sort_recursion(T *arr, size_t len)
{
	if (len <= 1) return;

	int ind = partition2(arr, len);
	quick_sort_recursion(arr, ind);
	quick_sort_recursion(arr + ind + 1, len - ind - 1);
}

// quick sort 非递归实现版本
template<typename T>
void quick_sort_nonrecursion(T *arr, size_t len)
{
	if (len <= 1) return;

	int ind = partition2(arr, len);

	stack<int> start, end; // start存放开始位置，end存放结束位置
	start.push(ind + 1); end.push(len - 1);
	start.push(0); end.push(ind - 1);

	while (!start.empty())
	{
		auto s = start.top();
		auto e = end.top();
		start.pop(), end.pop();

		if (s < e) // 注意这里要判断起始位置，接下来入栈时不用考虑
		{
			ind = partition2(arr + s, e - s + 1);
			start.push(s + ind + 1);
			end.push(e);
			start.push(s);
			end.push(s + ind - 1);
		}
	}
}

// 插入排序-->时间复杂度在最好的情况下可以达到O(n)
template<typename T>
void insert_sort(T *arr, int len)
{
	if (len <= 0 || !arr) return;
	for (int i = 1; i < len; ++i)
	{
		T tmp(arr[i]);
		int j;
		for (j = i - 1; j >= 0 && arr[j] > tmp; --j)
			arr[j + 1] = arr[j];
		arr[j + 1] = tmp;
	}
}

// 普通的冒泡排序
template<typename T>
void bubble_sort(T *arr, int len)
{
	if (!arr || len <= 0) return;

	int i, j;
	for (i = 1; i < len; ++i) // len-1趟
	{
		for (j = 0; j < len - i; ++j)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
	}
}

// 改进的冒泡排序-->时间复杂度在最好情况下可以达到O(n)
template<typename T>
void ibubble_sort(T *arr, int len)
{
	if (!arr || len <= 0) return;
	
	int i, j;
	bool flag = false; // 记录是否有两个相邻元素交换顺序
	for (i = 1; i < len; ++i) // len-1趟
	{
		for (j = 0; j < len - i; ++j)
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				flag = true;
			}
			else flag = false; // 相邻元素的位置都正确，则整个序列都是排序的
		if (!flag) return;

	}
}

// 选择排序
template<typename T>
void select_sort(T *arr, int len)
{
	if (!arr || len <= 0) return;
	int i, j;
	for (i = 0; i < len - 1; ++i)
		for (j = i + 1; j < len; ++j)
			if (arr[i] > arr[j]) swap(arr[i], arr[j]);
}

};

template <typename T>
class IsOne {
public:
	bool operator() (T &t) {
		return t == 1;
	}
};

template <typename T>
class Print {
public:
	void operator() (T &t, string delimiter = " ") {
		cout << t << delimiter;
	}
};

//int main()
//{
//	vector<int> a;
//	a.push_back(3);
//	a.push_back(2);
//	a.push_back(8);
//	a.push_back(6);
//	a.push_back(9);
//	a.push_back(7);
//	a.push_back(4);
//
//	//autumnlight::quick_sort_nonrecursion(a.data(), a.size());
//	//autumnlight::insert_sort(a.data(), a.size());
//	autumnlight::bubble_sort(a.data(), a.size());
//
//	for_each(a.begin(), a.end(), Print<int>());
//	cout << endl;
//
//	int b[] = {2, 1, 2, 1, 2, 1};
//	int len = sizeof(b) / sizeof(int);
//	autumnlight::partition2(b, len, IsOne<int>());
//	for_each(begin(b), end(b), Print<int>());
//	cout << endl;
//	system("PAUSE");
//	return 0;
//}

