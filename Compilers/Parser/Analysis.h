#include<bits/stdc++.h>
#include "In.h"
#ifndef ANALYSIS_H
#define ANALYSIS_H
class Analysis{
	
	public:
		 
		vector<char>Cause;
		int border;
		int over;
		
		int cnt;      //�ƽ���Լ���̵Ĳ���� 
		stack<char> Symbol;
		stack<int> State;
		queue<char> Prepare;
		int method;//0���ƽ�  1�ǹ�Լ  -1�Ǳ��� 
		
		char nowCC;
		int nowAction;//��ʾSj ����rj��j 
		int nowGo;  // ��ʾ״̬j 
	
		ofstream output;
	
	public:
		//������������� 
		void buildCause(vector<In> In_unit);
		void init(vector<In> In_unit,Production pro);
		bool judge(string input,Production pro);
		int findCause(char c);
		void showForm(vector<In> In_unit);
		void showProgress();
	
};


#endif
