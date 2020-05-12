#include<bits/stdc++.h>
#include "NFA.h"
#ifndef DFA_H
#define DFA_H
using namespace std;

typedef map<string,int> STATE_TRANSFOR; //DFA的确定性 map性质一对一 

 
class DFA_STATE{
	
	public:
		
		NFA_STATE_UNIT stateUnit;
		bool is_end_state;   //终态 
		bool is_a_new_state; //未标记状态 
		STATE_TRANSFOR production;
	
	DFA_STATE()
	{
		is_end_state = false;
		is_a_new_state = true;
	}
};

typedef vector<DFA_STATE> DFA_STATE_UNIT; //DFA状态集合 
typedef pair<int,string> Rules;//token 

class DFA{
	
	public:
		
		DFA_STATE_UNIT dfa_state_unit;
		Rules rules[1000];
		
	public:
		
		DFA_STATE NFA_TO_DFA(NFA_STATE_UNIT stateSet);//将NFA的状态集合放入一个DFA状态中 
		void buildDFA(NFA nfa);//子集法构造DFA 
		bool isNewState(DFA_STATE_UNIT dfa_state_unit,DFA_STATE dfa_state);
		bool remainNewState(DFA_STATE_UNIT dfa_state_unit);
		
		bool showDFA();
		bool equalTo(DFA_STATE s1,DFA_STATE s2);
		int findPosition(DFA_STATE_UNIT dfa_state_unit,DFA_STATE dfa_state);
		
		bool isEnd(DFA_STATE dfa_state);
		int isLegal(string word);//判断单词是否合法 
		
		void showProduction();
		void showUnit(DFA_STATE_UNIT dfa_state_unit);
		
		void makeRules();
		
		
};



#endif
