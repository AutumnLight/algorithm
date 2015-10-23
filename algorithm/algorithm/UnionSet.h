#ifndef UNIONSET_H
#define UNIONSET_H

class DijointSet
{
public:
	DijointSet(int num) : father(num)
	{
		for (size_t i = 0; i < father.size(); ++i)
			father[i] = i;
	}
	int getFather(int v)
	{
		if (father[v] != v)
			father[v] = getFather(father[v]);
		return father[v];
	}
	int uionSet(int x, int y) 
	{
		father[getFather(x)] = getFather(y);
	}
	bool isSame(int x, int y)
	{
		return getFather(x) == getFather(y);
	}
private:
	vector<int> father;
};

#endif

