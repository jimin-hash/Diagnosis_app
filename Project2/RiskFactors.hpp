/**	@file RickFactor.cpp
	@author Jimin Park
	@date 2019-12-06
*/

#pragma once
#include <string>
#include <vector>

using namespace std;

class RiskFactors {
public:
	int id_ = 0; // id
	vector<bool> factorVec;
	// bool gender_;		- factorVec[0]	
	// bool age_;			- factorVec[1]	
	// bool genericFactor_;	- factorVec[2]
	// bool familyHistory_;	- factorVec[3]
	// bool overweight_;	- factorVec[4]
	// bool alcoholic_;		- factorVec[5]
	// bool smoking_;		- factorVec[6]
	// bool hormone_;		- factorVec[7]
	
	//constructor
	RiskFactors();
};
