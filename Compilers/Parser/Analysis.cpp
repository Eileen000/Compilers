#include<bits/stdc++.h>
#include "Analysis.h"
using namespace std;
int Action[400][400];//遇终结符 
char ActionCC[400][400];
int GOTO[400][400];//遇非终结符
void Analysis::buildCause(vector<In> In_unit)
{
	set<char> tmp;
	for(int i=0;i<In_unit.size();i++)
	{
		if(In_unit[i].cause!=' ')
			tmp.insert(In_unit[i].cause);
		for(int j=0;j<In_unit[i].item.size();j++)
		{
			string x = In_unit[i].item[j].first;
			for(int k=0;k<x.length();k++)
				if(In_unit[i].item[j].first[k]!=' ')
				tmp.insert(In_unit[i].item[j].first[k]);
		}
	}
		
	border=-1;
	over = -1;
	set<char>::iterator it;//set将终结符和非终结符从小到大排序 
	vector<char>cVT,cVN;
	Item e;
	for(it = tmp.begin();it!=tmp.end();it++)
	{
		if(e.isVT(*it)==true&&*it!='#')
			cVT.push_back(*it);
		else if(*it!='S'&&*it!='#')
			cVN.push_back(*it);
	}
	//Cause.push_back('#');
	for(int i=0;i<cVT.size();i++)
		Cause.push_back(cVT[i]);
	Cause.push_back('#');
	over = Cause.size()-1;
	Cause.push_back('S');
	for(int i=0;i<cVN.size();i++)
		Cause.push_back(cVN[i]);
	for(int i=0;i<Cause.size();i++)
		if(border==-1&&Cause[i]=='S')
		{
			border=i;
			break;
		}	
	
	//for(int i=0;i<Cause.size();i++)
	//	cout<<Cause[i]<<" ";
	//cout<<border<<" "<<over<<endl;
	//cout<<"Finish Cause!"<<endl;
}
int Analysis::findCause(char c)
{
	for(int i=0;i<Cause.size();i++)
		if(c==Cause[i])
			return i;
	return -1;
}
void Analysis::init(vector<In> In_unit,Production pro)
{
	//所有空格默认为空白 
	for(int i=0;i<400;i++)
		for(int j=0;j<400;j++)
		{
			Action[i][j]=-1;
			ActionCC[i][j]='@';
			GOTO[i][j]=-1;
		}
	for(int i=0;i<In_unit.size();i++)	
			for(int j=0;j<In_unit[i].item.size();j++)
			{
				Item tmp = In_unit[i].item[j];
				int index  = tmp.findStar(tmp);
				//如果是规约项目或是接受项目 
				if(index==-1)
				{
					//是接受项目 
					//若项目 S‘→S?,# 属于Ik ，则置ACTION[k,#]=acc
					if(In_unit[i].item[j].first=="#"&&i==1)
					{
						//0表示acc 
						//# 在 Cause 中的下标为0 
						//cout<<"acc : "<<i<<endl;
						Action[i][over]=0;
					}
					//是规约项目
					//若项目 A→??,a 属于Ik ，则对a为任何终结符或‘#’，置ACTION[k,a] = rj ，j为产生式编号
					//else
					//{
						//cout<<"规约"<<tmp.sentence<<"  "<<tmp.first<<endl;
						string s = In_unit[i].item[j].first;
						//pIndex为产生式编号 
						int pIndex = pro.findProIndex(tmp.sentence);
						//cout<<"产生式编号："<<pIndex<<"  ";
						for(int k=0;k<s.size();k++)
						{
							int cIndex = findCause(s[k]);
							Action[i][cIndex] = pIndex;
							ActionCC[i][cIndex] = 'r';
							//cout<<ActionCC[i][cIndex]<<Action[i][cIndex]<<endl;
						}
						
						//注意这里的cIndex 的取值，因为index == -1 
						//cout<<"移进/待约"<<tmp.sentence<<endl;
						int cIndex = findCause(tmp.sentence[tmp.sentence.length()-2]);
						//如果*前面是终结符 即当前item是由A->α*aβ转换过来 
						//cout<<cIndex<<endl;
						if(cIndex<border)
						{
							
							Action[In_unit[i].preInIndex][cIndex] = i;
							ActionCC[In_unit[i].preInIndex][cIndex] = 'S';
							//cout<<"S"<<Action[In_unit[i].preInIndex][cIndex]<<" "<<In_unit[i].preInIndex<<" "<<Cause[cIndex]<<endl;
						}
						//如果*前面是非终结符 即当前item是由A->A*aβ转换过来
						else
						{
							GOTO[In_unit[i].preInIndex][cIndex] = i;
							//cout<<"GOTO"<<In_unit[i].preInIndex<<"  "<<Cause[cIndex]<<"  : "<<i<<endl;
						}
						
				//	}
				}
				//如果是移进项目或者是待约项目 
				else //if(index>3&&i>0) //*在产生式中间A→?*a?,b   而不是 S->*A 
				{
					//cout<<"移进/待约"<<tmp.sentence<<endl;
					int cIndex = findCause(tmp.sentence[index-1]);
					//如果*前面是终结符 即当前item是由A->α*aβ转换过来 
					if(cIndex<border)
					{
						
						Action[In_unit[i].preInIndex][cIndex] = i;
						ActionCC[In_unit[i].preInIndex][cIndex] = 'S';
						//cout<<"S"<<Action[In_unit[i].preInIndex][cIndex]<<endl;
					}
					//如果*前面是非终结符 即当前item是由A->A*aβ转换过来
					else
					{
						GOTO[In_unit[i].preInIndex][cIndex] = i;
					}
				}
			}
	//cout<<"Finish Analysis Form build!"<<endl;
	showForm(In_unit);
}

