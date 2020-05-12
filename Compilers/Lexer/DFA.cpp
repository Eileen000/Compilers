#include<bits/stdc++.h>
#include "DFA.h"
using namespace std;


DFA_STATE DFA::NFA_TO_DFA(NFA_STATE_UNIT stateSet)
{
	DFA_STATE dfa_state;
	for(int i=0;i<stateSet.size();i++)
		dfa_state.stateUnit.push_back(stateSet[i]);
	return dfa_state;
}

bool DFA::equalTo(DFA_STATE s1,DFA_STATE s2)
{
	
	if(s1.stateUnit.size()!=s2.stateUnit.size())
		return false;
	for(int i=0;i<s1.stateUnit.size();i++)
	{
		bool flag = false;
		for(int j=0;j<s2.stateUnit.size();j++)
			if(s1.stateUnit[i].name == s2.stateUnit[j].name)
			{
				flag = true;
				break;
			}			
		if(flag == false)
			return false;
	}
	return true;
}
bool DFA::isNewState(DFA_STATE_UNIT dfa_state_unit,DFA_STATE dfa_state)
{
	for(int i=0;i<dfa_state_unit.size();i++)
	{
		if(equalTo(dfa_state,dfa_state_unit[i]))
			return false;
	}
	return true;
}

int DFA::findPosition(DFA_STATE_UNIT dfa_state_unit,DFA_STATE dfa_state)
{
	for(int i=0;i<dfa_state_unit.size();i++)
	{
		if(equalTo(dfa_state,dfa_state_unit[i]) == true)
			return i;
	}
	return -1;
}

bool DFA::remainNewState(DFA_STATE_UNIT state_unit)
{
	for(int i=0;i<state_unit.size();i++)
		if(state_unit[i].is_a_new_state == true)
			return true;
	return false;
}

bool DFA::isEnd(DFA_STATE dfa_state)
{
	for(int i=0;i<dfa_state.stateUnit.size();i++)
		if(dfa_state.stateUnit[i].is_end_state == true)
			return true;
	return false;
}

void DFA::buildDFA(NFA nfa)
{
	
	NFA_STATE_UNIT nfa_begin;
	nfa_begin.push_back(nfa.getStart());       
	
	//创建  T0   dfa_state_unit 存放的是每个DFA状态 Ti 
	//DFA_STATE_UNIT dfa_state_unit;
	//放入状态T0 
	DFA_STATE dfa_begin = NFA_TO_DFA(nfa_begin);
	
	dfa_state_unit.push_back(dfa_begin);
			
	bool keepRun = true;//是否有未标记状态，有则keepRun为true 
	vector<string> eachInput = nfa.calculateInput(); //输入字符集合 
		
	for(int i=0;i<dfa_state_unit.size()&&keepRun == true;i++)  
	{
		
		NFA_STATE_UNIT Ti = dfa_state_unit[i].stateUnit;//对 C 中的每个 Ti 
		
		dfa_state_unit[i].is_a_new_state = false; //标记Ti 
		
			
		for(int j=0;j<eachInput.size();j++)       //对每个输入字符
		{
			int index = -1;		
			
			NFA_STATE_UNIT move_unit = nfa.move(Ti,eachInput[j]);   //move (Ti,a)
			
			NFA_STATE_UNIT closure_unit = nfa.closure(move_unit);  //e-closure(move())
			
			if(closure_unit.size()==0)
			{
				continue;
			}
			
			DFA_STATE new_dfa_state;
			new_dfa_state.stateUnit = closure_unit;
			new_dfa_state.is_end_state = isEnd(new_dfa_state);  //是否是终态 
			
			if(isNewState(dfa_state_unit,new_dfa_state) == true)
			{
				dfa_state_unit.push_back(new_dfa_state);
			}
			
			index = findPosition(dfa_state_unit,new_dfa_state);
			
			if(index!=-1)
				dfa_state_unit[i].production[eachInput[j]] = index;  //当前Ti 对输入字符 映射到的 状态 
			
		}
		
		if(remainNewState(dfa_state_unit)  == true)  //还有未标记状态 
			keepRun = true;
		else
			keepRun = false;
	}
	cout<<"Finish DFA Build"<<endl;
}

void DFA::showProduction()
{
	ofstream output;
	output.open("C:\\Users\\Eileen\\Compilers\\Lexer\\production.txt");
	output<<dfa_state_unit.size()<<endl;
	for(int i=0;i<dfa_state_unit.size();i++)
	{
		output<<i<<endl;
		map<string,int>::iterator it;
		for(it = dfa_state_unit[i].production.begin();it!=dfa_state_unit[i].production.end();it++)
			output<<it->first<<"  "<<it->second<<endl;
	}
	output.close();
}
int DFA::isLegal(string word)
{
	
	int now = 0;
	bool flag;
	
	for(int i=0;i<word.length();i++)
	{
		flag = false;
		map<string,int>::iterator it;
		
		for(it = dfa_state_unit[now].production.begin();it!=dfa_state_unit[now].production.end();it++)
		{
			string face = it->first;
			string tmp;
			if(face.length()>1)
				continue;
			else
				tmp = it->first;
			if(word[i] == tmp[0])
			{
				now = it->second;
				flag = true;
				break;  //没有这个break就会造成死循环 
			}	
		}
		
		
		if(flag == false)
			break;
	}
	
	if(flag==false)
	{
		map<string,int>::iterator it;
		for(it = dfa_state_unit[0].production.begin();it!=dfa_state_unit[0].production.end();it++)
		{
			string face = it->first;
			char tmp;
			if(face.length()>1&&face==word)
			{
				flag = true;
				now = it->second;
				break;
			}
		}
	}
	
	if(dfa_state_unit[now].is_end_state == true&&flag==true)//if(now<dfa_state_unit.size()-1)
		return now;
	else
		return -1;
	
}

void DFA::showUnit(DFA_STATE_UNIT dfa_state_unit)
{
	ofstream output;
	output.open("C:\\Users\\Eileen\\Compilers\\Lexer\\dfaUnit.txt");
	output<<"DFA state unit is : ";
	for(int i=0;i<dfa_state_unit.size();i++)
	{
		for(int j=0;j<dfa_state_unit[i].stateUnit.size();j++)
			output<<dfa_state_unit[i].stateUnit[j].name<<"  ";
		output<<endl;
	}
		
	output<<endl;
	output.close();
} 


void DFA::makeRules()
{
	for(int i=0;i<dfa_state_unit.size();i++)
	{
		string tmp = dfa_state_unit[i].stateUnit[0].name;
		if(tmp=="integer"||tmp=="double")
			tmp = "constant"; 	
		rules[i] = make_pair(i,tmp);

	}
}

