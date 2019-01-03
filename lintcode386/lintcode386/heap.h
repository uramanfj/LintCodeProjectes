#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef __HEAP_H__
#define __HEAP_H__

using namespace std;

/*��¼ÿ��Ԫ�����³���ʱ��*/
typedef pair<char, int> ELEM;

/* ʹ�ö���ͳ��ÿ��Ԫ�����³���ʱ����������Ǹ�
 * ����������򵯳�������ֵ��Ǹ��������µ�Ԫ�أ������µ�ǰ�Ӵ�����Ϣ
 */
class heap
{
private:
	const int capacity;	//������󳤶�
	int top;			//�Ѵ�Сָ��
	vector<ELEM> buffer;

	//�Ѷ�Ԫ��
	ELEM& peak()
	{
		if (top < 1)
			return buffer[0];

		return buffer[top];
	}

	//�ȽϺ���
	inline bool cmp(int num1, int num2)
	{
		return (buffer[num1].second < buffer[num2].second);
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
		//��buffer[1] ��ʼ�洢
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

	//pushʱ���������δ������ֱ�Ӽ��봰�ڣ�����������ˣ��򵯳��Ѷ�
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
