/**	@file DiagnosisMain.cpp
	@author Jimin Park
	@date 2019-12-06

	1. Diagnosis of Breast Cancer using Decision Tree Data Mining Technique
		- By create binaryTree, determine diagnosis which is Benign(2) or Malignant(4) 
	2. Correlation of Risk Factors with Cancer Diagnosis
		- By create Graph, matrix showing the relationships and their weights using the weights for each Edge as the data.
*/
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BinaryTree.hpp"
#include "WisconsinNode.hpp"
#include "RiskFactors.hpp"
#include "Graph.hpp"

using namespace std;

void readCSVFile(BinaryTree* tree, vector<WisconsinNode*>& attributesV);
void readCSVRiskFactor(vector<RiskFactors*>& riskFactorV);

/*!	 \fn readCSVFile
	 \return none
	 \param BinaryTree* tree, vector<WisconsinNode*>& attributesV 

	 attributeV - Vector of all the data from wisconsin data.csv */
void readCSVFile(BinaryTree* tree, vector<WisconsinNode*>& attributesV) {

	ifstream ip("wisconsin data.csv");

	if (!ip.is_open()) cout << "Error: File Open" << endl;

	string id;
	string clumpThickness;
	string uniformityOfCellSize;
	string uniformityOfCellShape;
	string marginalAdhesion;
	string singleEpitheialCellSize;
	string bareNuclei;
	string blandChromatin;
	string normalNucleoli;
	string miroses;
	string bOrMClass;

	while (getline(ip, id, ',')) {
		getline(ip, clumpThickness, ',');
		getline(ip, uniformityOfCellSize, ',');
		getline(ip, uniformityOfCellShape, ',');
		getline(ip, marginalAdhesion, ',');
		getline(ip, singleEpitheialCellSize, ',');
		getline(ip, bareNuclei, ',');
		getline(ip, blandChromatin, ',');
		getline(ip, normalNucleoli, ',');
		getline(ip, miroses, ',');
		getline(ip, bOrMClass, '\n');

		WisconsinNode* att = new WisconsinNode(); // wisconsin breast cancer dataset attribute

		if (bareNuclei == "?") { // exception if the value is '?'
			bareNuclei = "1";
		}

		// All the string convert to int
		att->id_ = stoi(id);
		att->clumpThickness_ = stoi(clumpThickness);
		att->uniformityOfCellSize_ = stoi(uniformityOfCellSize);
		att->uniformityOfCellShape_ = stoi(uniformityOfCellShape);
		att->marginalAdhesion_ = stoi(marginalAdhesion);
		att->singleEpitheialCellSize_ = stoi(singleEpitheialCellSize);
		att->bareNuclei_ = stoi(bareNuclei);
		att->blandChromatin_ = stoi(blandChromatin);
		att->normalNucleoli_ = stoi(normalNucleoli);
		att->miroses_ = stoi(miroses);
		att->class_ = stoi(bOrMClass);

		// execute binaryTree to determine diagnosis
		att = tree->generatedTree(att);
		
		// push dataset attribute with diagnosis
		attributesV.push_back(att);
	}

	ip.close();
}

/*!	 \fn readCSVRiskFactor
	 \return none
	 \param vector<RiskFactors*>& riskFactorV

	 riskFactorV - Vector of all the data from risk factor data data.csv 
	 Dimensionality in statistics refers to how many attributes a dataset has.
	 Find the correlation between incidences of malignant or benign cancer diagnosis and associated risk factors. */
void readCSVRiskFactor(vector<RiskFactors*>& riskFactorV) {

	ifstream ip("risk factor data.csv");

	if (!ip.is_open()) cout << "Error: File Open" << endl;

	string id;
	string gender;
	string age;
	string genericFactor;
	string familyHistory;
	string overweight;
	string alcoholic;
	string smoking;
	string hormone;

	while (getline(ip, id, ',')) {
		getline(ip, gender, ',');
		getline(ip, age, ',');
		getline(ip, genericFactor, ',');
		getline(ip, familyHistory, ',');
		getline(ip, overweight, ',');
		getline(ip, alcoholic, ',');
		getline(ip, smoking, ',');
		getline(ip, hormone, '\n');

		RiskFactors* fators = new RiskFactors(); // all the Risk Factors

		// id_ the string convert to int, and all the string conver to bool
		fators->id_ = stoi(id);
		fators->factorVec[0] = (gender == "T") ? true : false;
		fators->factorVec[1] = (age == "T") ? true : false;
		fators->factorVec[2] = (genericFactor == "T") ? true : false;
		fators->factorVec[3] = (familyHistory == "T") ? true : false;
		fators->factorVec[4] = (overweight == "T") ? true : false;
		fators->factorVec[5] = (alcoholic == "T") ? true : false;
		fators->factorVec[6] = (smoking == "T") ? true : false;
		fators->factorVec[7] = (hormone == "T") ? true : false;

		riskFactorV.push_back(fators);
	}
	ip.close();
}

int main() {

#if defined(_DEBUG)
	// gets the state of the debug flags
	int dbgFlags = ::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	// bitwise or - check block integrity on every memory call
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	// don't always remove the blocks on delete
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	// check for memory leaks at process termination
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
	// modifies the state of the debug flags
	_CrtSetDbgFlag(dbgFlags);
#endif

	/* Part A */
	vector<WisconsinNode*> attributesV;
	BinaryTree* tree = new BinaryTree();

	readCSVFile(tree, attributesV);
	tree->writeCSVWithDiagnosis(attributesV);

	// A summary of the total amount of patients with malignant and benign tumors 
	// in the format shown below output to console
	int cntMalignant = 0;
	int cntBenign = 0;
	for (auto a : attributesV) {
		if (a->class_ == 2) {
			cntBenign++;
		}
		else if (a->class_ == 4) {
			cntMalignant++;
		}
	}

	cout << "Benign: " << cntBenign << endl;
	cout << "Malignant: " << cntMalignant << endl;
	cout << "Total Patients: " << cntMalignant + cntBenign << endl;

	/* Part A */
	vector<RiskFactors*> riskFactorV;
	readCSVRiskFactor(riskFactorV);

	Graph* graphMalignant = new Graph(4); // 4 - Malignant 
	graphMalignant->addNode(attributesV, riskFactorV);
	graphMalignant->printGraph();
	graphMalignant->saveFileGraph();

	Graph* graphBenign = new Graph(2); // 2 - Benign
	graphBenign->addNode(attributesV, riskFactorV);
	graphBenign->printGraph(); 
	graphBenign->saveFileGraph(); 

	// Delete all the node to prevent memory leak.
	graphMalignant->deleteNode();
	graphBenign->deleteNode();

	for (size_t i = 0; i < riskFactorV.size(); i++) {
		delete riskFactorV[i];
	}

	tree->deleteAllNode(attributesV);

	delete tree;
	delete graphMalignant;
	delete graphBenign;

	_CrtSetDbgFlag(dbgFlags);

	return 0;
}
