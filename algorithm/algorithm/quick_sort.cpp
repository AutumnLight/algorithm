#include "stdafx.h"
#include "partition.h"
#include <iostream>
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

};

template <typename T>
class IsOne {
public:
	bool operator() (T &t) {
		return t == 1;
	}
};

int main()
{
	vector<int> a;
	a.push_back(3);
	a.push_back(2);
	a.push_back(8);
	a.push_back(6);
	a.push_back(9);
	a.push_back(7);
	a.push_back(4);
	autumnlight::quick_sort_recursion(a.data(), a.size());

	//for_each(a.begin(), a.end(), Print<int>());
	int b[] = {1, 2, 1, 2, 1, 2};
	int len = sizeof(b) / sizeof(int);
	autumnlight::partition(b, len, IsOne<int>());
	for (int i = 0; i < len; ++i)
		cout << b[i] << " ";
	cout << endl;
	system("PAUSE");
	return 0;
}

