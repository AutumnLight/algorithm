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

		int **distanceMatrix = new int*[len1 + 1];

		size_t i, j;
		for (i = 0; i <= len1; ++i)
			distanceMatrix[i] = new int[len2 + 1];

		// ��һ��-->��ʼ��Ϊ0
		for (i = 0; i <= len2; ++i) distanceMatrix[0][i] = 0;

		// ��һ��-->��ʼ��Ϊ0
		for (i = 1; i < len1; ++i) distanceMatrix[i][0] = 0;

		for (i = 1; i <= len1; ++i)
			for (j = 1; j <= len2; ++j)
				if (c1[i-1] == c2[j-1])
					distanceMatrix[i][j] = distanceMatrix[i - 1][j - 1];
				else
					distanceMatrix[i][j] = 1 +
					min(distanceMatrix[i][j - 1],		// ����
						min(distanceMatrix[i - 1][j],		// ɾ��
							distanceMatrix[i - 1][j - 1])); // �޸�

		double dist = distanceMatrix[len1][len2];

		for (i = 0; i < len1; ++i)
			delete[] distanceMatrix[i];

		delete[] distanceMatrix;
		return dist;
	}
}

#endif