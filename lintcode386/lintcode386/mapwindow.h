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
		//当要加入一个新元素时，如果该元素不是第一次出现，则更新buffer中的信息，
		for (auto elem : buffer)
		{
			if (elem.second == s[index])
			{
				buffer.erase(elem.first);
				buffer[index] = s[index];
				return -1;
			}
		}

		//新元素，窗口未满
		if (buffer.size() < capacity)
		{
			buffer[index] = s[index];
			return -1;
		}

		//窗口已经满了,则要删除最早出现的元素
		int ret = buffer.begin()->first;
		buffer.erase(buffer.begin());
		buffer[index] = s[index];
		return ret;
	}
};

#endif //__MAPWINDOW_H__
//End of File