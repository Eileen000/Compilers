#include<bits/stdc++.h>
#include"Production.h"
using namespace std;


void Production::showUnit()
{
	ofstream output;
	output.open("C:\\Users\\Eileen\\Compilers\\Parser\\proUnit.txt");
	for(int i=0;i<unit.size();i++)
		output<<unit[i]<<endl;
	output.close();
}
void Production::init(char path[])
{
	unit.push_back("S'->S");
	
	fstream in;
	in.open(path);
	string line="";
	while(!in.eof())
	{
		if(in.good())
		{
			char c ;
			in.get(c);
			if(c!='\n'&&c!='\t')
				line+=c;
			else
			{
				unit.push_back(line);
				line="";
			}	
		}
	}
	in.close();
 } 
 
 //找到 ->  左边是  c  的产生式集合 
vector<string> Production::findProduction(char c)
{
	vector<string> ans;
	//不从0开始，0是拓广文法 
	for(int i=1;i<unit.size();i++)
	{
		if(unit[i][0]==c)
			ans.push_back(unit[i]);
	}
	return ans;
}
int Production::findProIndex(string s)
{
	/*string x="";
	for(int i=0;i<s.length()-1;i++)
	{
		x[i]=s[i];
	}
	cout<<x<<endl;*/
	s[s.length()-1]='\0';
	string x = s;
	//cout<<x<<endl;
	for(int i =0;i<unit.size();i++)
	{
		bool flag = true;
		for(int j=0;j<x.length();j++)
		{
			if(x[j]!=unit[i][j])
			{
				flag = false;
				break;
			}
		}
		if(flag == false)
			continue;
		else
			return i;
	}
	return -1;
}
int Production::findPre(int index)
{
	string s = unit[index];
	return s.length()-3;
}
