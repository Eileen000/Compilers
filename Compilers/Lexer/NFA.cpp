#include <windows.h>
#include "NFA.h"

using namespace std;

NFA_STATE_UNIT NFA::findNextState(NFA_STATE nowState,string name)
{
	NFA_STATE_UNIT result;
	
	for(int j=0;j<nowState.nextState.size();j++)
	{
		if(name==nowState.nextState[j].first)
		{
			int index = nowState.nextState[j].second;
			result.push_back(stateUnit[index]);
		}
	}
				
	return result;
}

bool NFA::notExit(string name)
{
	for(int i=0;i<stateUnit.size();i++)
		if(name==stateUnit[i].name)
			return false;
	return true;
}

int NFA::getPosition(string name)     //根据状态名字 返回它在stateUnit中的下标 
{
	for(int i=0;i<stateUnit.size();i++)
		if(name==stateUnit[i].name)
			return i;
	return -1;
}

int NFA::createState(string name)    //处理state 并返回该state在stateUnit中的下标 
{
	if(notExit(name)==true)
	{
		NFA_STATE newState;
		newState.name = name;
		stateUnit.push_back(newState);
		return stateUnit.size()-1;
	}
	else
	{
		int position = getPosition(name);
		if(position!=-1)
			return position;
	}
	return -1;
}

void NFA::buildNFA(char txtPath[])
{
	SetConsoleOutputCP(437);
	fstream txtInput;
	txtInput.open(txtPath);
	while(!txtInput.eof())
	{
		
		string line;
		getline(txtInput,line);
		/*for(int i=0;i<line.length();i++)
		{
			unsigned char c;
			c = line[i];
			if(c==238)
				cout<<"****"<<endl;
		}
		cout<<line<<endl;*/
		string start="";
		int mark=1;
		for(mark=1;line[mark]!='>';mark++)
			start+=line[mark];
		int left = createState(start);
		
		int right = -1;
		
		unsigned char c;
		c = line[line.length()-1];
		if(c==238)
		{
			stateUnit[left].is_end_state = true;
			continue;
		}
				
		else
		{
			int endmark=line.length()-2;
			while(line[endmark]!='<')
				endmark--;
			string next="";
			for(int i=endmark+1;line[i]!='>';i++)             
				next+=line[i];
		
			right = createState(next);
			for(int i=mark+3;i<endmark;i++)    //<< 以及  <=怎么处理？
			{					
				string meet="";
				while(  (line[i]!='|'|| (line[i-1]=='|'&&line[i]=='|')) &&i<endmark)
				{
					meet+=line[i];
					i++;
				}
					
				pair<string,int> transfor = make_pair(meet,right);
				stateUnit[left].nextState.push_back(transfor);
			}
		}
	
	}
	
	txtInput.close();
	cout<<"Finish NFA build!"<<endl;
}

void NFA::showNFA()
{
	ofstream output;
	output.open("C:\\Users\\Eileen\\Compilers\\Lexer\\nfa.txt");
	for(int i=0;i<stateUnit.size();i++)
	{
		output<<"order: "<<i<<"  name:  "<<stateUnit[i].name<<endl;
		for(int j=0;j<stateUnit[i].nextState.size();j++)
		{
			output<<"when meet : "<<stateUnit[i].nextState[j].first;
			int index = stateUnit[i].nextState[j].second;
			output<<"  then go to state : "<<stateUnit[index].name<<endl;
		}
	}
	output.close();
}


const NFA_STATE_UNIT NFA::move(NFA_STATE_UNIT now,string name)
{

	NFA_STATE_UNIT nextStateUnit ;
	set<int> next;   //考虑push_back会产生重复元素, 所以用set 
	
	
	for(int i=0;i<now.size();i++)  //对NFA状态集合中的每一个状态 
	{
		
		NFA_STATE_UNIT temp = findNextState(now[i],name); //遇到字符name将转换到的状态集合 
		
		for(int j=0;j<temp.size();j++)
			next.insert( getPosition( temp[j].name ) );
	}
	
	
	set<int>::iterator it;                    //将set中的元素压入vector中 
	for(it= next.begin();it!=next.end();it++)
	{
		int index = *it;
		NFA_STATE temp = stateUnit[index];
		nextStateUnit.push_back(temp);
	}
	
	return nextStateUnit;
}

const NFA_STATE_UNIT NFA::closure(NFA_STATE_UNIT stateSet)   //求闭包epslion-closure（） 
{
	NFA_STATE_UNIT stateClosure;
	for(int i=0;i<stateSet.size();i++)
		stateClosure.push_back(stateSet[i]);          
	return stateClosure;
}

const NFA_STATE NFA::getStart()
{
	return stateUnit[0];
}

vector<string> NFA::calculateInput() 
{
	vector<string> result;
	//注意这里使用的stl set会自动对成员进行排序 
	set<string> temp;
	for(int i=0;i<stateUnit.size();i++)
	{
		for(int j=0;j<stateUnit[i].nextState.size();j++)
		{
			temp.insert(stateUnit[i].nextState[j].first);
		}
	}
	set<string>::iterator it;
	for(it= temp.begin();it!=temp.end();it++)
		result.push_back(*it);
	//cout<<"inpput string is : "<<result<<endl;
	return result;
}

void NFA::showUnit()
{
	ofstream output;
	output.open("C:\\Users\\Eileen\\Compilers\\Lexer\\nfaUnit.txt");
	output<<"This NFA Unit is :  ";
	for(int i=0;i<stateUnit.size();i++)
		output<<stateUnit[i].name<<"   ";
	output<<endl;
	output.close();
}

