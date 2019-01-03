#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "heap.h"

using namespace std;

class Solution {
public:
	/**
	 * @param num: a non-negative intege
	 * @return: the maximum valued number
	 */
	int maximumSwap(int num)
	{
		/*	堆的存储规则为：
		 *	队列区域保存num各位值，堆区域用num各位值建立大根堆，
		 *
		 *	如果num中有两位相同时，认为低位值大于高位值
		 *	改设定保证了交换时得到最大值，比如 2919，交换后应该为9912
		 */
		heap h(num);

		for (int i = h.buf.size() - 1; i >= 0; i--)
		{
			int tmp = h.peak();

			/*	如果堆中最大的值就是num的最高位值：
			 *  则匹配堆中第二大值和num的次高位值
			 *	直到找出一位第i高位不是第i大值时，进行交换
			 */
			if (tmp == h.buf[i])
			{
				h.pop();
				continue;
			}
			else
			{
				/* 第i高位不是第i大值时：
				 *				 值					位
				 *	第i高位信息：buf[i]				i
				 *	第i大值信息: buf[index[1]]	index[1]
				 */
				int oper1 = h.buf[i] * pow(10, i) + tmp * pow(10, h.index[1]);
				int oper2 = h.buf[i] * pow(10, h.index[1]) + tmp * pow(10, i);

				return (num - oper1 + oper2);
			}
		}
		return num;
	}
};