#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef __HEAP_H__
#define __HEAP_H__

using namespace std;

/*记录每个元素最新出现时间*/
typedef pair<char, int> ELEM;

/* 使用堆来统计每个元素最新出现时间中最早的那个
 * 如果堆满，则弹出最早出现的那个，加入新的元素，并更新当前子串的信息
 */
class heap
{
private:
	const int capacity;	//窗口最大长度
	int top;			//堆大小指针
	vector<ELEM> buffer;

	//堆顶元素
	ELEM& peak()
	{
		if (top < 1)
			return buffer[0];

		return buffer[top];
	}

	//比较函数
	inline bool cmp(int num1, int num2)
	{
		return (buffer[num1].second < buffer[num2].second);
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

			buffer[pare].swap(buffer[min]);

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

			buffer[pare].swap(buffer[min]);

			pare = min;
		}
	}

public:
	heap() :top(0), capacity(1), buffer(2)
	{
		//从buffer[1] 开始存储
		buffer.push_back(ELEM());
	}

	heap(int num) :top(0), capacity(num), buffer(num + 1)
	{
		buffer.push_back(ELEM());
	}

	int bufferSize() { return top; }

	ELEM pop()
	{
		if (top < 1)
			return ELEM();

		ELEM ret = peak();
		
		buffer[1] = buffer[top--];
		rollDown(1);

		return ret;
	}

	//push时，如果窗口未满，则直接加入窗口，如果窗口满了，则弹出堆顶
	pair<bool, ELEM> push(ELEM& e)
	{
		if (top < capacity)
		{
			buffer[++top] = e;
			rollUp(top);
			return make_pair(false, peak());
		}
		//else top == capacity
		ELEM ret = peak();
		buffer[1] = e;
		rollDown(1);
		return make_pair(true, ret);
	}
};
#endif // !__HEAP_H__
