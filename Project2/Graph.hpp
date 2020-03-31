/**	@file Graph.cpp
	@author Jimin Park
	@date 2019-12-06
*/
#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "WisconsinNode.hpp"
#include "RiskFactors.hpp"
#include "Node.hpp"

using namespace std;

class Graph
{
public:
	int Diagnotype_;
	Graph(int type);
	~Graph();

	vector<WisconsinNode*> wisV;
	vector<RiskFactors*> factorsV;
	vector< vector<int> > matrixV;
	vector<Node*> nodeV;

	void addNode(vector<WisconsinNode*> const& , vector<RiskFactors*>  const& );
	void addEdge(int src, int dest);
	void deleteNode();
	void printGraph();
	void saveFileGraph();
};

