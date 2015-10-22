#include "stdafx.h"
namespace autumnlight {

// 提取中位数的下标
template<typename T>
int mymiddle(T *arr, int ind1, int ind2, int ind3)
{
	if (arr[ind1] <= arr[ind2] && arr[ind2] <= arr[ind3]
		|| arr[ind3] <= arr[ind2] && arr[ind2] <= arr[ind1])
		return ind2;
	if (arr[ind2] <= arr[ind1] && arr[ind1] <= arr[ind3]
		|| arr[ind3] <= arr[ind1] && arr[ind1] <= arr[ind2])
		return ind1;
	if (arr[ind1] <= arr[ind3] && arr[ind3] <= arr[ind2]
		|| arr[ind2] <= arr[ind3] && arr[ind3] <= arr[ind1])
		return ind3;
}

template<typename T>
int partition(T *arr, int len)
{
	int mid_ind = mymiddle(arr, 0, len / 2, len - 1);

	swap(arr[mid_ind], arr[0]);
	T pivot(arr[0]);

	int s = 0, e = len - 1;
	while (s < e)
	{
		while (s < e && arr[e] > pivot) --e;
		if (s < e) arr[s++] = arr[e];
		while (s < e && arr[s] < pivot) ++s;
		if (s < e) arr[e--] = arr[s];
	}
	arr[s] = pivot;
	return s;
}

template<typename T, typename Pred>
void partition(T *arr, int len, Pred pred)
{
	int s = 0, e = len - 1;
	while (s < e)
	{
		while (s < e && pred(arr[s])) ++s;
		while (s < e && !pred(arr[e])) --e;
		if (s < e)
			swap(arr[s], arr[e]);
	}
}


template<typename T>
int partition2(T *arr, int len)
{
	int mid_ind = mymiddle(arr, 0, len / 2, len - 1);
	// 主元放在最后的位置上，若主元在其他位置上会产生错误
	swap(arr[mid_ind], arr[len - 1]); 

	int i, j;
	for (i = -1, j = 0; j < len; ++j)
		if (arr[j] < arr[mid_ind]) swap(arr[++i], arr[j]);
	swap(arr[++i], arr[mid_ind]);
	return i;
}

template<typename T, typename Pred>
void partition2(T *arr, int len, Pred pred)
{
	for (int i = -1, j = 0; j < len; j++)
		if (pred(arr[j])) swap(arr[++i], arr[j]);
}

}