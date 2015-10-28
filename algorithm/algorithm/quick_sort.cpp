#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include "partition.h"

namespace autumnlight {

// quick sort �ݹ�ʵ�ְ汾
template<typename T>
void quick_sort_recursion(T *arr, size_t len)
{
	if (len <= 1) return;

	int ind = partition2(arr, len);
	quick_sort_recursion(arr, ind);
	quick_sort_recursion(arr + ind + 1, len - ind - 1);
}

// quick sort �ǵݹ�ʵ�ְ汾
template<typename T>
void quick_sort_nonrecursion(T *arr, size_t len)
{
	if (len <= 1) return;

	int ind = partition2(arr, len);

	stack<int> start, end; // start��ſ�ʼλ�ã�end��Ž���λ��
	start.push(ind + 1); end.push(len - 1);
	start.push(0); end.push(ind - 1);

	while (!start.empty())
	{
		auto s = start.top();
		auto e = end.top();
		start.pop(), end.pop();

		if (s < e) // ע������Ҫ�ж���ʼλ�ã���������ջʱ���ÿ���
		{
			ind = partition2(arr + s, e - s + 1);
			start.push(s + ind + 1);
			end.push(e);
			start.push(s);
			end.push(s + ind - 1);
		}
	}
}

// ��������-->ʱ�临�Ӷ�����õ�����¿��ԴﵽO(n)
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

// ��ͨ��ð������
template<typename T>
void bubble_sort(T *arr, int len)
{
	if (!arr || len <= 0) return;

	int i, j;
	for (i = 1; i < len; ++i) // len-1��
	{
		for (j = 0; j < len - i; ++j)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
	}
}

// �Ľ���ð������-->ʱ�临�Ӷ����������¿��ԴﵽO(n)
template<typename T>
void ibubble_sort(T *arr, int len)
{
	if (!arr || len <= 0) return;
	
	int i, j;
	bool flag = false; // ��¼�Ƿ�����������Ԫ�ؽ���˳��
	for (i = 1; i < len; ++i) // len-1��
	{
		for (j = 0; j < len - i; ++j)
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				flag = true;
			}
			else flag = false; // ����Ԫ�ص�λ�ö���ȷ�����������ж��������
		if (!flag) return;

	}
}

// ѡ������
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

