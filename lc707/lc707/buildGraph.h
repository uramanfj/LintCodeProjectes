#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

#ifndef __BUILDGRAPH_H__
#define __BUILDGRAPH_H__

class buildGraph
{
private:
	/*	���ݽṹ�� 
	 *  ��map��vertexDegrees���洢ÿ������Ķȣ�Ϊ�˱��ⶥ���1000~1002�����ֿӵ�������˴���ʹ��vector<int>(maxVertexIndex)
	 *	��vector: nonZeroIndexes���洢��ǰȨֵ��Ϊ0�Ľڵ㣺1.Ϊ�˱���ɾ��map�ڵ�ʱ��ɷ�����������2.Ϊ�����Ч�ʣ����� ��ɾmap�ڵ�Ŀ���
	 */
	map<int, int> vertexDegrees;	//key Ϊ�����ţ� val Ϊ�ö����Ȩֵ
	vector<int> nonZeroIndexes;		//��¼���з�0�ڵ㣬�൱��map������
	int nonZeroCount;				//��¼��ǰ��0�ڵ����

public:
	buildGraph(vector<vector<int>> &clues) :nonZeroCount(0) 
	{
		//¼��ÿ������ĳ��ȡ���������ȼ�Ϊ+����ȼ�Ϊ-
		for (auto elem : clues)
		{
			vertexDegrees[elem[0]] += elem[2];
			vertexDegrees[elem[1]] -= elem[2];
		}

		//�����еķǿսڵ��¼��vector��
		for (auto it = vertexDegrees.begin(); it != vertexDegrees.end(); it++)
		{
			if (it->second != 0)
			{
				nonZeroIndexes.push_back(it->first);
				nonZeroCount++;
			}
		}

		return;
	}
	~buildGraph() {}

	//����start�������һλ��ƽ�ⶥ�㣬��û�ҵ��򷵻�-1
	int findNextNonZero(int start)
	{
		for (int i = start + 1; i < nonZeroIndexes.size(); i++)
		{
			if (nonZeroIndexes[i] != -1)
			{
				return i;
			}
		}
		return -1;
	}

	int balanceGraph(int startIndex = 0)
	{
		switch (nonZeroCount)
		{
		case 0:			//�������ȨֵΪ�գ������ͼ��������ƽ���
			return 0;
		case 2:			//�����������㲻ƽ�⣬��Ϊϵͳ������������ƽ��ģ�����ֻ��һ��ƥ��
			return 1;
		case 3:			//�����������㲻ƽ�⣬��ض�ƥ��2�Σ��ɴﵽƽ��
			return 2;
		}

		//���еĲ�ƽ�ⶥ�㶼���ʹ��ˣ����ߵ�ǰ��ʼ�����Ѿ�ƽ�⣬�򷵻�
		if ((startIndex < 0) || (startIndex >= nonZeroIndexes.size()) || (nonZeroIndexes[startIndex] == -1)) 
		{
			return 0;
		}

		//����������жϣ�vertexDegrees��������4��Ԫ�أ��ҵ�һ�����㲻ƽ�⣻
		int minMove = INT_MAX;

		//���ǰ����ֱ��ƽ����ˣ���ô��Ѱ����һ����ƽ��ĵ㣻����ƽ�������Ч��
		int nextIndex = findNextNonZero(startIndex);
		if ((vertexDegrees[nonZeroIndexes[startIndex]] == -1 * vertexDegrees[nonZeroIndexes[nextIndex]]))
		{
			nextIndex = findNextNonZero(nextIndex);
			nonZeroCount -= 2;
			int count = balanceGraph(nextIndex) + 1;
			nonZeroCount += 2;
			return count;
		}
		
		//DP
		for (int i = nextIndex; i < nonZeroIndexes.size(); i++)
		{
			//����ƽ�ⶥ��
			if (nonZeroIndexes[i] == -1)
			{
				continue;
			}
			
			//����һ��Ԫ�ص�ֵ�ӵ� i��
			vertexDegrees[nonZeroIndexes[i]] += vertexDegrees[nonZeroIndexes[startIndex]];
			if (vertexDegrees[nonZeroIndexes[i]] == 0)
			{
				//�պ�ƽ��
				nonZeroCount -= 2;
				int count = balanceGraph(findNextNonZero(i)) + 1;
				//�ָ��ֳ�
				nonZeroCount += 2;
				vertexDegrees[nonZeroIndexes[i]] -= vertexDegrees[nonZeroIndexes[startIndex]];
				return count;
			}
			else
			{
				nonZeroCount -= 1;
				int count = balanceGraph(nextIndex) + 1;
				nonZeroCount += 1;
				vertexDegrees[nonZeroIndexes[i]] -= vertexDegrees[nonZeroIndexes[startIndex]];

				minMove = (minMove < count) ? minMove : count;
			}
		}//end of for
		return minMove;
	}
};

#endif // !__BUILDGRAPH_H__
//End of File



//A���ŵ����º���