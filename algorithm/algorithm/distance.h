#ifndef DISTANCE_H

#define DISTANCE_H
#include <algorithm>

namespace ml { // mlΪmachine learning����д
	template <typename T>
	class Distance
	{
	public:
		typedef T Container;
		virtual double operator() (const T &t1, const T &t2) = 0;
	};

	template <typename Container>
	class EditDistance : public Distance<Container>
	{
	public:
		typedef typename Container::size_type size_t;
		double operator() (const Container &c1, const Container &c2);
	};

	// ��׼����ľ��룬�μ�weka��׼���������
	// ����ʹ��װ����ģʽ�������
	template <typename Container>
	class NormalizedDistance : public Distance<Container>
	{
	public:
		typedef typename Container::size_type size_t;
		NormalizedDistance(Distance<Container> &d) : dist(d) {}
		double operator() (const Container &c1, const Container &c2)
		{
			double maxLen = c1.size() > c2.size() ? c1.size() : c2.size();
			double d = dist(c1, c2);
			return d / maxLen;
		}
	private:
		Distance &dist; // ����Ӧ������Ϊ���ã�����ᱨ���޷�ʵ���������ࡱ
						// �������ͱ����ڹ��캯����ʼ���б��г�ʼ��������ͬ��
	};

	// EditDistance��ʵ��
	template <typename Container>
	double EditDistance<Container>::operator() (const Container &c1, const Container &c2)
	{
		size_t len1 = c1.size();
		size_t len2 = c2.size();
		size_t maxLen = len1 > len2 ? len1 : len2;
		size_t i, j;

		vector<int> row0(len2 + 1, 0);
		vector<int> row1(len2 + 1, 0);

		// ��һ��
		for (i = 0; i <= len2; ++i) row0[i] = i;

		for (i = 1; i <= len1; ++i)
		{
			row1[0] = i;
			for (j = 1; j <= len2; ++j)
				if (c1[i - 1] == c2[j - 1])
					row1[j] = row0[j - 1];
				else
					row1[j] = 1 + min(row0[j - 1], min(row0[j], row1[j - 1]));
			copy(row1.begin(), row1.end(), row0.begin());
			
		}

		return row0[len2];
	}
}

#endif