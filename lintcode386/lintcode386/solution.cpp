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

		int substrStart = 0;	//当前子串开始下标
		int maxLen = 0;			//统计过得最长子串长度
		int i = 0;
		int len = 0;

		for ( i = 0; i < s.length(); i++)
		{
			ELEM e(s[i], i);
			auto ret = h.push(e);

			if (ret.first)		//ret.first == true 即为窗口已经满了，创建了新的子串
			{
				len = i - substrStart; //当前子串为 s[substrStart : i-1]
				substrStart = ret.second.second + 1;	//被淘汰元素最后一次出现位置的下一个位置为新子串开始
				maxLen = (len > maxLen) ? len : maxLen;
			}
		}

		//在string S的末尾有可能产生一个最长满足条件的子串，最后一个子串的验证:
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