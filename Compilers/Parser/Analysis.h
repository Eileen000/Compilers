#include<bits/stdc++.h>
#include "In.h"
#ifndef ANALYSIS_H
#define ANALYSIS_H
class Analysis{
	
	public:
		 
		vector<char>Cause;
		int border;
		int over;
		
		int cnt;      //移进规约过程的步骤号 
		stack<char> Symbol;
		stack<int> State;
		queue<char> Prepare;
		int method;//0是移进  1是规约  -1是报错 
		
		char nowCC;
		int nowAction;//表示Sj 还是rj的j 
		int nowGo;  // 表示状态j 
	
		ofstream output;
	
	public:
		//构建分析表的行 
		void buildCause(vector<In> In_unit);
		void init(vector<In> In_unit,Production pro);
		bool judge(string input,Production pro);
		int findCause(char c);
		void showForm(vector<In> In_unit);
		void showProgress();
	
};


#endif
