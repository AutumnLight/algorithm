// algorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "distance.h"
#include "HierarchicalClusterer.h"

using namespace std;
int main()
{
	/*ml::EditDistance<string> ed;
	string str1("abc");
	string str2("abcd");
	double dist = ed(str1, str2);
	cout << dist << endl;

	ml::NormalizedDistance<string> nd(ed);
	double dist2 = nd(str1, str2);
	cout << dist2 << endl;*/

	/*vector<int> a{ 1,2,3,4,5 };
	vector<int> b{ 1,3,3,4,5 };
	vector<int> c{ 1,4,4,4,5 };
	vector<int> d{ 1,5,4,4,5 };
	vector<vector<int>> data;
	data.push_back(a);
	data.push_back(b);
	data.push_back(c);
	data.push_back(d);
	ml::EditDistance<vector<int>> ed2;
	ml::HierachicalClusterer<vector<vector<int>>> hc(ed2, 2);
	hc.setData(&data);
	hc.cluster();
	vector<int> res = hc.getDataClass();
	for (size_t i = 0; i < res.size(); i++)
	{
		cout << res[i] << " ";
	}
	cout << endl;*/

	ifstream ifs("0_5_angle.arff");
	vector<string> data2;
	string line;
	while (!ifs.eof()) {
		getline(ifs, line);
		if (line.empty()) continue;
		data2.push_back(line);
	}
	ml::HierachicalClusterer<vector<string>> hc2(nd, 7);
	hc2.setData(&data2);
	hc2.cluster();
	vector<int> res2 = hc2.getDataClass();
	for (size_t i = 0; i < res2.size(); i++)
	{
		cout << res2[i] << " ";
	}
	cout << endl;
	system("PAUSE");
    return 0;
}

