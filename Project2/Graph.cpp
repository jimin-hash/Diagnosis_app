/**	@file Graph.cpp
	@author Jimin Park
	@date 2019-12-06

	Implement for Graph.hpp
*/
#include "Graph.hpp"

Graph::~Graph() {
}

/*!	 Constructor
	 \return none
	 \param none  */
Graph::Graph(int type) {
	this->Diagnotype_ = type; // 2 - Benign , 4 - Malignant 

	matrixV.resize(8);

	//initialize the matrix vector
	for (size_t i = 0; i < matrixV.size(); i++) {
		matrixV[i].resize(8);
		for (size_t j = 0; j < matrixV[i].size(); j++) {
			matrixV[i][j] = 0;
		}
	}
}

/*!	 \fn deleteNode
	 \return none
	 \param none

	  Delete all the node from Graph */
void Graph::deleteNode() {
	for (size_t i = 0; i < nodeV.size(); i++) {
		delete nodeV[i]->next_;
		delete nodeV[i];
	}
	matrixV.clear();
}

/*!	 \fn addNode
	 \return none
	 \param none

	  Add all the node */
void Graph::addNode(vector<WisconsinNode*> const& w, vector<RiskFactors*>  const& r) {
	this->wisV = w;
	this->factorsV = r;

	addEdge(0,1); // gender, age
	addEdge(0,2); // gender, deneric factor
	addEdge(0,3); // gender, family history
	addEdge(0,4); // gender, overwight
	addEdge(0,5); // gender, alcoholic
	addEdge(0,6); // gender, smoking
	addEdge(0,7); // gender, hormone

	addEdge(1,2); // age, generic
	addEdge(1,3); // age, family history
	addEdge(1,4); // age, overwight
	addEdge(1,5); // age, alcoholic
	addEdge(1,6); // age, smoking
	addEdge(1,7); // age, hormone
	
	addEdge(2,3); // generic, family history
	addEdge(2,4); // generic, overweighr
	addEdge(2,5); // generic, alcoholic
	addEdge(2,6); // generic, smoking
	addEdge(2,7); // generic, hormone
	
	addEdge(3,4); // fmaily, overwight
	addEdge(3,5); // fmaily, alcoholic
	addEdge(3,6); // fmaily, smoking
	addEdge(3,7); // fmaily, hormone

	addEdge(4,5); // overweight, alcoholic
	addEdge(4,6); // overweight, smoking
	addEdge(4,7); // overweight, hormone

	addEdge(5,6); // alcoholic, smoking
	addEdge(5,7); // alcoholic, hormone

	addEdge(6,7); // smoking, hormone
}

/*!	 \fn addEdge
	 \return none
	 \param int src, int dest

	 Adding the edge in an undirectional graph  */
void Graph::addEdge(int src, int dest) {
	Node* newNode = new Node(dest);
	Node* newNode1 = new Node(src);

	newNode->next_ = newNode1;
	newNode1->next_ = newNode;

	nodeV.push_back(newNode);

	// wisV - Vector of all the data from wisconsin data.csv
	for (size_t wIndex = 0; wIndex < wisV.size(); wIndex++) {
		if (wisV[wIndex]->class_ == Diagnotype_) { // 2 - Benign , 4 - Malignant 
			if (factorsV[wIndex]->factorVec[src] == true && factorsV[wIndex]->factorVec[dest] == true) {
				matrixV[src][dest] = ++newNode->cntEdge_; //matrixV[src][dest];
				matrixV[dest][src] = ++newNode1->cntEdge_; //matrixV[dest][src];
			}
		}
	}
}

/*!	 \fn printGraph
	 \return none
	 \param none

	  Print formatted matrix */
void Graph::printGraph() {
	cout << endl;
	string catagoryName[8] = { "Gender","Age","GenericFactor","FamilyHistory","Overweight","Alcoholic","Smoking","HRT" };

	if (Diagnotype_ == 2)
		cout << right << "*** Benign ***" << endl;
	else 
		cout << right << "*** Malignant ***" << endl;

	
	for (int i = 0; i < sizeof(catagoryName) / sizeof(catagoryName[0]); i++) {
		if (i == 0)
			cout << setw(27);
		
		cout << catagoryName[i];
		if (i == 1)
			cout << '\t';
		else
			cout << setw(10 + (catagoryName[i].length()));
		
	}
	cout << endl;

	for (size_t i = 0; i < matrixV.size(); i++) {
		if (i == 0)
			cout << setw(10);
		cout << right << catagoryName[i] << setw(10);
		for (size_t j = 0; j < matrixV[i].size(); j++) {
			if (j == 0 || j == 1) {
				cout << '\t' << matrixV[i][j] << setw(10);
			}
			else if (j == 2){
				cout << '\t';
				cout << setw(5) << matrixV[i][j] << setw(10);
			}
			else if(j == 3) {
				cout << '\t';
				cout << setw(12) << matrixV[i][j] << setw(10);
			}
			else if (j == 4) {
				cout << '\t';
				cout << setw(11) << matrixV[i][j] << setw(10);
			}
			else if (j == 5) {
				cout << '\t';
				cout << setw(8) << matrixV[i][j] << setw(10);
			}
			else {
				cout << '\t';
				cout << matrixV[i][j] << setw(10);
			}
		}
		cout << endl;
	}
}

/*!	 \fn saveFileGraph
	 \return none
	 \param none

	  output in csv format */
void Graph::saveFileGraph() {
	ofstream op;

	if (Diagnotype_ == 2)
		op.open("adjmatrixBenign.txt");
	else
		op.open("adjmatrixMalignant.txt");

	if (!op.is_open()) cout << "Error: File Open" << endl;

	for (size_t i = 0; i < matrixV.size(); i++) {
		for (size_t j = 0; j < matrixV[i].size(); j++) {
			if (j != 7)
				op << matrixV[i][j] << ",";
			else
				op << matrixV[i][j];
		}
		op << "\n";
	}
	op.close();
}