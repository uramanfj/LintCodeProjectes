#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef __HEAP_H__
#define __HEAP_H__

using namespace std;

class heap
{
public:
	int top;
	vector<int> buf;
	vector<int> index;

	heap() :top(0)
	{
		index.push_back(-1);
	}

	heap(int num) :top(0)
	{
		index.push_back(-1);

		int i = 0;
		while (num > 0)
		{
			buf.push_back(num % 10);
			num /= 10;
			push(i++);
		}
	}

	int peak()
	{
		if (top < 1)
		{
			return -1;
		}

		return buf[index[1]];
	}

	bool cmp(int num1, int num2)
	{
		if ((buf[index[num1]] > buf[index[num2]]) ||
			(buf[index[num1]] == buf[index[num2]]) && (num1 < num2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void rollUp(int sub)
	{
		if (sub <= 1)
		{
			return;
		}

		int pare = sub / 2;

		while (pare > 0)
		{
			int max = pare;

			if (2 * pare <= top)
			{
				max = cmp(pare, 2 * pare) ? pare : 2 * pare;
			}

			if (2 * pare + 1 <= top)
			{
				max = cmp(max, 2 * pare + 1) ? max : 2 * pare + 1;
			}

			if (max == pare)
			{
				return;
			}

			int tmp = index[max];
			index[max] = index[pare];
			index[pare] = tmp;

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
			int max = pare;

			if (2 * pare <= top)
			{
				max = cmp(pare, 2 * pare) ? pare : 2 * pare;
			}

			if (2 * pare + 1 <= top)
			{
				max = cmp(max, 2 * pare + 1) ? max : 2 * pare + 1;
			}

			if (max == pare)
			{
				return;
			}

			int tmp = index[max];
			index[max] = index[pare];
			index[pare] = tmp;

			pare = max;
		}
	}

	void push(int elem)
	{
		top++;
		index.push_back(elem);
		rollUp(top);
	}

	int	pop()
	{
		if (top < 1)
		{
			return -1;
		}

		int ret = index[1];

		index[1] = index[top--];
		index.pop_back();
		rollDown(1);

		return buf[ret];
	}
};
#endif // !__HEAP_H__
