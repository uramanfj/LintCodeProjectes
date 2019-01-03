#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef __HEAP_H__
#define __HEAP_H__

using namespace std;

/* 使用堆来统计每个元素最新出现时间中最早的那个
 * 如果堆满，则弹出最早出现的那个，加入新的元素，并更新当前子串的信息
 */
class heap
{
private:
	const int capacity;		//窗口最大长度
	int top;				//堆大小指针
	map<char, int> elem;	//存放当前窗口
	vector<int> buffer;		//为了迅速找出最小值，一个堆用来存放elem中的key值

	//堆顶元素
	inline int peak()
	{
		if (top < 1)
			return -1;

		return elem[buffer[top]];
	}

	//比较函数
	inline bool cmp(int index1, int index2)
	{
		return (elem[buffer[index1]] < elem[buffer[index2]]);
	}

	inline void mySwap(int index1, int index2)
	{
		auto temp = buffer[index1];
		buffer[index1] = buffer[index2];
		buffer[index2] = temp;
		return;
	}

	//上翻
	void rollUp(int sub)
	{
		if (sub <= 1)
		{
			return;
		}

		int pare = sub / 2;

		while (pare > 0)
		{
			int min = pare;

			if (2 * pare <= top)
				min = cmp(pare, 2 * pare) ? pare : 2 * pare;

			if (2 * pare + 1 <= top)
				min = cmp(min, 2 * pare + 1) ? min : 2 * pare + 1;

			if (min == pare)
				return;

			mySwap(min, pare);

			pare /= 2;
		}
	}

	void rollDown(int sub)
	{
		if (sub < 1)
		{
			return;
		}

		int pare = sub;

		while (pare <= top / 2)
		{
			int min = pare;

			if (2 * pare <= top)
				min = cmp(pare, 2 * pare) ? pare : 2 * pare;

			if (2 * pare + 1 <= top)
				min = cmp(min, 2 * pare + 1) ? min : 2 * pare + 1;

			if (min == pare)
				return;

			mySwap(min, pare);

			pare = min;
		}
	}

public:
	heap() :top(0), capacity(1), buffer(2)
	{
		//从buffer[1] 开始存储
		buffer[0] = -1;
	}

	heap(int num) :top(0), capacity(num), buffer(num + 1)
	{
		buffer[0] = -1;
	}

	int bufferSize() { return top; }

	int pop()
	{
		if (top < 1)
			return -1;

		auto keynum = buffer[1];
		int ret = peak();
		
		buffer[1] = buffer[top--];
		rollDown(1);

		elem.erase(keynum);

		return ret;
	}

	//push时，如果窗口未满，则直接加入窗口，如果窗口满了，则弹出堆顶
	int push(char keynum, int valnum)
	{
		//如果新push的元素为子串中重复出现的元素
		auto it = elem.find(keynum);
		if (it != elem.end())
		{
			it->second = valnum;
			
			for (int i = 1; i <= top; i++)
			{
				if (buffer[i] == it->first)
				{
					rollDown(i);
					return -1;
				}
			}
			return -1;	//这一句不会执行，因为如果在map中找到的元素，则堆中一定存在。写这个为了消warning
		}

		//新元素在子串中第一次出现，但当前窗口未满
		if (top < capacity)
		{
			elem[keynum] = valnum;
			buffer[++top] = keynum;
			rollUp(top);
			return -1;
		}

		//新元素为第一次出现元素，且当前窗口已经满了
		int ret = peak();
		auto mapkey = buffer[1];
		elem[keynum] = valnum;

		buffer[1] = keynum;
		rollDown(1);

		elem.erase(mapkey);

		return ret;
	}
};
#endif // !__HEAP_H__
