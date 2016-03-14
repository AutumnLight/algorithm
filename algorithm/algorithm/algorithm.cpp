// algorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "distance.h"
#include "HierarchicalClusterer.h"
#include "comm_type.h"

using namespace std;


int test2(int n, int step) {
	if (n == 0 && (step & 1)) return 0;
	if (n == 0 && !(step & 1)) return 1;
	if (n == 1 && (step & 1)) return 1;
	if (n == 1 && !(step & 1)) return 0;
	return test2(n - 1, step + 1) + test2(n - 2, step + 1);

}

void test1() {
	int n, res;
	cin >> n;
	res = test2(n, 0);

	cout << res;
}


int main()
{
	/*ml::EditDistance<vint> ed;
	ml::NormalizedDistance<vint> nd(ed);

	ifstream ifs("./data/trend_angle.txt");
	vector<vint> data2;
	string line;
	while (!ifs.eof()) {
		getline(ifs, line);
		if (line.empty()) continue;
		vint tmp;
		string2Ints(line, tmp, ' ');
		data2.push_back(tmp);
	}
	ml::HierachicalClusterer<vvint> hc2(nd, 7, ml::HierachicalClusterer<vvint>::SINGLE);
	hc2.setData(&data2);
	hc2.cluster();
	vector<int> res2 = hc2.getDataClass();
	for (size_t i = 0; i < res2.size(); i++)
	{
		cout << res2[i] << " ";
		if ((i + 1) % 20 == 0) cout << endl;
	}*/

	test1();
	system("PAUSE");
    return 0;
}


