#include<bits/stdc++.h>
#include"Item.h"
#ifndef IN_H
#define IN_H
using namespace std;


class In{
	
	public:
		int preInIndex;		 	//产生此 In 的 In 下标
		char  cause;    		//引起状态转换的 字符 
		vector<Item> item;	  	//所含的项目集合 
		
	public:
		
		vector<In> Init(Production pro);
		vector<In> buildInUnit(vector<In>In_unit,Production pro);
		//void addClosure(Closure a,Closure b);
		void showInUnit(vector<In>In_unit);
		bool Exit(In newIn,vector<In> In_unit);
	
};



#endif
