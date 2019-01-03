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
		int len = 0;

		for (int i = 0; i < s.length(); i++)
		{
			int ret = h.push(s[i], i);

			if (ret != -1)	//��Ϊ�����Ѿ����ˣ��������µ��Ӵ�
			{
				len = i - substrStart;	//��ǰ�Ӵ�Ϊ s[substrStart : i-1]
				substrStart = ret + 1;	//����̭Ԫ�����һ�γ���λ�õ���һ��λ��Ϊ���Ӵ���ʼ
				maxLen = (len > maxLen) ? len : maxLen;
			}
		}

		//��string S��ĩβ�п��ܲ���һ��������������Ӵ������һ���Ӵ�����֤:
		len = s.length() - substrStart;

		return (len > maxLen) ? len : maxLen;
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