#include "stdafx.h"
#include "lib.h"
namespace autumnlight {
	namespace utils {
		using namespace std;
		bool string2Ints(const string &str, vint &ints, char delim)
		{
			auto iter = str.begin();
			int t = 0;
			for (; iter != str.end(); ++iter)
			{
				if (*iter == delim)
				{
					ints.push_back(t);
					t = 0;
				}
				else if (*iter >= '0' && *iter <= '9')
				{
					t = t * 10 + *iter - '0';
				}
				else return false;
			}
			ints.push_back(t);  // 最后一个数值
			return true;
		}
	}
}