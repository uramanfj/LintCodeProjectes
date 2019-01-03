#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef __HEAP_H__
#define __HEAP_H__

using namespace std;

/* ʹ�ö���ͳ��ÿ��Ԫ�����³���ʱ����������Ǹ�
 * ����������򵯳�������ֵ��Ǹ��������µ�Ԫ�أ������µ�ǰ�Ӵ�����Ϣ
 */
class heap
{
private:
	const int capacity;		//������󳤶�
	int top;				//�Ѵ�Сָ��
	map<char, int> elem;	//��ŵ�ǰ����
	vector<int> buffer;		//Ϊ��Ѹ���ҳ���Сֵ��һ�����������elem�е�keyֵ

	//�Ѷ�Ԫ��
	inline int peak()
	{
		if (top < 1)
			return -1;

		return elem[buffer[top]];
	}

	//�ȽϺ���
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

	//�Ϸ�
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
		//��buffer[1] ��ʼ�洢
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

	//pushʱ���������δ������ֱ�Ӽ��봰�ڣ�����������ˣ��򵯳��Ѷ�
	int push(char keynum, int valnum)
	{
		//�����push��Ԫ��Ϊ�Ӵ����ظ����ֵ�Ԫ��
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
			return -1;	//��һ�䲻��ִ�У���Ϊ�����map���ҵ���Ԫ�أ������һ�����ڡ�д���Ϊ����warning
		}

		//��Ԫ�����Ӵ��е�һ�γ��֣�����ǰ����δ��
		if (top < capacity)
		{
			elem[keynum] = valnum;
			buffer[++top] = keynum;
			rollUp(top);
			return -1;
		}

		//��Ԫ��Ϊ��һ�γ���Ԫ�أ��ҵ�ǰ�����Ѿ�����
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
