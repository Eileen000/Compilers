#include<bits/stdc++.h>
#include"Item.h"
#ifndef IN_H
#define IN_H
using namespace std;


class In{
	
	public:
		int preInIndex;		 	//������ In �� In �±�
		char  cause;    		//����״̬ת���� �ַ� 
		vector<Item> item;	  	//��������Ŀ���� 
		
	public:
		
		vector<In> Init(Production pro);
		vector<In> buildInUnit(vector<In>In_unit,Production pro);
		//void addClosure(Closure a,Closure b);
		void showInUnit(vector<In>In_unit);
		bool Exit(In newIn,vector<In> In_unit);
	
};



#endif
