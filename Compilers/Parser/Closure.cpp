/*#include<bits/stdc++.h>
#include "Closure.h"


//注意使用这个函数的项目不是 规约项目 
//这个项目是已经经过GO函数的初始项目 
//例如 这个项目是 A→??B? ,a 
//那么本函数求的就是 B->·γ,b 等 
// 根据当前项目，求出 这个项目 的闭包 
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
	
	while(!deal.empty())//根据当前非终结符求闭包 
	{
		
		vector<string> search;
		//注意 production 是没有 * 号的 
		
		char now = deal.front();
		search = production.findProduction(now);
		deal.pop();
		
		for(int i=0;i<search.size();i++)
		{
			 
			Item newItem;
			//处理字符串 加入 * 号
			search[i].insert(3,'*'); 
			newItem.sentence = search[i];
			newItem.first = e.FIRST(e);
			
			newClosure.item.push_back(newItem);
		
			// 第一个是大写字母非终结符 
			if(newItem.isVT(search[i][4])==true)
			{
				//如果是形如 A->Ab这种情况 
				if(now == search[i][4])
					continue;
				//如果是形如 A->Bb这种情况 
				else
					deal.push(search[4]);
			}
		}
	}
	return newClosure;
	
}*/

