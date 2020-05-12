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
	
	//��ȡ��������ʱ�� 
	DWORD start,end;
	
	start = GetTickCount();   
	
	//�����ķ� 
	char cPath[] = 	"C:\\Users\\Eileen\\Compilers\\Lexer\\chomskyIII.txt";
	createProduction(cPath);

	//�����ķ� ���� NFA 
	
	char path[100];
	strcpy(path,"C:\\Users\\Eileen\\Compilers\\Lexer\\chomskyIII.txt");
	NFA nfa;
	nfa.buildNFA(path);
	nfa.showNFA();
	//nfa.calculateInput();
	//nfa.showUnit();
	
	//���� DFA
	 
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
	
	
	//����ʶ�����  ʶ���ı� 
	Identify idtf;
	idtf.markFile();
	idtf.createToken(dfa);
	
	//�������ִ��ʱ�� 
	end = GetTickCount() - start;
	cout<<end<<endl;
	  
	return 0;
}
