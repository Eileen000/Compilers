#include<bits/stdc++.h>
#include "Analysis.h"
using namespace std;
int Action[400][400];//���ս�� 
char ActionCC[400][400];
int GOTO[400][400];//�����ս��
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
	set<char>::iterator it;//set���ս���ͷ��ս����С�������� 
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
	//���пո�Ĭ��Ϊ�հ� 
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
				//����ǹ�Լ��Ŀ���ǽ�����Ŀ 
				if(index==-1)
				{
					//�ǽ�����Ŀ 
					//����Ŀ S����S?,# ����Ik ������ACTION[k,#]=acc
					if(In_unit[i].item[j].first=="#"&&i==1)
					{
						//0��ʾacc 
						//# �� Cause �е��±�Ϊ0 
						//cout<<"acc : "<<i<<endl;
						Action[i][over]=0;
					}
					//�ǹ�Լ��Ŀ
					//����Ŀ A��??,a ����Ik �����aΪ�κ��ս����#������ACTION[k,a] = rj ��jΪ����ʽ���
					//else
					//{
						//cout<<"��Լ"<<tmp.sentence<<"  "<<tmp.first<<endl;
						string s = In_unit[i].item[j].first;
						//pIndexΪ����ʽ��� 
						int pIndex = pro.findProIndex(tmp.sentence);
						//cout<<"����ʽ��ţ�"<<pIndex<<"  ";
						for(int k=0;k<s.size();k++)
						{
							int cIndex = findCause(s[k]);
							Action[i][cIndex] = pIndex;
							ActionCC[i][cIndex] = 'r';
							//cout<<ActionCC[i][cIndex]<<Action[i][cIndex]<<endl;
						}
						
						//ע�������cIndex ��ȡֵ����Ϊindex == -1 
						//cout<<"�ƽ�/��Լ"<<tmp.sentence<<endl;
						int cIndex = findCause(tmp.sentence[tmp.sentence.length()-2]);
						//���*ǰ�����ս�� ����ǰitem����A->��*a��ת������ 
						//cout<<cIndex<<endl;
						if(cIndex<border)
						{
							
							Action[In_unit[i].preInIndex][cIndex] = i;
							ActionCC[In_unit[i].preInIndex][cIndex] = 'S';
							//cout<<"S"<<Action[In_unit[i].preInIndex][cIndex]<<" "<<In_unit[i].preInIndex<<" "<<Cause[cIndex]<<endl;
						}
						//���*ǰ���Ƿ��ս�� ����ǰitem����A->A*a��ת������
						else
						{
							GOTO[In_unit[i].preInIndex][cIndex] = i;
							//cout<<"GOTO"<<In_unit[i].preInIndex<<"  "<<Cause[cIndex]<<"  : "<<i<<endl;
						}
						
				//	}
				}
				//������ƽ���Ŀ�����Ǵ�Լ��Ŀ 
				else //if(index>3&&i>0) //*�ڲ���ʽ�м�A��?*a?,b   ������ S->*A 
				{
					//cout<<"�ƽ�/��Լ"<<tmp.sentence<<endl;
					int cIndex = findCause(tmp.sentence[index-1]);
					//���*ǰ�����ս�� ����ǰitem����A->��*a��ת������ 
					if(cIndex<border)
					{
						
						Action[In_unit[i].preInIndex][cIndex] = i;
						ActionCC[In_unit[i].preInIndex][cIndex] = 'S';
						//cout<<"S"<<Action[In_unit[i].preInIndex][cIndex]<<endl;
					}
					//���*ǰ���Ƿ��ս�� ����ǰitem����A->A*a��ת������
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
		output<<"    �ƽ�";
	}
	if(method==1)
	{
		output<<"    ��Լ";
	}
	if(method==2)
	{
		output<<"    ����"<<"       acc";
		cout<<"YES"<<endl;
	}
		
	if(method==-1)
	{
		output<<"    ����";
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
	
	//��ʼ�� 
	cnt = 0;
	Symbol.push('#');
	State.push(0);
	for(int i=0;i<input.length();i++)
		Prepare.push(input[i]);
	
	while(flag&&!Prepare.empty()&&!State.empty())
	{
		cnt++;
		//��ǰ��������� 
		int cIndex = findCause(Prepare.front());
		//��ǰ״̬ 
		int state = State.top();
		/*if(state==-1)
		{
			cout<<"xstop"<<endl;
			break;
		}*/
		//cout<<cnt<<" : "<<state<<" �� "<<Cause[cIndex]<<"   "<<ActionCC[state][cIndex]<<Action[state][cIndex]<<endl;
		if(Action[state][cIndex]==-1) //��ǰ״̬����һ�����ű��� 
		{
		
			flag = false;
			method = -1;
			showProgress();
		}
		if(ActionCC[state][cIndex]=='S')
		{
			//�ƽ� 
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
		else if(ActionCC[state][cIndex]=='r'&&Action[state][cIndex])//�ǹ�Լ��Ŀ�����ǽ�����Ŀ 
		{
			
			//��Լ 
			method = 1;
			showProgress();
			
			//proIndex����ʽ��� 
			int proIndex = Action[state][cIndex];
			
			//���ݲ���ʽ����ҵ���->���ұߵ��ַ����� ,������״̬ջ�ͷ���ջ�����ĸ��� 
			int x = pro.findPre(proIndex);
			
			while(x--&&!Symbol.empty()&&!State.empty())
			{
				Symbol.pop();
				State.pop();
			}
				
			//c �Ǹò���ʽ�ľ�� 
			char c = pro.unit[proIndex][0];
			Symbol.push(c);
			
			//��ǰ����ջջ�������þ���������״̬ GOTO 
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
			//���� 
			method =2;
			showProgress();
			flag = false;
		}
		
		
	}
	output.close();
	//cout<<"finish token judge!"<<endl;
}


