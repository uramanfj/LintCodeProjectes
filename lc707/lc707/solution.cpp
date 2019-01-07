#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "buildGraph.h"

using namespace std;

class Solution {
public:
	/*
	 * @param edges: a directed graph where each edge is represented by a tuple
	 * @return: the number of edges
	 */
	int balanceGraph(vector<vector<int>> &edges) {
		buildGraph bg(edges);

		return bg.balanceGraph();
	}
};