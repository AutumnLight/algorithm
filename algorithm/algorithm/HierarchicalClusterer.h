#ifndef HIERARCHICAL_CLUSTERER_H

#define HIERARCHICAL_CLUSTERER_H

#include <limits>
#include <list>
#include <set>
#include "distance.h"
#include "comm_type.h"

namespace ml 
{
	template<typename Container>
	class HierachicalClusterer 
	{
	public:
		typedef typename Container::size_type size_t;
		typedef typename Container::value_type DistanceContainer;

		HierachicalClusterer(Distance<DistanceContainer> &d, int n = 1)
			: d(d), classNum(n), data(nullptr) {};
		void cluster();
		void setData(const Container *data) 
		{
			this->data = data;
			dataLen = data->size();
		}
		vector<int> getDataClass()
		{
			return dataClass;
		}
		int getDataClass(int index)  // ���ÿ�������������ע���±��0��ʼ
		{
			return dataClass[i];
		}
	private:
		typedef typename list<set<int>>::iterator iterator;
		double averageDistance(iterator x, iterator y, vvd &distanceMatrix);
		void unionSet(iterator x, iterator y); // �ϲ����Ϊi��j���������
	private:
		Distance<DistanceContainer> &d;
		const Container *data;
		list<set<int>> classRes;	// ÿ��������������ݵ��±�
		vector<int> dataClass;		// ��¼ÿ�������������
		int classNum;	// ����������ɵ������
		int dataLen;
	};


	template<typename Container>
	void HierachicalClusterer<Container>::cluster()
	{
		int i, j;
		int currClassNum = dataLen;
		vector<vector<double>> distanceMatrix(dataLen, vector<double>(dataLen, 0.0));

		// ��ʼ����ÿ��ʵ������Ϊһ��
		for (i = 0; i < currClassNum; i++)
		{
			set<int> s;
			s.insert(i);
			classRes.push_back(s);
		}

		// ��¼��������֮��ľ���
		for (i = 0; i < dataLen; ++i)
		{
			distanceMatrix[i][i] = 0;
			for (j = i + 1; j < dataLen; ++j)
			{
				distanceMatrix[i][j] = d((*data)[i], (*data)[j]);
				distanceMatrix[j][i] = distanceMatrix[i][j];
			}
		}

		while (currClassNum > classNum)
		{
			// �ҵ�����������������
			double minDist = numeric_limits<double>::max(); // ������ľ���
			decltype(classRes.begin()) m, n;		// ������������
			for (auto it = classRes.begin(); it != classRes.end(); ++it)
			{
				auto it2 = it;
				for (++it2; it2 != classRes.end(); ++it2)
				{
					// �������Ϊi��j������ʵ����ƽ������
					double d = averageDistance(it, it2, distanceMatrix);
					if (d < minDist) 
					{
						minDist = d;
						m = it, n = it2;
					}
				}
				
			}

			// �ϲ�
			unionSet(m, n);
			--currClassNum;
		}

		dataClass.resize(dataLen);
		// ��¼ÿ�������������
		for (i = 0; i < dataLen; ++i)
		{
			j = 0;
			for (auto it = classRes.begin(); it != classRes.end(); ++it, ++j)
			{
				if (it->find(i) != it->end())
				{
					dataClass[i] = j;
					break;
				}
			}
		}
		
	}

	template<typename Container>
	double HierachicalClusterer<Container>::averageDistance(
		iterator x, iterator y, vvd &distanceMatrix)
	{
		auto c1 = *x, c2 = *y;
		double dist = 0.0;
		auto len1 = c1.size(), len2 = c2.size();

		for (auto it1 = c1.begin(); it1 != c1.end(); ++it1)
			for (auto it2 = c2.begin(); it2 != c2.end(); ++it2)
				dist += distanceMatrix[*it1][*it2];
		return dist / (len1 * len2);
	}

	template<typename Container>
	void HierachicalClusterer<Container>::unionSet(iterator x, iterator y)
	{
		// �ѽ��ٵļ��Ϻϲ����ϴ�ļ�����
		if (x->size() < y->size())
		{
			y->insert(x->begin(), x->end());
			classRes.erase(x);
		}
		else
		{
			x->insert(y->begin(), y->end());
			classRes.erase(y);
		}
	}
}

#endif