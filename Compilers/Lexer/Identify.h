#include<bits/stdc++.h>
#include "File.h"
#include "NFA.h"
#include "DFA.h"
#ifndef IDENTIFY_H
#define IDENTIFY_H
using namespace std;
class Token{
	public:
		
	int row_number;//�к� 
	string sort;//���� 
	string word;//���� 
	 
	public:
		Token(){
			row_number = 0;
		}
	 
};

typedef pair<string,int> status;

class Identify{
	
	public:
		vector<Token> result;  //token�� 
			
	public:
		
		void markFile();
		void createToken(DFA dfa);
	
};


#endif
