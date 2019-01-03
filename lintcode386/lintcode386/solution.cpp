#include <iostream>
#include <vector>
#include <string>
#include "heap.h"

using namespace std;

class Solution {
public:
	/**
	 * @param s: A string
	 * @param k: An integer
	 * @return: An integer
	 */
	int lengthOfLongestSubstringKDistinct(string &s, int k) {
		heap h(k);

		int substrStart = 0;	//��ǰ�Ӵ���ʼ�±�
		int maxLen = 0;			//ͳ�ƹ�����Ӵ�����
		int i = 0;
		int len = 0;

		for ( i = 0; i < s.length(); i++)
		{
			ELEM e(s[i], i);
			auto ret = h.push(e);

			if (ret.first)		//ret.first == true ��Ϊ�����Ѿ����ˣ��������µ��Ӵ�
			{
				len = i - substrStart; //��ǰ�Ӵ�Ϊ s[substrStart : i-1]
				substrStart = ret.second.second + 1;	//����̭Ԫ�����һ�γ���λ�õ���һ��λ��Ϊ���Ӵ���ʼ
				maxLen = (len > maxLen) ? len : maxLen;
			}
		}

		//��string S��ĩβ�п��ܲ���һ��������������Ӵ������һ���Ӵ�����֤:
		len = i - substrStart;
		maxLen = (len > maxLen) ? len : maxLen;

		return maxLen;
	}
};

int main()
{
	Solution s;
	string str("eceba");
	int len = s.lengthOfLongestSubstringKDistinct(str, 3);

	cout << len << endl;

	return 0;
}

//End of File