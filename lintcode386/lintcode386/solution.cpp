#include <iostream>
#include <vector>
#include <string>
#include "mapwindow.h"

using namespace std;

class Solution {
public:
	/**
	 * @param s: A string
	 * @param k: An integer
	 * @return: An integer
	 */
	int lengthOfLongestSubstringKDistinct(string &s, int k) {
		//窗口长度为0
		if (k == 0)
			return 0;

		/* 原先使用heap，出现了问题，更新思路：单独使用map*/
		mapwindow mw(s, k);

		int substrStart = 0;	//当前子串开始下标
		int maxLen = 0;			//统计过得最长子串长度
		int len = 0;

		for (int i = 0; i < s.length(); i++)
		{
			int ret = mw.push(i);

			if (ret != -1)	//即为窗口已经满了，创建了新的子串
			{
				len = i - substrStart;	//当前子串为 s[substrStart : i-1]
				substrStart = ret + 1;	//被淘汰元素最后一次出现位置的下一个位置为新子串开始
				maxLen = (len > maxLen) ? len : maxLen;
			}
		}
		//在string S的末尾有可能产生一个最长满足条件的子串，最后一个子串的验证:
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