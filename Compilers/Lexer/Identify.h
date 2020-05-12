#include<bits/stdc++.h>
#include "File.h"
#include "NFA.h"
#include "DFA.h"
#ifndef IDENTIFY_H
#define IDENTIFY_H
using namespace std;
class Token{
	public:
		
	int row_number;//行号 
	string sort;//种类 
	string word;//内容 
	 
	public:
		Token(){
			row_number = 0;
		}
	 
};

typedef pair<string,int> status;

class Identify{
	
	public:
		vector<Token> result;  //token表 
			
	public:
		
		void markFile();
		void createToken(DFA dfa);
	
};


#endif
