/*#include<bits/stdc++.h>
#include "Closure.h"


//ע��ʹ�������������Ŀ���� ��Լ��Ŀ 
//�����Ŀ���Ѿ�����GO�����ĳ�ʼ��Ŀ 
//���� �����Ŀ�� A��??B? ,a 
//��ô��������ľ��� B->����,b �� 
// ���ݵ�ǰ��Ŀ����� �����Ŀ �ıհ� 
Closure Closure::findClosure(Item e)
{
	Closure newClosure;
	int index = e.findStar(e) ;
	string s = e.sentence ;
	newClosure.item.push_back(e);
	
	if(e.isVT(s[index+1])==true)
		return newClosure;

	Production production;
	queue<char> deal;
	deal.push(s[index+1]);
	
	while(!deal.empty())//���ݵ�ǰ���ս����հ� 
	{
		
		vector<string> search;
		//ע�� production ��û�� * �ŵ� 
		
		char now = deal.front();
		search = production.findProduction(now);
		deal.pop();
		
		for(int i=0;i<search.size();i++)
		{
			 
			Item newItem;
			//�����ַ��� ���� * ��
			search[i].insert(3,'*'); 
			newItem.sentence = search[i];
			newItem.first = e.FIRST(e);
			
			newClosure.item.push_back(newItem);
		
			// ��һ���Ǵ�д��ĸ���ս�� 
			if(newItem.isVT(search[i][4])==true)
			{
				//��������� A->Ab������� 
				if(now == search[i][4])
					continue;
				//��������� A->Bb������� 
				else
					deal.push(search[4]);
			}
		}
	}
	return newClosure;
	
}*/