void Analysis::showForm(vector<In> In_unit)
{
	ofstream out;
	out.open("C:\\Users\\Eileen\\Compilers\\Parser\\form.txt");
	out<<"       ";
	for(int j=0;j<Cause.size();j++)
		out<<"   "<<Cause[j]<<"    ";
	out<<endl;
	for(int i=0;i<In_unit.size();i++)
	{
		out<<i<<"  ";
		if(i<10)
			out<<"  ";
		if(i>=10&&i<=99)
			out<<" ";
		for(int j=0;j<border;j++)
		{
			if(ActionCC[i][j]=='@'&&Action[i][j]==-1)
				out<<"      ";	
			else if(ActionCC[i][j]=='r'&&Action[i][j]==0)
				out<<"  acc   ";
			else
			
				out<<"   "<<ActionCC[i][j]<<Action[i][j]<<"   ";
		}
			
		for(int j=border;j<Cause.size();j++)
			if(GOTO[i][j]==-1)
				out<<"      ";
			else
				out<<"   "<<GOTO[i][j]<<"   ";
			
		out<<endl;
	}
		
	out.close();
}

void Analysis::showProgress()
{
	output<<cnt<<"   ";
	stack<char>temp1;
	while(!Symbol.empty())
	{
		temp1.push(Symbol.top());
		Symbol.pop();
	}
	while(!temp1.empty())
	{
		output<<temp1.top();
		Symbol.push(temp1.top());
		temp1.pop();
	}
	output<<"         ";
	stack<int> temp2;
	while(!State.empty())
	{
		
		temp2.push(State.top());
		State.pop();
	}
	
	while(!temp2.empty())
	{
		output<<temp2.top();
		State.push(temp2.top());
		temp2.pop();
	}
	output<<"          ";
	queue<char>temp3;
	while(!Prepare.empty())
	{
		
		temp3.push(Prepare.front());
		Prepare.pop();
	}
	while(!temp3.empty())
	{
		output<<temp3.front();
		Prepare.push(temp3.front());
		temp3.pop();
	}
	if(method==0)
	{
		output<<"    移进";
	}
	if(method==1)
	{
		output<<"    归约";
	}
	if(method==2)
	{
		output<<"    接受"<<"       acc";
		cout<<"YES"<<endl;
	}
		
	if(method==-1)
	{
		output<<"    报错";
		ofstream outW;
		outW.open("C:\\Users\\Eileen\\Compilers\\Parser\\wrong.txt");
		int line = 6;
		outW<<"Line "<<line<<" is wrong :  Symbol "<<Symbol.top()<<"  meet "<<Prepare.front()<<" could not continue!"<<endl;
		outW.close();
		cout<<"NO"<<endl;
	}
		
	output<<endl;
}

bool Analysis::judge(string input,Production pro)
{
	
	
	output.open("C:\\Users\\Eileen\\Compilers\\Parser\\judge.txt");
	bool flag = true;
	
	//初始化 
	cnt = 0;
	Symbol.push('#');
	State.push(0);
	for(int i=0;i<input.length();i++)
		Prepare.push(input[i]);
	
	while(flag&&!Prepare.empty()&&!State.empty())
	{
		cnt++;
		//当前待输入符号 
		int cIndex = findCause(Prepare.front());
		//当前状态 
		int state = State.top();
		/*if(state==-1)
		{
			cout<<"xstop"<<endl;
			break;
		}*/
		//cout<<cnt<<" : "<<state<<" 遇 "<<Cause[cIndex]<<"   "<<ActionCC[state][cIndex]<<Action[state][cIndex]<<endl;
		if(Action[state][cIndex]==-1) //当前状态遇下一个符号报错 
		{
		
			flag = false;
			method = -1;
			showProgress();
		}
		if(ActionCC[state][cIndex]=='S')
		{
			//移进 
			method = 0;
			showProgress();
			
			Symbol.push(Prepare.front());
			Prepare.pop();
			State.push(Action[state][cIndex]);
			/*if(State.top()==-1)
			{
				cout<<"stop"<<endl;
				showProgress();
			}*/
			continue;
			
		}
		else if(ActionCC[state][cIndex]=='r'&&Action[state][cIndex])//是归约项目但不是接受项目 
		{
			
			//归约 
			method = 1;
			showProgress();
			
			//proIndex产生式编号 
			int proIndex = Action[state][cIndex];
			
			//根据产生式编号找到它->的右边的字符个数 ,将决定状态栈和符号栈弹出的个数 
			int x = pro.findPre(proIndex);
			
			while(x--&&!Symbol.empty()&&!State.empty())
			{
				Symbol.pop();
				State.pop();
			}
				
			//c 是该产生式的句柄 
			char c = pro.unit[proIndex][0];
			Symbol.push(c);
			
			//当前符号栈栈顶遇到该句柄将到达的状态 GOTO 
			int next = GOTO[State.top()][findCause(c)];
			State.push(next);
			/*if(State.top()==-1)
			{
				cout<<"stop"<<endl;
				showProgress();
			}*/
			continue;
			
		}
		else if(ActionCC[state][cIndex]=='r'&&Action[state][cIndex]==0)
		{
			//接受 
			method =2;
			showProgress();
			flag = false;
		}
		
		
	}
	output.close();
	//cout<<"finish token judge!"<<endl;
}


