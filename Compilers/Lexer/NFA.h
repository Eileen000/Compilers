#include<bits/stdc++.h>
#ifndef NFA_H
#define NFA_H
using namespace std;


class NFA_STATE{
		
	public:
		string name;
		bool is_end_state;
		//string:������ַ�  int:NFA�����е�״̬�±� 
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
		const NFA_STATE_UNIT move(NFA_STATE_UNIT now,string name);//״̬���ϵ������ַ�ת�� 
		const NFA_STATE_UNIT closure(NFA_STATE_UNIT stateSet);//״̬���ϵıհ� 
		vector<string> calculateInput();  //�������ַ����� 
		void showUnit();
		
};

#endif
