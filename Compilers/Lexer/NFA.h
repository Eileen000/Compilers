#include<bits/stdc++.h>
#ifndef NFA_H
#define NFA_H
using namespace std;


class NFA_STATE{
		
	public:
		string name;
		bool is_end_state;
		//string:输入的字符  int:NFA集合中的状态下标 
		vector< pair<string,int> > nextState;
		
		NFA_STATE()
		{
			is_end_state = false;
		}
};

typedef vector<NFA_STATE> NFA_STATE_UNIT;


class NFA{ 
	
	private	:
		NFA_STATE_UNIT stateUnit;
		
	public:
		bool notExit(string name);
		
		int getPosition(string name);
			
		int createState(string name);
		
		void buildNFA(char txtPath[]);
	
		void showNFA();
		const NFA_STATE getStart();
		NFA_STATE_UNIT findNextState(NFA_STATE nowState,string name);
		const NFA_STATE_UNIT move(NFA_STATE_UNIT now,string name);//状态集合的输入字符转换 
		const NFA_STATE_UNIT closure(NFA_STATE_UNIT stateSet);//状态集合的闭包 
		vector<string> calculateInput();  //求输入字符集合 
		void showUnit();
		
};

#endif
