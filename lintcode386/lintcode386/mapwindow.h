#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef __MAPWINDOW_H__
#define __MAPWINDOW_H__

using namespace std;

class mapwindow 
{
private:
	string& s;
	int capacity;
	map<int, char> buffer;

public:
	mapwindow(string &str, int k = 1) : s(str), capacity(k) {}

	int push(int index)
	{
		//��Ҫ����һ����Ԫ��ʱ�������Ԫ�ز��ǵ�һ�γ��֣������buffer�е���Ϣ��
		for (auto elem : buffer)
		{
			if (elem.second == s[index])
			{
				buffer.erase(elem.first);
				buffer[index] = s[index];
				return -1;
			}
		}

		//��Ԫ�أ�����δ��
		if (buffer.size() < capacity)
		{
			buffer[index] = s[index];
			return -1;
		}

		//�����Ѿ�����,��Ҫɾ��������ֵ�Ԫ��
		int ret = buffer.begin()->first;
		buffer.erase(buffer.begin());
		buffer[index] = s[index];
		return ret;
	}
};

#endif //__MAPWINDOW_H__
//End of File