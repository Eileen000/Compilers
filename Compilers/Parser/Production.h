#include <bits/stdc++.h>
#ifndef PRODUCTION_H
#define PRODUCTION_H
using namespace std;

class Production{
	public:
		vector<string> unit;
	
	public:
		void showUnit();
		void init(char path[]);
		void buildPro(char path[]);
		vector<string> findProduction(char c);
		int findProIndex(string s);
		int findPre(int index);
	
};

//Production proUnit;

#endif
