#include<bits/stdc++.h>
#include "In.h"
using namespace std;

void In::showInUnit(vector<In>In_unit)
{
	ofstream out;
	out.open("C:\\Users\\Eileen\\Compilers\\Parser\\InUnit.txt");
	for(int i=0;i<In_unit.size();i++)
	{
		for(int j=0;j<In_unit[i].item.size();j++)
		{
			out<<i<<" , "<<j<<" "<<In_unit[i].item[j].sentence<<"   ,  "<<In_unit[i].item[j].first<<endl;
		}
		out<<endl;
	}
	out.close();
}
/*vector<Item> In::addClosure(vector<Item> a)
{
	for(int i=0;i<b.item.size();i++)
		a.item.push_back(b[i])
	return a;
}*/

//首先把拓广文法 S'->*S,# 加入 In 中   vector<Item>称为 Closure 
vector<In> In::Init(Production pro)
{
	
	vector<In>In_unit;
	
	Item extend;
	extend.sentence="S'->*S";
	extend.first="#";
	//findClosure的作用是根据当前item的找出它的闭包 
	vector<Item> clo = extend.findClosure(extend,pro);
	//cout<<"In"<<endl;
	//for(int i=0;i<clo.size();i++)
	//	cout<<clo[i].sentence<<" , "<<clo[i].first<<endl;
	
	In begin;
	begin.preInIndex = 0;
	begin.cause = ' ';
	begin.item = clo;
	
	In_unit.push_back(begin);
	showInUnit(In_unit);
	
	return In_unit;
}
bool In::Exit(In newIn,vector<In> In_unit)
{
	bool flag=false;
	//cout<<"here"<<endl;
	for(int i=0;i<In_unit.size();i++)
	{
		if(In_unit[i].item.size()!=newIn.item.size())
			continue;
		
		for(int j=0;j<newIn.item.size();j++)
		{
			flag = false;
			for(int k=0;k<In_unit[i].item.size();k++)
				if(In_unit[i].item[k].sentence == newIn.item[j].sentence
				&&In_unit[i].item[k].first == newIn.item[j].first)
				{
					flag = true;
					break;
				}
			if(flag == false)
				return false;
		}
		if(flag==true)
			return true;
	}
	return false;
}
vector<In> In::buildInUnit(vector<In> In_unit,Production pro)
{
	bool flag = true;
	
	int now = 0;
	//cout<<In_unit.size()<<endl;
	while(flag)
	{
		vector<char> cause;
		//把一个In中的GO（I，X）的 X 的集合放在 cause中 
		int i=0;
		/*if(now==0)
			i=1;
		else
			i=0;*/
		for(;i<In_unit[now].item.size();i++)
		{
			Item temp = In_unit[now].item[i];
			//cout<<"In_unit["<<now<<"].item["<<i<<"] : "<<temp.sentence;
			int index = temp.findStar(temp);
			if(index!=-1)
			{
				//cout<<"  "<<temp.sentence[index+1];
				bool cao = true;
				for(int j=0;j<cause.size();j++)
					if(cause[j]==temp.sentence[index+1])
					{
						cao = false;
						break;
					}
				if(cao==true)
				{
					cause.push_back(temp.sentence[index+1]);
				}
					
			}
		}
		
		//对 cause 中的每一个 X，执行 GO （I，X） 函数
		
		for(int i = 0;i<cause.size();i++)
		{
			In newIn;
			for(int j=0;j<In_unit[now].item.size();j++)
			{
				Item temp = In_unit[now].item[j];
				int index = temp.findStar(temp);
				if(index==-1)
					continue;
				char c = temp.sentence[index+1];
				
				if(c ==  cause[i])
				{
					Item e;
					
					temp.sentence[index]=temp.sentence[index+1];
					temp.sentence[index+1]='*';
				
					e.sentence = temp.sentence;
					e.first = temp.first;
					
					//寻找 e ：S->a*Ad闭包 
					vector<Item> item_temp = e.findClosure(e,pro);
					
					
					for(int k=0;k<item_temp.size();k++)
					{
						newIn.item.push_back(item_temp[k]);
					}		
				}
				else
					continue;
			
			}
			newIn.cause = cause[i];
			newIn.preInIndex = now;
			if(newIn.Exit(newIn,In_unit)==false)
			{
				In_unit.push_back(newIn);
				showInUnit(In_unit);
			}
				
		} 
		
		//判断是否接着寻找新的 In
		flag =false;
		
		if(now<In_unit.size()-1)
		{
			//cout<<"now : "<<now<<endl;
			flag = true;
			now++;
		}
		//cout<<now<<" "<<In_unit.size()<<endl;
		
	}
	//cout<<"Finish In build!"<<endl;
	return In_unit;
}

