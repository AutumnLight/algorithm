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
		int getDataClass(int index)  // 获得每个数据所属类别，注意下标从0开始
		{
			return dataClass[i];
		}
	private:
		typedef typename list<set<int>>::iterator iterator;
		double averageDistance(iterator x, iterator y, vvd &distanceMatrix);
		void unionSet(iterator x, iterator y); // 合并类别为i和j的两个类别
	private:
		Distance<DistanceContainer> &d;
		const Container *data;
		list<set<int>> classRes;	// 每个类别所包含数据的下标
		vector<int> dataClass;		// 记录每个数据所属类别
		int classNum;	// 聚类最后生成的类别数
		int dataLen;
	};


	template<typename Container>
	void HierachicalClusterer<Container>::cluster()
	{
		int i, j;
		int currClassNum = dataLen;
		vector<vector<double>> distanceMatrix(dataLen, vector<double>(dataLen, 0.0));

		// 初始化，每个实例单独为一类
		for (i = 0; i < currClassNum; i++)
		{
			set<int> s;
			s.insert(i);
			classRes.push_back(s);
		}

		// 记录两两数据之间的距离
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
			// 找到距离最近的两个类别
			double minDist = numeric_limits<double>::max(); // 最近类别的距离
			decltype(classRes.begin()) m, n;		// 最近类别的类别编号
			for (auto it = classRes.begin(); it != classRes.end(); ++it)
			{
				auto it2 = it;
				for (++it2; it2 != classRes.end(); ++it2)
				{
					// 计算类别为i和j的所有实例的平均距离
					double d = averageDistance(it, it2, distanceMatrix);
					if (d < minDist) 
					{
						minDist = d;
						m = it, n = it2;
					}
				}
				
			}

			// 合并
			unionSet(m, n);
			--currClassNum;
		}

		dataClass.resize(dataLen);
		// 记录每个数据所属类别
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
		// 把较少的集合合并到较大的集合中
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