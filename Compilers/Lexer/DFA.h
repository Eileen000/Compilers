#include<bits/stdc++.h>
#include "NFA.h"
#ifndef DFA_H
#define DFA_H
using namespace std;

typedef map<string,int> STATE_TRANSFOR; //DFA��ȷ���� map����һ��һ 

 
class DFA_STATE{
	
	public:
		
		NFA_STATE_UNIT stateUnit;
		bool is_end_state;   //��̬ 
		bool is_a_new_state; //δ���״̬ 
		STATE_TRANSFOR production;
	
	DFA_STATE()
	{
		is_end_state = false;
		is_a_new_state = true;
	}
};

typedef vector<DFA_STATE> DFA_STATE_UNIT; //DFA״̬���� 
typedef pair<int,string> Rules;//token 

class DFA{
	
	public:
		
		DFA_STATE_UNIT dfa_state_unit;
		Rules rules[1000];
		
	public:
		
		DFA_STATE NFA_TO_DFA(NFA_STATE_UNIT stateSet);//��NFA��״̬���Ϸ���һ��DFA״̬�� 
		void buildDFA(NFA nfa);//�Ӽ�������DFA 
		bool isNewState(DFA_STATE_UNIT dfa_state_unit,DFA_STATE dfa_state);
		bool remainNewState(DFA_STATE_UNIT dfa_state_unit);
		
		bool showDFA();
		bool equalTo(DFA_STATE s1,DFA_STATE s2);
		int findPosition(DFA_STATE_UNIT dfa_state_unit,DFA_STATE dfa_state);
		
		bool isEnd(DFA_STATE dfa_state);
		int isLegal(string word);//�жϵ����Ƿ�Ϸ� 
		
		void showProduction();
		void showUnit(DFA_STATE_UNIT dfa_state_unit);
		
		void makeRules();
		
		
};



#endif
