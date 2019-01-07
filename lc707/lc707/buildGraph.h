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
	/*	数据结构： 
	 *  用map：vertexDegrees来存储每个顶点的度：为了避免顶点从1000~1002，这种坑爹情况，此处不使用vector<int>(maxVertexIndex)
	 *	用vector: nonZeroIndexes来存储当前权值不为0的节点：1.为了避免删除map节点时造成废弃迭代器，2.为了提高效率，减少 增删map节点的开销
	 */
	map<int, int> vertexDegrees;	//key 为顶点编号， val 为该顶点的权值
	vector<int> nonZeroIndexes;		//记录所有非0节点，相当于map的索引
	int nonZeroCount;				//记录当前非0节点个数

public:
	buildGraph(vector<vector<int>> &clues) :nonZeroCount(0) 
	{
		//录入每个顶点的出度、入读，出度记为+，入度记为-
		for (auto elem : clues)
		{
			vertexDegrees[elem[0]] += elem[2];
			vertexDegrees[elem[1]] -= elem[2];
		}

		//将所有的非空节点记录在vector中
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

	//查找start后面的下一位不平衡顶点，如没找到则返回-1
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
		case 0:			//如果顶点权值为空，则这个图本来就是平衡的
			return 0;
		case 2:			//若有两个顶点不平衡，因为系统本来就是整体平衡的，所以只需一次匹配
			return 1;
		case 3:			//若有三个顶点不平衡，则必定匹配2次，可达到平衡
			return 2;
		}

		//所有的不平衡顶点都访问过了，或者当前开始顶点已经平衡，则返回
		if ((startIndex < 0) || (startIndex >= nonZeroIndexes.size()) || (nonZeroIndexes[startIndex] == -1)) 
		{
			return 0;
		}

		//经过上面的判断，vertexDegrees里至少有4个元素，且第一个顶点不平衡；
		int minMove = INT_MAX;

		//如果前两个直接平衡掉了，那么就寻找下一个不平衡的点；两两平衡是最高效的
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
			//遇到平衡顶点
			if (nonZeroIndexes[i] == -1)
			{
				continue;
			}
			
			//将第一个元素的值加到 i上
			vertexDegrees[nonZeroIndexes[i]] += vertexDegrees[nonZeroIndexes[startIndex]];
			if (vertexDegrees[nonZeroIndexes[i]] == 0)
			{
				//刚好平衡
				nonZeroCount -= 2;
				int count = balanceGraph(findNextNonZero(i)) + 1;
				//恢复现场
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



//A级优等生下海记