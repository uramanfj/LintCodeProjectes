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
		/*	�ѵĴ洢����Ϊ��
		 *	�������򱣴�num��λֵ����������num��λֵ��������ѣ�
		 *
		 *	���num������λ��ͬʱ����Ϊ��λֵ���ڸ�λֵ
		 *	���趨��֤�˽���ʱ�õ����ֵ������ 2919��������Ӧ��Ϊ9912
		 */
		heap h(num);

		for (int i = h.buf.size() - 1; i >= 0; i--)
		{
			int tmp = h.peak();

			/*	�����������ֵ����num�����λֵ��
			 *  ��ƥ����еڶ���ֵ��num�Ĵθ�λֵ
			 *	ֱ���ҳ�һλ��i��λ���ǵ�i��ֵʱ�����н���
			 */
			if (tmp == h.buf[i])
			{
				h.pop();
				continue;
			}
			else
			{
				/* ��i��λ���ǵ�i��ֵʱ��
				 *				 ֵ					λ
				 *	��i��λ��Ϣ��buf[i]				i
				 *	��i��ֵ��Ϣ: buf[index[1]]	index[1]
				 */
				int oper1 = h.buf[i] * pow(10, i) + tmp * pow(10, h.index[1]);
				int oper2 = h.buf[i] * pow(10, h.index[1]) + tmp * pow(10, i);

				return (num - oper1 + oper2);
			}
		}
		return num;
	}
};