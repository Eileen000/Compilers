#include <iostream>
#include <windows.h>
#include "Create.h"
#include "Identify.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;


int main() {
	
	
	/*File file;
	strcpy(file.filePath,"C:\\Users\\Eileen\\Compilers\\test.txt");
	file.readFile();*/
	
	//获取程序运行时间 
	DWORD start,end;
	
	start = GetTickCount();   
	
	//创建文法 
	char cPath[] = 	"C:\\Users\\Eileen\\Compilers\\Lexer\\chomskyIII.txt";
	createProduction(cPath);

	//读入文法 创建 NFA 
	
	char path[100];
	strcpy(path,"C:\\Users\\Eileen\\Compilers\\Lexer\\chomskyIII.txt");
	NFA nfa;
	nfa.buildNFA(path);
	nfa.showNFA();
	//nfa.calculateInput();
	//nfa.showUnit();
	
	//创建 DFA
	 
	DFA dfa;
	dfa.buildDFA(nfa);
	dfa.showProduction();
	
	/*string str;
	while(cin>>str)
	{
		int test = dfa.isLegal(str);
		if(test == -1)
			cout<<"ilegal"<<endl;
		else
			cout<<"legal"<<endl;
	}*/
	
	
	//启动识别程序  识别文本 
	Identify idtf;
	idtf.markFile();
	idtf.createToken(dfa);
	
	//输出程序执行时间 
	end = GetTickCount() - start;
	cout<<end<<endl;
	  
	return 0;
}
