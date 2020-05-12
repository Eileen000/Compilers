#include<bits/stdc++.h>
#include "Analysis.h"
#include "File.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	

	Production production;
	char path[10000];
	strcpy(path,"C:\\Users\\Eileen\\Compilers\\Parser\\production.txt");
	production.init(path);     //读入文法 
	production.showUnit();

	//构建项目集规范族 
	vector<In> In_unit;     
	In x;
	In_unit = x.Init(production);
	In_unit = x.buildInUnit(In_unit,production);
	x.showInUnit(In_unit);
	
	string s = read();   //读入token 
	s+="#";
	//cout<<s<<endl;
	//string xx = "ab<e>fe(){fe=j;fe=j;k(e=j;e>j;e++){fe=j;}mj;}#";
	string xxx="ab<e>fe(fe){fe=j;fe=j;p(e==j)e=j;mj;}#";
	
	//cout<<xx<<"  "<<xx.length()<<" "<<s.length()<<endl;
	
	//识别程序 
	Analysis an;
	an.buildCause(In_unit);
	an.init(In_unit,production);
	//an.judge(xxx,production);
	an.judge(s,production);
	
	return 0;
}
