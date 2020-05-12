#include<bits/stdc++.h>
#include "Item.h"
using namespace std;

//VT  �ս�� 
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
string Item::FIRST(char c,Production pro)   //��FIRST()�� 
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
				ans+=FIRST(prox[i][3],pro);  //�ݹ����first 
	}
	set<char> tmp;     //set�����ظ� 
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
	//�ѵ�ǰ��Ŀ A->X*BY����հ��� 
	vector<Item> newClosure;
	newClosure.push_back(e);
	
	int index = findStar(e) ;

	if(index == -1)
		return newClosure; 
	
	string s = e.sentence ;
	if(isVT(s[index+1])==true)
		return newClosure;
	//������ս��  ��հ�����Ҫ������ 
	
	queue<Item> deal;
	
	deal.push(e);
	
	while(!deal.empty())//���ݵ�ǰ���ս����հ� 
	{
		
		vector<string> search;
		//ע�� production ��û�� * �ŵ� 
		Item now = deal.front();
		int indexNow = now.findStar(now);
		
		search = pro.findProduction(now.sentence[indexNow+1]);
		deal.pop();
		for(int i=0;i<search.size();i++)
		{
			Item newItem;
			//�����ַ��� ���� * ��
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
		
			// ��һ���Ǵ�д��ĸ���ս�� 
			if(newItem.isVT(search[i][4])==false)
			{
				
				//��������� A->Ab������� 
				if(now.sentence[indexNow+1]==search[i][4])
					continue;
				//��������� A->Bb������� 
				else 
				{
				 
					deal.push(newItem);
				} 
				
			}
		}
		
	}
	

	return newClosure;
	
}
