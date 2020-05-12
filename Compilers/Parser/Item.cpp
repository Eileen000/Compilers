#include<bits/stdc++.h>
#include "Item.h"
using namespace std;

//VT  终结符 
bool Item::isVT(char c)
{
	if(c>='A'&&c<='Z')
		return false;
	return true;
}
int Item::findStar(Item e)
{
	int index = 0;
	for(int i=0;i<e.sentence.length();i++)
		if(e.sentence[i]=='*')
		{
			index = i;
			break;
		}
	if(index == e.sentence.length()-1)
		index = -1;
	return index;
}
string Item::FIRST(char c,Production pro)   //求FIRST()集 
{
	string ans="";
	if(isVT(c)==true)
	{
		ans+=c;
	}
	else
	{
		vector<string> prox;
		prox = pro.findProduction(c);
		for(int i=0;i<prox.size();i++)
			if(prox[i][3]==c)
				continue;
			else
				ans+=FIRST(prox[i][3],pro);  //递归查找first 
	}
	set<char> tmp;     //set避免重复 
	for(int i=0;i<ans.length();i++)
		tmp.insert(ans[i]);
	set<char>::iterator it;
	ans="";
	for(it=tmp.begin();it!=tmp.end();it++)
		ans+=*it;
	return ans; 
}
bool Item::notExit(queue<Item>deal,Item e)
{
	bool ans = true;
	while(!deal.empty())
	{
		if(e.sentence==deal.front().sentence&&e.first==deal.front().first)
			return false;
		deal.pop();
	}
	return true;
}
bool Item::Exit(Item e,vector<Item>II)
{
	for(int i=0;i<II.size();i++)
	{
		if(e.sentence==II[i].sentence&&e.first==II[i].first )
			return true;
	}
	return false;
}
vector<Item> Item::findClosure(Item e,Production pro)
{
	//把当前项目 A->X*BY放入闭包中 
	vector<Item> newClosure;
	newClosure.push_back(e);
	
	int index = findStar(e) ;

	if(index == -1)
		return newClosure; 
	
	string s = e.sentence ;
	if(isVT(s[index+1])==true)
		return newClosure;
	//如果是终结符  则闭包不需要再求了 
	
	queue<Item> deal;
	
	deal.push(e);
	
	while(!deal.empty())//根据当前非终结符求闭包 
	{
		
		vector<string> search;
		//注意 production 是没有 * 号的 
		Item now = deal.front();
		int indexNow = now.findStar(now);
		
		search = pro.findProduction(now.sentence[indexNow+1]);
		deal.pop();
		for(int i=0;i<search.size();i++)
		{
			Item newItem;
			//处理字符串 加入 * 号
			search[i].insert(3,"*"); 
		
			newItem.sentence = search[i];
		
			if(now.sentence.length()<indexNow+3)
			{
				newItem.first  = now.first;
			}
			else
			{
				char c = now.sentence[indexNow+2];
				newItem.first = FIRST(c,pro); 
			 } 
			
		
			if(Exit(newItem,newClosure)==false)
				newClosure.push_back(newItem);
		
			// 第一个是大写字母非终结符 
			if(newItem.isVT(search[i][4])==false)
			{
				
				//如果是形如 A->Ab这种情况 
				if(now.sentence[indexNow+1]==search[i][4])
					continue;
				//如果是形如 A->Bb这种情况 
				else 
				{
				 
					deal.push(newItem);
				} 
				
			}
		}
		
	}
	

	return newClosure;
	
}
